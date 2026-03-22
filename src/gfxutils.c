#ifndef GFXUTILS
#define GFXUTILS

#include "charbitmap.c"

/* screen */
#define SCREEN_W 800
#define SCREEN_H 600

/* color */
#define COL_RGB(r,g,b) ((unsigned int)(((r)<<16)|((g)<<8)|(b)))
#define BLACK   COL_RGB(0  ,0  ,0  )
#define WHITE   COL_RGB(255,255,255)
#define RED     COL_RGB(255,0  ,0  )
#define GREEN   COL_RGB(0  ,255,0  )
#define BLUE    COL_RGB(0  ,0  ,255)
#define YELLOW  COL_RGB(255,255,0  )
#define CYAN    COL_RGB(0  ,255,255)
#define MAGENTA COL_RGB(255,0  ,255)

/* Win32 structs */
struct wind_class { /* WNDCLASSEXA */
    unsigned int cb_size;
    unsigned int style;
    void *lpfn_wnd_proc;
    int cb_cls_extra;
    int cb_wnd_extra;
    void *h_instance;
    void *h_icon;
    void *h_cursor;
    void *hbr_background;
    const char *lpsz_menu_name;
    const char *lpsz_class_name;
    void *h_icon_sm;
};

struct rect { int left,top,right,bottom; }; /* RECT */

struct bitmap_info_header { /* BITMAPINFOHEADER */
    unsigned int bi_size;
    int bi_width;
    int bi_height;
    unsigned short bi_planes;
    unsigned short bi_bit_count;
    unsigned int bi_compression;
    unsigned int bi_sizeImage;
    int bi_x_pels_per_meter;
    int bi_y_pels_per_meter;
    unsigned int bi_clr_used;
    unsigned int bi_clr_important;
};

struct bitmap_info { /* BITMAPINFO */
    struct bitmap_info_header bmi_header;
    unsigned int bmiColors[1];
};

struct winuser_thread_msg { /* MSG */
    void         *hwnd;
    unsigned int  message;
    unsigned int  pad;
    void         *w_Param;
    void         *l_param;
    unsigned int  time;
    int           pt_x;
    int           pt_y;
};

/* Win32 imports (-lgdi32 -luser32 in linker settings) */
extern void * __stdcall RegisterClassExA(const struct wind_class *);
extern void * __stdcall CreateWindowExA(unsigned int,const char*,const char*,unsigned int,int,int,int,int,void*,void*,void*,void*);
extern int    __stdcall AdjustWindowRect(struct rect*,unsigned int,int);
extern void * __stdcall GetDC(void*);
extern int    __stdcall ReleaseDC(void*,void*);
extern int    __stdcall PeekMessageA(struct winuser_thread_msg*,void*,unsigned int,unsigned int,unsigned int);
extern int    __stdcall TranslateMessage(const struct winuser_thread_msg*);
extern void * __stdcall DispatchMessageA(const struct winuser_thread_msg*);
extern int    __stdcall DestroyWindow(void*);
extern void   __stdcall PostQuitMessage(int);
extern void * __stdcall DefWindowProcA(void*,unsigned int,void*,void*);
extern void * __stdcall LoadCursorA(void*,const char*);
extern void * __stdcall CreateCompatibleDC(void*);
extern void * __stdcall CreateDIBSection(void*,const struct bitmap_info*,unsigned int,void**,void*,unsigned int);
extern void * __stdcall SelectObject(void*,void*);
extern int    __stdcall DeleteObject(void*);
extern int    __stdcall DeleteDC(void*);
extern int    __stdcall BitBlt(void*,int,int,int,int,void*,int,int,unsigned int);
extern void * __stdcall GetModuleHandleA(const char*);

/* utils.asm */
extern int abs_val(int x);
extern void mem_set(void *dst,int val,unsigned int n);

/* ── internal state ──────────────────────────────────────────────────────── */
unsigned int *frame_buffer=0;

static void *g_hwnd=0;
static void *g_hdc=0;
static void *g_hbm=0;
static void *g_memdc=0;
static struct bitmap_info g_bmi;
static int g_running=1;

static int mouse_x_click=0;
static int mouse_y_click=0;

/* window procedure */
typedef void * (__stdcall *WNDPROC)(void*, unsigned int, void*, void*);

