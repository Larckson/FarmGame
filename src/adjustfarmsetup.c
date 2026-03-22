#ifndef ADJUSTFARMSETUP
#define ADJUSTFARMSETUP

extern unsigned long get_rand(void);
extern void read_text(char* buf, int size);
extern void print_int(int num);
extern void print_char(char* c);
extern int text_to_int(char* buf, int* out);

#include "gfx.c"
#include "initfarmsetup.c"

void update_crop_prices(struct crop* crops) {
    struct crop *crop_iter=crops;
    int str_len;
    while (crop_iter!=NULL) {
        if (crop_iter->price<10) {
            crop_iter->price+=get_rand()%10;
        } else if (crop_iter->price>100) {
            crop_iter->price-=get_rand()%10;
        } else {
            crop_iter->price+=(get_rand()%21)-10;
        }
        crop_iter=crop_iter->next_crop;
    }

    /* --- PRINT NEW PRICE TABLE --- */
    /* print crop names */
    print_text("Crop Names:");
    crop_iter=crops;
    while (crop_iter!=NULL) {
        int str_len=print_text(crop_iter->name);
        while (str_len++ < 9) print_text(" ");
        crop_iter=crop_iter->next_crop;
    }
    print_text("\n           ");
    /* print crop prices */
    crop_iter=crops;
    while (crop_iter!=NULL) {
        print_text("$");
        print_int(crop_iter->price);
        print_text("      ");
        crop_iter=crop_iter->next_crop;
    }
    print_text("\nAdds:      ");
    /* print mineral adds */
    crop_iter=crops;
    while (crop_iter!=NULL) {
        print_text("^");
        str_len=print_text(mineral_names[crop_iter->mineral_add]);
        while (str_len++ < 8) print_text(" ");
        crop_iter=crop_iter->next_crop;
    }
    print_text("\nDepletes:  ");
    /* print mineral removals */
    crop_iter=crops;
    while (crop_iter!=NULL) {
        print_text("v");
        str_len=print_text(mineral_names[crop_iter->mineral_del]);
        while (str_len++ < 8) print_text(" ");
        crop_iter=crop_iter->next_crop;
    }
    print_text("\n\n");
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
        print_text("Farm ");print_char(&farm_iter->name);
        print_text(" profits from ");print_text(crop_iter->name);print_text(" $");
        print_int(crop_iter->price);print_text("\n");
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
            print_text("What crop to grow on farm ");
            print_char(&farm_iter->name);
            print_text(": ");
            read_text(buf, sizeof(buf));

            if (text_to_int(buf, &num)!=1) {
                print_text("Not a number. Try again.\n");
                continue;
            }
            if (num<0) {
                print_text("Num less than 0, not valid.\n");
                continue;
            }
            if (num>crop_count) {
                print_text("Num greater than crop count, not valid.\n");
                continue;
            }

            crop_iter=crops;
            for (i=0;i<num;i++) {
                crop_iter=crop_iter->next_crop;
            }
            if (farm_iter->minerals[crop_iter->mineral_del]==0) {
                print_text("Not enough minerals to grow crop.\n");
                continue;
            }

            valid_num=1;
        }
        farm_iter->current_crop=num;
        farm_iter=farm_iter->next_farm;
    }
}

void print_farm_minerals(struct farm* farms) {
    int mineral_n,str_len;
    struct farm *farm_iter=farms;

    print_text("Minerals:    ");
    for (mineral_n=0;mineral_n<mineral_count;mineral_n++) {
        str_len=print_text(mineral_names[mineral_n]);
        while (str_len++ < 7) print_text(" ");
    }
    print_text("\n");
    while (farm_iter!=NULL) {
        print_text("Farm");print_char(&farm_iter->name);print_text(":     ");
        for (mineral_n=0;mineral_n<mineral_count;mineral_n++) {
            print_text("  ");print_int(farm_iter->minerals[mineral_n]);print_text("0%  ");
        }
        farm_iter=farm_iter->next_farm;
        print_text("\n");
    }
}

int expenses_effects(struct farm* farms) {
    struct farm *farm_iter=farms;
    int cost_acc=0;
    while (farm_iter!=NULL) {
        print_text("Farm ");print_char(&farm_iter->name);print_text(" expenses: $10\n");
        cost_acc+=10;
        farm_iter=farm_iter->next_farm;
    }
    return cost_acc;
}

static int has_newline(char *buf, int size) {
    int i;
    for (i=0;i<size;i++) {
        if (buf[i]=='\n') { return 1; }
    }
    return 0;
}

static unsigned long __stdcall prompt_num_async(void* arg) {
    int *ans = (int *)arg;
    int num,text_filled_buffer;
    char buf[10];
    while (1) {
        while (*ans!=0) {}
        read_text(buf, sizeof(buf));
        text_filled_buffer=has_newline(buf,sizeof(buf));

        if(!text_filled_buffer) {
            /* If it filled the buffer, the next ReadConsoleA will contain the rest of the text, so we have to drain it */
            do { read_text(buf,sizeof(buf)); } while(!has_newline(buf,sizeof(buf)));
            print_text("Input too many chars. Try again\n");
            continue;
        }

        if (text_to_int(buf, &num)!=1) {
            print_text("Not a number. Try again.\n");
            continue;
        }
        if (num==0) {
            print_text("Num is 0, not valid.\n");
            continue;
        }
        if (num<0) {
            print_text("Num less than 0, not valid.\n");
            continue;
        }
        *ans=num;
    }
    return 0;
}

void purchase_items(struct farm** farms,int* money) {
    void *prompt_thread;
    int ans=0;
    char* base_prompt = "0:Do Nothing, 1:Purchase Farm(-$50), 2:Sell Farm(+$50)\n";
    print_text("Money: $");print_int(*money);print_text("\n");

    purchase_items_gui_setup();

    print_text(base_prompt);
    prompt_thread = CreateThread(0, 0, prompt_num_async, &ans, 0, 0);

    while (ans==0 && gfx_present()) {
        purchase_items_gui_loop();

        switch (ans) {
            case 0: { break; }
            case 1: {
                if(*money<50) {
                    print_text("Do not have enough money ($50).\n");
                    ans=0;
                    print_text(base_prompt);
                    continue;
                }
                *farms=add_farm(*farms);
                *money-=50;
                print_text("Farm Purchased -$50\n");
                print_text("Money after purchase: ");print_int(*money);print_text("\n");
                break;
            }
            case 2: {
                if((*farms)->next_farm==NULL) {
                    print_text("You only have one farm, there are no excess to sell.\n");
                    ans=0;
                    print_text(base_prompt);
                    continue;
                }
                mem_free(*farms);
                *farms=(*farms)->next_farm;
                *money+=50;
                print_text("Farm Sold +$50\n");
                break;
            }
            default: {
                print_text("Num too large.\n");
                ans=0;
                print_text(base_prompt);
                continue;
            }
        }
    }

    TerminateThread(prompt_thread, 0);
}

#endif
