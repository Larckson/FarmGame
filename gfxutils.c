/* ── screen ──────────────────────────────────────────────────────────────── */
#define SCREEN_W 800
#define SCREEN_H 600

/* ── colour ──────────────────────────────────────────────────────────────── */
#define MKRGB(r,g,b) ((unsigned int)(((r)<<16)|((g)<<8)|(b)))
#define BLACK   MKRGB(0,0,0)
#define WHITE   MKRGB(255,255,255)
#define RED     MKRGB(255,0,0)
#define GREEN   MKRGB(0,255,0)
#define BLUE    MKRGB(0,0,255)
#define YELLOW  MKRGB(255,255,0)
#define CYAN    MKRGB(0,255,255)
#define MAGENTA MKRGB(255,0,255)

/* ── Win32 constants ─────────────────────────────────────────────────────── */
#define WS_OVERLAPPED       0x00000000
#define WS_CAPTION          0x00C00000
#define WS_SYSMENU          0x00080000
#define WS_THICKFRAME       0x00040000
#define WS_MINIMIZEBOX      0x00020000
#define WS_MAXIMIZEBOX      0x00010000
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX)
#define WS_VISIBLE          0x10000000
#define CS_OWNDC            0x0020
#define CW_USEDEFAULT       ((int)0x80000000)
#define WM_DESTROY          0x0002
#define WM_KEYDOWN          0x0100
#define VK_ESCAPE           0x1B
#define PM_REMOVE           0x0001
#define SRCCOPY             0x00CC0020
#define DIB_RGB_COLORS      0
#define BI_RGB              0
#define FALSE               0
#define IDC_ARROW           ((const char *)32512)

/* ── Win32 structs ───────────────────────────────────────────────────────── */
typedef struct {
    unsigned int  cbSize;
    unsigned int  style;
    void         *lpfnWndProc;
    int           cbClsExtra;
    int           cbWndExtra;
    void         *hInstance;
    void         *hIcon;
    void         *hCursor;
    void         *hbrBackground;
    const char   *lpszMenuName;
    const char   *lpszClassName;
    void         *hIconSm;
} WNDCLASSEXA;

typedef struct { int left, top, right, bottom; } RECT;

typedef struct {
    unsigned int   biSize;
    int            biWidth;
    int            biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int   biCompression;
    unsigned int   biSizeImage;
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;
} BITMAPINFOHEADER;

typedef struct {
    BITMAPINFOHEADER bmiHeader;
    unsigned int     bmiColors[1];
} BITMAPINFO;

typedef struct {
    void         *hwnd;
    unsigned int  message;
    unsigned int  pad;
    void         *wParam;
    void         *lParam;
    unsigned int  time;
    int           pt_x;
    int           pt_y;
} MSG;

/* ── Win32 imports (-lgdi32 -luser32 in linker settings) ────────────────── */
extern void * __stdcall RegisterClassExA(const WNDCLASSEXA *);
extern void * __stdcall CreateWindowExA(unsigned int,const char*,const char*,unsigned int,int,int,int,int,void*,void*,void*,void*);
extern int    __stdcall AdjustWindowRect(RECT*,unsigned int,int);
extern void * __stdcall GetDC(void*);
extern int    __stdcall ReleaseDC(void*,void*);
extern int    __stdcall PeekMessageA(MSG*,void*,unsigned int,unsigned int,unsigned int);
extern int    __stdcall TranslateMessage(const MSG*);
extern void * __stdcall DispatchMessageA(const MSG*);
extern int    __stdcall DestroyWindow(void*);
extern void   __stdcall PostQuitMessage(int);
extern void * __stdcall DefWindowProcA(void*,unsigned int,void*,void*);
extern void * __stdcall LoadCursorA(void*,const char*);
extern void * __stdcall CreateCompatibleDC(void*);
extern void * __stdcall CreateDIBSection(void*,const BITMAPINFO*,unsigned int,void**,void*,unsigned int);
extern void * __stdcall SelectObject(void*,void*);
extern int    __stdcall DeleteObject(void*);
extern int    __stdcall DeleteDC(void*);
extern int    __stdcall BitBlt(void*,int,int,int,int,void*,int,int,unsigned int);
extern void * __stdcall GetModuleHandleA(const char*);

