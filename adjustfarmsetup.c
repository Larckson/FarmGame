#ifndef ADJUSTFARMSETUP
#define ADJUSTFARMSETUP

#include "initfarmsetup.c"

extern unsigned long random(void);

void update_crop_prices(struct crop* crops) {
    struct crop *crop_iter=crops;
    while (crop_iter!=NULL) {
        if (crop_iter->price<10) {
            crop_iter->price+=random()%10;
        } else if (crop_iter->price>100) {
            crop_iter->price-=random()%10;
        } else {
            crop_iter->price+=(random()%21)-10;
        }
        crop_iter=crop_iter->next_crop;
    }

    /* --- PRINT NEW PRICE TABLE --- */
    /* print crop names */
    printf("Crop Names:");
    crop_iter=crops;
    while (crop_iter!=NULL) {
        printf("%-10s",crop_iter->name);
        crop_iter=crop_iter->next_crop;
    }
    printf("\n           ");
    /* print crop prices */
    crop_iter=crops;
    while (crop_iter!=NULL) {
        printf("$%03d      ",crop_iter->price);
        crop_iter=crop_iter->next_crop;
    }
    printf("\nAdds:       ");
    /* print mineral adds */
    crop_iter=crops;
    while (crop_iter!=NULL) {
        printf("^%-2s       ",mineral_names[crop_iter->mineral_add]);
        crop_iter=crop_iter->next_crop;
    }
    printf("\nDepletes:   ");
    /* print mineral removals */
    crop_iter=crops;
    while (crop_iter!=NULL) {
        printf("v%-2s       ",mineral_names[crop_iter->mineral_del]);
        crop_iter=crop_iter->next_crop;
    }
    printf("\n\n");
}

int farm_growth_effects(struct farm* farms,struct crop* crops) {
    int i,money_increase;
    struct farm *farm_iter=farms;
    struct crop *crop_iter;

    money_increase=0;
    while(farm_iter!=NULL) {
        crop_iter=crops;
        for(i=0;i<farm_iter->current_crop;i++) {
            crop_iter=crop_iter->next_crop;
        }
        printf("Farm %c profits from %s $%d\n",farm_iter->name,crop_iter->name,crop_iter->price);
        money_increase+=crop_iter->price;
        farm_iter->minerals[crop_iter->mineral_add]++;
        farm_iter->minerals[crop_iter->mineral_del]--;
        farm_iter=farm_iter->next_farm;
    }
    return money_increase;
}

void prompt_new_crops(struct farm* farms,struct crop* crops) {
    struct farm *farm_iter=farms;
    char buf[10];
    int num,crop_count=0,i;
    int valid_num;

    struct crop* crop_iter=crops;
    while(crop_iter->next_crop!=NULL) {
        crop_iter=crop_iter->next_crop;
        crop_count++;
    }

    while (farm_iter!=NULL) {
        valid_num=0;
        while (!valid_num) {
            printf("What crop to grow on farm %c: ",farm_iter->name);

            fgets(buf, sizeof(buf), stdin);

            if (sscanf(buf, "%d", &num)!=1) {
                printf("Not a number. Try again.\n");
                continue;
            }
            if (num<0) {
                printf("Num less than 0, not valid.\n");
                continue;
            }
            if (num>crop_count) {
                printf("Num greater than crop count, not valid.\n");
                continue;
            }

            crop_iter=crops;
            for (i=0;i<num;i++) {
                crop_iter=crop_iter->next_crop;
            }
            if (farm_iter->minerals[crop_iter->mineral_del]==0) {
                printf("Not enough minerals to grow crop.\n");
                continue;
            }

            valid_num=1;
        }
        farm_iter->current_crop=num;
        farm_iter=farm_iter->next_farm;
    }
}

void print_farm_minerals(struct farm* farms) {
    int mineral_n;
    struct farm *farm_iter=farms;

    printf("Minerals: ");
    for (mineral_n=0;mineral_n<mineral_count;mineral_n++) {
        printf(" %4s",mineral_names[mineral_n]);
    }
    printf("\n");
    while (farm_iter!=NULL) {
        printf("Farm%c:     ",farm_iter->name);
        for (mineral_n=0;mineral_n<mineral_count;mineral_n++) {
            printf(" %2d0%%",farm_iter->minerals[mineral_n]);
        }
        farm_iter=farm_iter->next_farm;
        printf("\n");
    }
}

int expenses_effects(struct farm* farms) {
    struct farm *farm_iter=farms;
    int cost_acc=0;
    while (farm_iter!=NULL) {
        printf("Farm %c expenses: $10\n", farm_iter->name);
        cost_acc+=10;
        farm_iter=farm_iter->next_farm;
    }
    return cost_acc;
}

void purchase_items(struct farm** farms,int* money) {
    char buf[10];
    int num;
    int valid_num=0;
    printf("Money: $%d\n",*money);

    while (!valid_num) {
        printf("0:Do Nothing, 1:Purchase Farm(-$50), 2:Sell Farm(+$50)\n");
        fgets(buf, sizeof(buf), stdin);

        if (sscanf(buf, "%d", &num)!=1) {
            printf("Not a number. Try again.\n");
            continue;
        }
        if (num<0) {
            printf("Num less than 0, not valid.\n");
            continue;
        }
        if (num>2) {
            printf("Num too large, not valid.\n");
            continue;
        }
        switch (num) {
            case 0:
                valid_num=1;
                break;
            case 1:
                if(*money<50) {
                    printf("Do not have enough money ($50).\n");
                    continue;
                }
                *farms=add_farm(*farms);
                *money-=50;
                valid_num=1;
                printf("Farm Purchased -$50\n");
                printf("Money after purchase: %d\n", *money);
                break;
            case 2:
                if((*farms)->next_farm==NULL) {
                    printf("You only have one farm, there are no excess to sell.\n");
                    continue;
                }
                /* A little risky, relying on values in freed memory, but I live life on the edge */
                free_c(*farms);
                *farms=(*farms)->next_farm;
                *money+=50;
                valid_num=1;
                printf("Farm Sold +$50\n");
                break;
            default:
                printf("How did we get here");
                break;
        }
    }
}

#endif
