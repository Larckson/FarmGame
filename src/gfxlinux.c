#ifndef GFXLINUX
#define GFXLINUX

#include "charbitmap.c"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <stdlib.h>

/* screen */
#define SCREENW 800
#define SCREENH 600

/* color */
#define COLRGB(r,g,b) ((unsigned int)(((r)<<16)|((g)<<8)|(b)))
#define BLACK   COLRGB(0  ,0  ,0  )
#define WHITE   COLRGB(255,255,255)
#define RED     COLRGB(255,0  ,0  )
#define GREEN   COLRGB(0  ,255,0  )
#define BLUE    COLRGB(0  ,0  ,255)
#define YELLOW  COLRGB(255,255,0  )
#define CYAN    COLRGB(0  ,255,255)
#define MAGENTA COLRGB(255,0  ,255)

/* utils.asm (or equivalent C fallbacks if not linking asm on linux) */
extern int abs_val(int x);
extern void mem_set(void *dst, int val, unsigned int n);

/* ── internal state ──────────────────────────────────────────────────────── */
extern long clone(long (*fn)(void *),void *stack,int flags,void *arg);
extern int tgkill(int tgid,int tid,int sig);
extern int getpid(void);
extern int gettid(void);
extern void *mmap(void*,unsigned long,int,int,int,long);

#define PROT_READ       0x1
#define PROT_WRITE      0x2
#define MAP_PRIVATE     0x02
#define MAP_ANONYMOUS   0x20
#define MAP_STACK       0x20000
#define MAP_FAILED      ((void *)-1)
#define STACK_SIZE      524288
#define SIGUSR1         10

/* clone flags: thread-like behavior */
#define CLONE_FLAGS ( \
    0x00000100 |  /* CLONE_VM       - share memory space    */ \
    0x00000200 |  /* CLONE_FS       - share filesystem info */ \
    0x00000400 |  /* CLONE_FILES    - share file descriptors*/ \
    0x00000800 |  /* CLONE_SIGHAND  - share signal handlers */ \
    0x00010000 |  /* CLONE_THREAD   - same thread group     */ \
    0x80000000 )  /* CLONE_IO       - share IO context      */

/* --- CreateThread replacement --- */
static void *CreateThread(void *lpThreadAttributes,
                          unsigned long dwStackSize,
                          long (*lpStartAddress)(void *),
                          void *lpParameter,
                          unsigned long dwCreationFlags,
                          unsigned long *lpThreadId)
{
    (void)lpThreadAttributes;
    (void)dwStackSize;
    (void)dwCreationFlags;

    char *stack = (char *)mmap((void*)0, STACK_SIZE,
                               PROT_READ | PROT_WRITE,
                               MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK,
                               -1, 0);
    if (stack == MAP_FAILED)
        return (void *)-1;

    /* compute 16-byte aligned stack top */
    unsigned long stack_top = (unsigned long)(stack + STACK_SIZE);
    stack_top &= ~0xFUL; /* align down to 16 */

    long tid = clone(lpStartAddress,
                     (void*)stack_top,
                     CLONE_FLAGS,
                     lpParameter);

    if (lpThreadId)
        *lpThreadId = (unsigned long)tid;

    return (void*)(long)tid;
}

unsigned int *frame_buffer = 0;

static Display     *g_display  = 0;
static Window       g_window   = 0;
static GC           g_gc       = 0;
static XImage      *g_ximage   = 0;
static int          g_screen   = 0;
static int          g_running  = 1;

static int click_x = 0;
static int click_y = 0;

void gfx_clear(int height_start) {
    mem_set(frame_buffer + SCREENW * height_start, 0,
            4 * SCREENW * (SCREENH - height_start));
}

/* init/shutdown */
int gfx_init(const char *title) {
    Visual         *visual;
    XSetWindowAttributes attrs;
    unsigned long   attr_mask;
    XSizeHints      hints;

    g_display = XOpenDisplay(0);
    if (!g_display) { return 0; }

    g_screen = DefaultScreen(g_display);
    visual   = DefaultVisual(g_display, g_screen);

    attr_mask             = CWBackPixel | CWEventMask;
    attrs.background_pixel = BlackPixel(g_display, g_screen);
    attrs.event_mask      = KeyPressMask | ButtonPressMask | StructureNotifyMask;

    g_window = XCreateWindow(
        g_display,
        RootWindow(g_display, g_screen),
        0, 0, SCREENW, SCREENH, 0,
        DefaultDepth(g_display, g_screen),
        InputOutput,
        visual,
        attr_mask,
        &attrs
    );
    if (!g_window) { return 0; }

    /* Fixed size window (mirrors AdjustWindowRect + no resize) */
    hints.flags      = PMinSize | PMaxSize;
    hints.min_width  = hints.max_width  = SCREENW;
    hints.min_height = hints.max_height = SCREENH;
    XSetWMNormalHints(g_display, g_window, &hints);

    XStoreName(g_display, g_window, title);
    XMapWindow(g_display, g_window);

    g_gc = XCreateGC(g_display, g_window, 0, 0);

    frame_buffer = (unsigned int *)malloc(4 * SCREENW * SCREENH);
    if (!frame_buffer) { return 0; }

    g_ximage = XCreateImage(
        g_display, visual,
        DefaultDepth(g_display, g_screen),
        ZPixmap, 0,
        (char *)frame_buffer,
        SCREENW, SCREENH,
        32, SCREENW * 4
    );
    if (!g_ximage) { return 0; }

    gfx_clear(0);
    return 1;
}

void gfx_shutdown(void) {
    if (g_ximage) {
        g_ximage->data = 0; /* we own the buffer; stop XDestroyImage freeing it */
        XDestroyImage(g_ximage);
    }
    if (g_gc)      { XFreeGC(g_display, g_gc); }
    if (g_window)  { XDestroyWindow(g_display, g_window); }
    if (g_display) { XCloseDisplay(g_display); }
    if (frame_buffer) { free(frame_buffer); }
}

int gfx_present(void) {
    XEvent ev;

    /* Drain all pending events */
    while (XPending(g_display)) {
        XNextEvent(g_display, &ev);
        switch (ev.type) {
            case DestroyNotify:
            case ClientMessage:
                g_running = 0;
                break;
            case KeyPress: {
                KeySym ks = XLookupKeysym(&ev.xkey, 0);
                if (ks == XK_Escape) {
                    g_running = 0;
                }
                break;
            }
            case ButtonPress:
                if (ev.xbutton.button == Button1) {
                    click_x = ev.xbutton.x;
                    click_y = ev.xbutton.y;
                }
                break;
        }
    }

    XPutImage(g_display, g_window, g_gc, g_ximage,
              0, 0, 0, 0, SCREENW, SCREENH);
    XFlush(g_display);
    return g_running;
}

#endif
