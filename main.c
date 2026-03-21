#include "gfxutils.c"

int main(void)
{
    if (!gfx_init("My Graphics")) return 1;

    gfx_clear(BLACK);

    gfx_rect_fill(50, 50, 200, 150, BLUE);
    gfx_rect(50, 50, 200, 150, WHITE);

    gfx_circle_fill(400, 300, 80, RED);
    gfx_circle(400, 300, 80, YELLOW);

    gfx_line(0, 0, SCREEN_W-1, SCREEN_H-1, GREEN);
    gfx_line(SCREEN_W-1, 0, 0, SCREEN_H-1, CYAN);

    gfx_hline(0, SCREEN_W-1, SCREEN_H/2, MAGENTA);
    gfx_vline(SCREEN_W/2, 0, SCREEN_H-1, MAGENTA);

    while (gfx_present()) {
    }

    gfx_shutdown();
    return 0;
}