/* ── from utils.asm ──────────────────────────────────────────────────────── */
extern int gfx_abs(int x);

/* ── forward declarations ────────────────────────────────────────────────── */
void  gfx_clear(unsigned int color);
void  gfx_put_pixel(int x, int y, unsigned int color);
void  gfx_hline(int x0, int x1, int y, unsigned int color);
void  gfx_vline(int x, int y0, int y1, unsigned int color);
void  gfx_line(int x0, int y0, int x1, int y1, unsigned int color);
void  gfx_rect(int x, int y, int w, int h, unsigned int color);
void  gfx_rect_fill(int x, int y, int w, int h, unsigned int color);
void  gfx_circle(int cx, int cy, int r, unsigned int color);
void  gfx_circle_fill(int cx, int cy, int r, unsigned int color);
int   gfx_init(const char *title);
void  gfx_shutdown(void);
int   gfx_present(void);

/* ── internal state ──────────────────────────────────────────────────────── */
unsigned int *framebuffer = 0;

static void         *g_hwnd    = 0;
static void         *g_hdc     = 0;
static void         *g_hbm     = 0;
static void         *g_memdc   = 0;
static BITMAPINFO    g_bmi;
static int           g_running = 1;

/* ── manual memset ───────────────────────────────────────────────────────── */
static void gfx_memset(void *dst, int val, unsigned int n)
{
    unsigned char *p = (unsigned char *)dst;
    while (n--) *p++ = (unsigned char)val;
}

/* ── window procedure ────────────────────────────────────────────────────── */
typedef void * (__stdcall *WNDPROC)(void*, unsigned int, void*, void*);

static void * __stdcall wnd_proc(void *hwnd, unsigned int msg, void *wp, void *lp)
{
    switch (msg) {
        case WM_DESTROY:
            g_running = 0;
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            if (wp == (void *)VK_ESCAPE) {
                g_running = 0;
                DestroyWindow(hwnd);
            }
            return 0;
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
}

/* ── init / shutdown ─────────────────────────────────────────────────────── */
int gfx_init(const char *title)
{
    WNDCLASSEXA wc;
    RECT r;
    void *bits;
    union { WNDPROC fn; void *ptr; } proc_cast;

    gfx_memset(&wc, 0, sizeof(wc));
    wc.cbSize        = sizeof(wc);
    wc.style         = CS_OWNDC;
    proc_cast.fn     = wnd_proc;
    wc.lpfnWndProc   = proc_cast.ptr;
    wc.hInstance     = GetModuleHandleA(0);
    wc.hCursor       = LoadCursorA(0, IDC_ARROW);
    wc.lpszClassName = "GfxWnd";
    RegisterClassExA(&wc);

    r.left = 0; r.top = 0; r.right = SCREEN_W; r.bottom = SCREEN_H;
    AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);

    g_hwnd = CreateWindowExA(
        0, "GfxWnd", title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        r.right - r.left, r.bottom - r.top,
        0, 0, GetModuleHandleA(0), 0
    );
    if (!g_hwnd) return 0;

    g_hdc   = GetDC(g_hwnd);
    g_memdc = CreateCompatibleDC(g_hdc);

    gfx_memset(&g_bmi, 0, sizeof(g_bmi));
    g_bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    g_bmi.bmiHeader.biWidth       = SCREEN_W;
    g_bmi.bmiHeader.biHeight      = -SCREEN_H;
    g_bmi.bmiHeader.biPlanes      = 1;
    g_bmi.bmiHeader.biBitCount    = 32;
    g_bmi.bmiHeader.biCompression = BI_RGB;

    bits  = 0;
    g_hbm = CreateDIBSection(g_memdc, &g_bmi, DIB_RGB_COLORS, &bits, 0, 0);
    if (!g_hbm) return 0;

    SelectObject(g_memdc, g_hbm);
    framebuffer = (unsigned int *)bits;

    gfx_clear(BLACK);
    return 1;
}

