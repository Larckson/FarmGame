#include "adjustfarmsetup.c"
extern unsigned long get_time();
extern void set_rand(unsigned long seed);

int main() {
    /* kljsdfs */
    int year,money=50,ans=5;
    CreateThread(0,0,prompt_num_async,&ans,0,0);
    struct crop* crops=create_initial_crops();
    struct farm* farms=add_farm(NULL);

    if (!gfx_init("My Graphics")) { return 1; }
    set_rand(get_time());

    for (year=1800;year<1900;year++) {
        print_text("Year: ");print_int(year);print_text("\n");
        money+=farm_growth_effects(farms,crops);
        money-=expenses_effects(farms);
        gui_basic_utils(money,year);
        purchase_items(&farms,&money,&ans);
        gui_basic_utils(money,year);
        update_crop_prices(crops);
        print_farm_minerals(farms);
        prompt_new_crops(farms,crops,&ans);
        print_text("-------------");
        print_text("\033[2J\033[H");
    }

    gfx_shutdown();
    return 0;
}