static void * __stdcall wnd_proc(void *hwnd, unsigned int msg, void *wp, void *lp) {
    switch (msg) {
        case 0x0002: { /* VM_DESTROY */
            g_running = 0;
            PostQuitMessage(0);
            return 0;
        }
        case 0x0100: { /* VM_KEYDOWN */
            if (wp == (void *)0x1B) { /* VK_ESCAPE */
                g_running = 0;
                DestroyWindow(hwnd);
            }
            return 0;
        }
        case 0x0201: { /* WM_LBUTTONDOWN */
            unsigned char *lp_char = (unsigned char *)&lp;
            mouse_x_click = (short)(lp_char[0] | (lp_char[1] << 8));
            mouse_y_click = (short)(lp_char[2] | (lp_char[3] << 8));

            return 0;
        }
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
}

void gfx_clear() {
    mem_set(frame_buffer,0,4*SCREEN_W*SCREEN_H);
}

/* init/shutdown */
int gfx_init(const char *title) {
    struct wind_class wind_class_inst;
    struct rect window_rect;
    void *bits;
    union { WNDPROC fn;void *ptr; } proc_cast;

    mem_set(&wind_class_inst,0,sizeof(struct wind_class));
    wind_class_inst.cb_size=sizeof(struct wind_class);
    wind_class_inst.style=0x0020; /* CS_OWNDC */
    proc_cast.fn=wnd_proc;
    wind_class_inst.lpfn_wnd_proc=proc_cast.ptr;
    wind_class_inst.h_instance=GetModuleHandleA(0);
    wind_class_inst.h_cursor=LoadCursorA(0,((const char *)32512)); /* IDC_ARROW */
    wind_class_inst.lpsz_class_name="GfxWnd";
    RegisterClassExA(&wind_class_inst);

    window_rect.left=0;window_rect.top=0;window_rect.right=SCREEN_W;window_rect.bottom=SCREEN_H;
    AdjustWindowRect(&window_rect,0x00CF0000,0); /* WS_OVERLAPPEDWINDOW */

    g_hwnd=CreateWindowExA(
        0,"GfxWnd",title,
        0x10CF0000,((int)0x80000000),((int)0x80000000), /* WS_OVERLAPPEDWINDOW&WS_VISIBLE, CW_USEDEFAULT */
        window_rect.right-window_rect.left,window_rect.bottom-window_rect.top,
        0, 0, GetModuleHandleA(0), 0
    );
    if (!g_hwnd) { return 0; }

    g_hdc=GetDC(g_hwnd);
    g_memdc=CreateCompatibleDC(g_hdc);

    mem_set(&g_bmi,0,sizeof(g_bmi));
    g_bmi.bmi_header.bi_size=sizeof(struct bitmap_info_header);
    g_bmi.bmi_header.bi_width=SCREEN_W;
    g_bmi.bmi_header.bi_height=-SCREEN_H;
    g_bmi.bmi_header.bi_planes=1;
    g_bmi.bmi_header.bi_bit_count=32;
    g_bmi.bmi_header.bi_compression=0;

    bits=0;
    g_hbm=CreateDIBSection(g_memdc,&g_bmi,0,&bits,0,0);
    if (!g_hbm) { return 0; }

    SelectObject(g_memdc,g_hbm);
    frame_buffer=(unsigned int *)bits;

    gfx_clear();
    return 1;
}

void gfx_shutdown(void) {
    if (g_hbm) { DeleteObject(g_hbm); }
    if (g_memdc) { DeleteDC(g_memdc); }
    if (g_hdc) { ReleaseDC(g_hwnd,g_hdc); }
}

int gfx_present(void) {
    struct winuser_thread_msg msg;
    while (PeekMessageA(&msg,0,0,0,0x0001)) { /* PM_REMOVE */
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    BitBlt(g_hdc,0,0,SCREEN_W,SCREEN_H,g_memdc,0,0,0x00CC0020); /* SRCCOPY */
    return g_running;
}

void gfx_put_pixel(int x,int y,unsigned int color) {
    frame_buffer[y*SCREEN_W+x]=color;
}

void gfx_hline(int x_0,int x_1,int y,unsigned int color) {
    unsigned int *pixel;
    int pixel_iter;
    if ((unsigned int)y>=SCREEN_H) { return; }
    if (x_0<0) { x_0=0; }
    if (x_1>=SCREEN_W) { x_1=SCREEN_W-1; }
    pixel=frame_buffer+y*SCREEN_W+x_0;
    pixel_iter=x_1-x_0+1;
    while (pixel_iter--) { *pixel++=color; }
}

void gfx_vline(int x,int y_0,int y_1,unsigned int color) {
    unsigned int *pixel;
    int pixel_iter;
    if ((unsigned int)x >= SCREEN_W) { return; }
    if (y_0<0) { y_0=0; }
    if (y_1>=SCREEN_H) { y_1=SCREEN_H-1; }
    pixel=frame_buffer+y_0*SCREEN_W+x;
    pixel_iter=y_1-y_0+1;
    while (pixel_iter--) { *pixel=color;pixel+=SCREEN_W; }
}

/* Bresenham's line algorithm */
void gfx_line(int x_0,int y_0,int x_1,int y_1,unsigned int color) {
    int dist_x=+abs_val(x_1-x_0),dir_x=x_0<x_1?1:-1;
    int dist_y=-abs_val(y_1-y_0),dir_y=y_0<y_1?1:-1;
    int double_acc_err,acc_err=dist_x+dist_y;
    while (1) {
        gfx_put_pixel(x_0,y_0,color);
        if (x_0==x_1&&y_0==y_1) { break; }
        double_acc_err=2*acc_err;
        if (double_acc_err>= dist_y) { acc_err+=dist_y;x_0+=dir_x; }
        if (double_acc_err<= dist_x) { acc_err+=dist_x;y_0+=dir_y; }
    }
}

void gfx_rect(int left_x,int top_y,int width,int height,unsigned int color) {
    gfx_hline(left_x,left_x+width-1,top_y,color); /* top */
    gfx_hline(left_x,left_x+width-1,top_y+height-1,color); /* bottom */
    gfx_vline(left_x,top_y,top_y+height-1,color); /* left */
    gfx_vline(left_x+width-1,top_y,top_y+height-1,color); /* right */
}

int click_in_rect(int left_x,int top_y,int width,int height) {
    if(mouse_x_click>left_x && mouse_x_click<left_x+width &&
       mouse_y_click>top_y && mouse_y_click <top_y+height) {
        return 1;
    }
    return 0;
}

void gfx_rect_fill(int left_x,int top_y,int width,int height,unsigned int color) {
    int row;
    for (row=top_y;row<top_y+height;row++) {
        gfx_hline(left_x,left_x+width-1,row,color);
    }
}

void gfx_circle(int center_x,int center_y,int radius,unsigned int color) {
    int x_iter=0,y_iter=radius,midpoint_outside_circle=1-radius;
    while (x_iter<=y_iter) {
        gfx_put_pixel(center_x+x_iter,center_y+y_iter,color); /* bottom bottom right 8th */
        gfx_put_pixel(center_x-x_iter,center_y+y_iter,color); /* bottom bottom left 8th */
        gfx_put_pixel(center_x+x_iter,center_y-y_iter,color); /* top top right 8th */
        gfx_put_pixel(center_x-x_iter,center_y-y_iter,color); /* top top left 8th */
        gfx_put_pixel(center_x+y_iter,center_y+x_iter,color); /* bottom right right 8th */
        gfx_put_pixel(center_x-y_iter,center_y+x_iter,color); /* bottom left left 8th */
        gfx_put_pixel(center_x+y_iter,center_y-x_iter,color); /* top right right 8th */
        gfx_put_pixel(center_x-y_iter,center_y-x_iter,color); /* top left left 8th */
        if (midpoint_outside_circle<0) {
            midpoint_outside_circle+=2*x_iter+3;
        } else {
            midpoint_outside_circle+=2*(x_iter-y_iter)+5;y_iter--;
        }
        x_iter++;
    }
}

void gfx_circle_fill(int center_x,int center_y,int radius,unsigned int color) {
    int x_iter=0,y_iter=radius,midpoint_outside_circle=1-radius;
    while (x_iter<=y_iter) {
        gfx_hline(center_x-x_iter,center_x+x_iter,center_y+y_iter,color); /* bottom 4th */
        gfx_hline(center_x-x_iter,center_x+x_iter,center_y-y_iter,color); /* top 4th */
        gfx_hline(center_x-y_iter,center_x+y_iter,center_y+x_iter,color); /* center bottom 4th */
        gfx_hline(center_x-y_iter,center_x+y_iter,center_y-x_iter,color); /* center top 4th */
        if (midpoint_outside_circle<0) {
            midpoint_outside_circle+=2*x_iter+3;
        } else {
            midpoint_outside_circle+=2*(x_iter-y_iter)+5;y_iter--;
        }
        x_iter++;
    }
}

void gfx_draw_char(int char_x,int char_y,char char_in,unsigned int color) {
    int x_iter,y_iter,char_index=(unsigned char)char_in-32;
    unsigned char char_bitmap;
    if (char_index<0||char_index>95) { return; }
    for (x_iter=0;x_iter<8;x_iter++) {
        char_bitmap=gfx_font[char_index][x_iter];
        for (y_iter=0;y_iter<8;y_iter++) {
            if (char_bitmap&(0x80>>y_iter)) {
                gfx_put_pixel(char_x+y_iter,char_y+x_iter,color);
            }
        }
    }
}

void gfx_draw_string(int char_x,int char_y,const char *string,unsigned int color) {
    while (*string) {
        if (*string=='\n') {
            char_x=0;char_y+=8;
        } else {
            gfx_draw_char(char_x,char_y,*string,color);
            if ((char_x+=8)+8>SCREEN_W) {
                char_x=0;char_y+=8;
            }
        }
        string++;
    }
}

#endif
