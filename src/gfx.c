#ifndef GFX
#define GFX

#include "gfxutils.c"

void * __stdcall CreateThread(void *, unsigned long, unsigned long (__stdcall *)(void *), void *, unsigned long, unsigned long *);
void __stdcall WaitForSingleObject(void *, unsigned long);
void __stdcall TerminateThread(void *, unsigned long);

int but_pos[3][4];
int but_count;

void gui_input_detect_loop(unsigned int* ans) {
    int button_iter;
    if (!gfx_present()) { return; }

    if (mouse_x_click==0 && mouse_y_click==0) { return; }

    for (button_iter=0;button_iter<but_count;button_iter++) {
        if (click_in_rect(but_pos[button_iter][0],but_pos[button_iter][1],but_pos[button_iter][2],but_pos[button_iter][3])) {
            *ans = button_iter+1;
            mouse_x_click=mouse_y_click=0;
            return;
        }
    }

    mouse_x_click=mouse_y_click=0;
    return;
}

void gui_purchase_items_setup() {
    if (!gfx_present()) { return; }
    gfx_clear(BLACK);

    but_pos[0][0]=50;but_pos[0][1]=50;but_pos[0][2]=200;but_pos[0][3]=40;
    gfx_rect_fill(but_pos[0][0],but_pos[0][1],but_pos[0][2],but_pos[0][3],BLUE);
    gfx_rect(but_pos[0][0],but_pos[0][1],but_pos[0][2],but_pos[0][3],WHITE);
    gfx_draw_string(but_pos[0][0]+10,but_pos[0][1]+10, "1: Do Nothing", WHITE);

    but_pos[1][0]=50;but_pos[1][1]=100;but_pos[1][2]=200;but_pos[1][3]=40;
    gfx_rect_fill(but_pos[1][0],but_pos[1][1],but_pos[1][2],but_pos[1][3],BLUE);
    gfx_rect(but_pos[1][0],but_pos[1][1],but_pos[1][2],but_pos[1][3],WHITE);
    gfx_draw_string(but_pos[1][0]+10,but_pos[1][1]+10, "2: Buy Farm (-$50)", WHITE);

    but_pos[2][0]=50;but_pos[2][1]=150;but_pos[2][2]=200;but_pos[2][3]=40;
    gfx_rect_fill(but_pos[2][0],but_pos[2][1],but_pos[2][2],but_pos[2][3],BLUE);
    gfx_rect(but_pos[2][0],but_pos[2][1],but_pos[2][2],but_pos[2][3],WHITE);
    gfx_draw_string(but_pos[2][0]+10,but_pos[2][1]+10, "3: Sell Farm (+$50)", WHITE);

    but_count=3;
}

#endif
