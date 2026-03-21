#include "adjustfarmsetup.c"

extern unsigned long get_time();
extern void set_rand(unsigned long seed);

int main() {
    int year;
    int money=50;
    struct crop* crops=create_initial_crops();
    struct farm* farms=add_farm(NULL);
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
