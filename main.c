#include "adjustfarmsetup.c"
#include "gfxutils.c"

extern unsigned long get_time();
extern void set_rand(unsigned long seed);

int main() {
    int year;
    int money=50;
    struct crop* crops=create_initial_crops();
    struct farm* farms=add_farm(NULL);

    /* temp graphics test code */
    char buf[10];
    print_text("Enter y to do a graphics test");
    read_text(buf, sizeof(buf));
    if (buf[0]=='y') { graphics_test(); }
    /* temp graphics test code end */

    set_rand(get_time());

    for (year=1800;year<1900;year++) {
        print_text("Year: ");print_int(year);print_text("\n");
        money+=farm_growth_effects(farms,crops);
        money-=expenses_effects(farms);
        purchase_items(&farms,&money);
        update_crop_prices(crops);
        print_farm_minerals(farms);
        prompt_new_crops(farms,crops);
        print_text("-------------");
        print_text("\033[2J\033[H");
    }

    return 0;
}

int graphics_test() {
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
    gfx_draw_string(10, 10, "abcdefghijklmnopqrstuvwxyz", WHITE);
    gfx_draw_string(10, 20, "ABCDEFGHIJKLMNOPQSRTUVWXYZ", YELLOW);
    gfx_draw_char(400, 300, 'A', RED);

    while (gfx_present()) {}

    gfx_shutdown();
    return 0;
}
