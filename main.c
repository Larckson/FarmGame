#include "adjustfarmsetup.c"

extern unsigned long print_time();
extern void srandom(unsigned long seed);

int main() {
    int year;
    int money=50;
    struct crop* crops=create_initial_crops();
    struct farm* farms=add_farm(NULL);
    srandom(print_time());

    for (year=1800;year<1900;year++) {
        printf("Year: %d\n",year);
        money+=farm_growth_effects(farms,crops);
        money-=expenses_effects(farms);
        purchase_items(&farms,&money);
        update_crop_prices(crops);
        print_farm_minerals(farms);
        prompt_new_crops(farms,crops);
        printf("-------------");
        printf("\033[2J\033[H");
    }

    return 0;
}