void gfx_shutdown(void)
{
    if (g_hbm)   DeleteObject(g_hbm);
    if (g_memdc) DeleteDC(g_memdc);
    if (g_hdc)   ReleaseDC(g_hwnd, g_hdc);
}

int gfx_present(void)
{
    MSG msg;
    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    BitBlt(g_hdc, 0, 0, SCREEN_W, SCREEN_H, g_memdc, 0, 0, SRCCOPY);
    return g_running;
}

/* ── primitives ──────────────────────────────────────────────────────────── */
void gfx_clear(unsigned int color)
{
    int n = SCREEN_W * SCREEN_H;
    unsigned int *p = framebuffer;
    while (n--) *p++ = color;
}

static int in_bounds(int x, int y)
{
    return (unsigned int)x < SCREEN_W && (unsigned int)y < SCREEN_H;
}

void gfx_put_pixel(int x, int y, unsigned int color)
{
    if (in_bounds(x, y))
        framebuffer[y * SCREEN_W + x] = color;
}

void gfx_hline(int x0, int x1, int y, unsigned int color)
{
    unsigned int *row;
    int n, t;
    if ((unsigned int)y >= SCREEN_H) return;
    if (x0 > x1) { t = x0; x0 = x1; x1 = t; }
    if (x0 < 0) x0 = 0;
    if (x1 >= SCREEN_W) x1 = SCREEN_W - 1;
    row = framebuffer + y * SCREEN_W + x0;
    n = x1 - x0 + 1;
    while (n--) *row++ = color;
}

void gfx_vline(int x, int y0, int y1, unsigned int color)
{
    unsigned int *p;
    int n, t;
    if ((unsigned int)x >= SCREEN_W) return;
    if (y0 > y1) { t = y0; y0 = y1; y1 = t; }
    if (y0 < 0) y0 = 0;
    if (y1 >= SCREEN_H) y1 = SCREEN_H - 1;
    p = framebuffer + y0 * SCREEN_W + x;
    n = y1 - y0 + 1;
    while (n--) { *p = color; p += SCREEN_W; }
}

void gfx_line(int x0, int y0, int x1, int y1, unsigned int color)
{
    int dx  =  gfx_abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy  = -gfx_abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;
    for (;;) {
        gfx_put_pixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void gfx_rect(int x, int y, int w, int h, unsigned int color)
{
    gfx_hline(x,     x+w-1, y,     color);
    gfx_hline(x,     x+w-1, y+h-1, color);
    gfx_vline(x,     y,     y+h-1, color);
    gfx_vline(x+w-1, y,     y+h-1, color);
}

void gfx_rect_fill(int x, int y, int w, int h, unsigned int color)
{
    int row;
    for (row = y; row < y + h; row++)
        gfx_hline(x, x + w - 1, row, color);
}

void gfx_circle(int cx, int cy, int r, unsigned int color)
{
    int x = 0, y = r, d = 1 - r;
    while (x <= y) {
        gfx_put_pixel(cx+x, cy+y, color); gfx_put_pixel(cx-x, cy+y, color);
        gfx_put_pixel(cx+x, cy-y, color); gfx_put_pixel(cx-x, cy-y, color);
        gfx_put_pixel(cx+y, cy+x, color); gfx_put_pixel(cx-y, cy+x, color);
        gfx_put_pixel(cx+y, cy-x, color); gfx_put_pixel(cx-y, cy-x, color);
        if (d < 0) d += 2*x + 3;
        else       { d += 2*(x-y) + 5; y--; }
        x++;
    }
}

void gfx_circle_fill(int cx, int cy, int r, unsigned int color)
{
    int x = 0, y = r, d = 1 - r;
    while (x <= y) {
        gfx_hline(cx-x, cx+x, cy+y, color);
        gfx_hline(cx-x, cx+x, cy-y, color);
        gfx_hline(cx-y, cx+y, cy+x, color);
        gfx_hline(cx-y, cx+y, cy-x, color);
        if (d < 0) d += 2*x + 3;
        else       { d += 2*(x-y) + 5; y--; }
        x++;
    }
}
