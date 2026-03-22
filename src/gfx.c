#ifndef GFX
#define GFX

#include "gfxutils.c"

void * __stdcall CreateThread(void *, unsigned long, unsigned long (__stdcall *)(void *), void *, unsigned long, unsigned long *);
void   __stdcall WaitForSingleObject(void *, unsigned long);
void __stdcall TerminateThread(void *, unsigned long);

void purchase_items_gui_loop() { }

void purchase_items_gui_setup() {
    gfx_clear(BLACK);

    gfx_rect_fill(50, 50, 200, 150, BLUE);
    gfx_rect(50, 50, 200, 150, WHITE);

    gfx_circle_fill(400, 300, 80, RED);
    gfx_circle(400, 300, 80, YELLOW);

    gfx_line(0, 0, SCREEN_W-1, SCREEN_H-1, GREEN);
    gfx_line(SCREEN_W-1, 0, 0, SCREEN_H-1, CYAN);

    gfx_hline(0, SCREEN_W-1, SCREEN_H/2, MAGENTA);
    gfx_vline(SCREEN_W/2, 0, SCREEN_H-1, MAGENTA);
    gfx_draw_string(10, 10, "abcdefghijklmnopqrstuvwxyz", WHITE);
    gfx_draw_string(10, 20, "ABCDEFGHIJKLMNOPQSRTUVWXYZ", YELLOW);
    gfx_draw_char(400, 300, 'A', RED);

}

#endif
