#ifndef ADJUSTFARMSETUP
#define ADJUSTFARMSETUP

extern unsigned long get_rand(void);
extern void read_text(char* buf,int size);
extern int print_int(int num);
extern int print_char(char* c);
extern int text_to_int(char* buf,int* out);
extern int has_newline(char *buf,int size);

#include "gfx.c"
#include "initfarmsetup.c"

void update_crop_prices(struct crop* crops) {
    struct crop *crop_iter=crops;
    int str_len,i;
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
    print_text("Crop ID:   ");
    crop_iter=crops;
    i=1;
    while (crop_iter!=NULL) {
        str_len=print_int(i);
        while (str_len++ < 8) print_text(" ");
        crop_iter=crop_iter->next_crop;
        i++;
    }

    print_text("\nCrop Names:");
    crop_iter=crops;
    while (crop_iter!=NULL) {
        str_len=print_text(crop_iter->name);
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

static unsigned long __stdcall prompt_num_async(void* arg) {
    int *verified_ans=(int *)arg;
    int num_ans,text_filled_buffer;
    char buf[10];
    while (1) {
        while (*verified_ans!=0) { }
        read_text(buf,sizeof(buf));
        /* More validation should be done in the receiving function, based on variable specific inputs.
        Basic validation is done here though, to make sure we are returning a valid unsigned int and that it's the one the user entered. */
        text_filled_buffer=has_newline(buf,sizeof(buf));

        if(!text_filled_buffer) {
            /* If user input overflowed the buffer, subsequent ReadConsoleAs will contain the rest of the text, so we have to drain it */
            do { read_text(buf,sizeof(buf)); } while(!has_newline(buf,sizeof(buf)));
            print_text("Input too many chars. Try again\n");
            continue;
        }

        if (text_to_int(buf,&num_ans)!=1) {
            print_text("Not a number. Try again.\n");
            continue;
        }
        if (num_ans==0) {
            print_text("Num is 0, not valid.\n");
            continue;
        }
        if (num_ans<0) {
            print_text("Num less than 0, not valid.\n");
            continue;
        }
        *verified_ans=num_ans;
    }
    return 0;
}

void prompt_new_crops(struct farm* farms,struct crop* crops) {
    void *prompt_thread,*button_thread;
    struct farm *farm_iter=farms;
    int i,ans=0;
    char base_prompt[]="What crop to grow on farm _ (Crop ID): ";

    struct crop* crop_iter=crops;

    while (farm_iter!=NULL) {
        ans=0;
        base_prompt[26]=farm_iter->name;
        print_text(base_prompt);

        gui_farm_minerals(farms,crops,farm_iter->name,farm_iter->name);

        prompt_thread=CreateThread(0,0,prompt_num_async,&ans,0,0);
        button_thread=CreateThread(0,0,button_detect_async,&ans,0,0);

        while (ans==0) {
            gfx_present();
            if (ans == 0) { continue; } /* skip mineral check if crop was invalid */

            crop_iter=crops;
            if (ans<0) { /* GUI Selection to look at other farm info, but no action */
                gui_farm_minerals(farms,crops,farm_iter->name,-ans);
                ans=0;
                continue;
            }
            for (i=1;i<ans;i++) {
                crop_iter=crop_iter->next_crop;
                if (crop_iter==NULL) {
                    feedback_update("Num greater than crop count, not valid.\n");
                    ans=0;
                    print_text(base_prompt);
                    break;
                }
            }
            if (farm_iter->minerals[crop_iter->mineral_del]==0) {
                feedback_update("Not enough minerals to grow crop.\n");
                ans=0;
                print_text(base_prompt);
                continue;
            }
        }
        farm_iter->current_crop=ans-1;
        farm_iter=farm_iter->next_farm;

        TerminateThread(prompt_thread,0);
        TerminateThread(button_thread,0);
        free_buttons();
    }
}

void print_farm_minerals(struct farm* farms) {
    int mineral_n,str_len;
    struct farm *farm_iter=farms;

    print_text("Minerals:    ");
    for (mineral_n=0;mineral_n<MINERALCOUNT;mineral_n++) {
        str_len=print_text(mineral_names[mineral_n]);
        while (str_len++ < 7) print_text(" ");
    }
    print_text("\n");
    while (farm_iter!=NULL) {
        print_text("Farm");print_char(&farm_iter->name);print_text(":     ");
        for (mineral_n=0;mineral_n<MINERALCOUNT;mineral_n++) {
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

void purchase_items(struct farm** farms,int* money) {
    void *prompt_thread,*button_thread;
    int ans=0;
    char* base_prompt="1-Do Nothing, 2-Purchase Farm(-$50), 3-Sell Farm(+$50). What do: ";
    print_text("Money: $");print_int(*money);print_text("\n");

    gui_purchase_items_setup();

    print_text(base_prompt);
    prompt_thread=CreateThread(0,0,prompt_num_async,&ans,0,0);
    button_thread=CreateThread(0,0,button_detect_async,&ans,0,0);

    while (ans==0) {
        gfx_present();

        switch (ans) {
            case 0: { break; } /* no answer given yet. Keep looping */
            case 1: { break; }
            case 2: {
                if(*money<50) {
                    feedback_update("Do not have enough money ($50).\n");
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
            case 3: {
                if((*farms)->next_farm==NULL) {
                    feedback_update("You only have one farm, there are no excess to sell.\n");
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
                feedback_update("Num too large.\n");
                ans=0;
                print_text(base_prompt);
                continue;
            }
        }
    }

    TerminateThread(prompt_thread,0);
    TerminateThread(button_thread,0);
    free_buttons();
}

#endif
