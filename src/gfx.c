#ifndef GFX
#define GFX

extern void int_to_str(int num, char* buf);

#include "gfxutils.c"
#include "initfarmsetup.c"

void * __stdcall CreateThread(void *, unsigned long, unsigned long (__stdcall *)(void *), void *, unsigned long, unsigned long *);
void __stdcall WaitForSingleObject(void *, unsigned long);
void __stdcall TerminateThread(void *, unsigned long);

struct button {
    int left_x,top_y,right_x,bot_y;
    struct button* next_button;
    int user_input;
};

struct button* but_iter = NULL; /* circular linked list */

static unsigned long __stdcall button_detect_async(void* arg) {
    int *ans = (int *)arg;
    if (but_iter == NULL) { return 0; } /* they closed the GUI */
    while (1) {
        if (click_x>but_iter->left_x&&click_x<but_iter->right_x&&click_y>but_iter->top_y&&click_y<but_iter->bot_y) {
            print_int(but_iter->user_input);
            print_text("\n");
            *ans = but_iter->user_input;
            click_x=click_y=0;
        }
        but_iter = but_iter->next_button;
    }
}

void add_button(int set_left_x,int set_top_y,int set_width,int set_height,char* set_text,int set_user_input,int is_char) {
    int text_pos;char num_buf[10];
    struct button* prev_but_iter = but_iter;

    but_iter = mem_alloc(sizeof(struct button));
    if (prev_but_iter == NULL) {
        but_iter->next_button = but_iter; /* circles back upon itself */
    } else {
        /* the last node will always point at the first node.
        So make the new last node point at the node the old last node used to point at (the 1st node) */
        but_iter->next_button = prev_but_iter->next_button;
        prev_but_iter->next_button = but_iter;
    }
    but_iter->user_input=set_user_input;
    but_iter->left_x=set_left_x;
    but_iter->top_y=set_top_y;
    but_iter->right_x=set_left_x+set_width;
    but_iter->bot_y=set_top_y+set_height;

    if (is_char) {
        gfx_rect_fill(set_left_x,set_top_y,set_width,set_height,RED);
        text_pos=gfx_draw_char(set_left_x+10,set_top_y+10, set_user_input, WHITE);
    } else {
        gfx_rect_fill(set_left_x,set_top_y,set_width,set_height,BLUE);
        int_to_str(set_user_input, num_buf);
        text_pos=gfx_draw_string(set_left_x+10,set_top_y+10, num_buf, WHITE);
    }
    gfx_rect(set_left_x,set_top_y,set_width,set_height,WHITE);
    text_pos=gfx_draw_char(text_pos,set_top_y+10, ':', WHITE);
    text_pos=gfx_draw_string(text_pos,set_top_y+10, set_text, WHITE);
}

void free_buttons() {
    struct button *but_head = but_iter;
    struct button *next;
    if (but_iter == NULL) { return; } /* they closed the GUI */
    do {
        next = but_iter->next_button;
        mem_free(but_iter);
        but_iter = next;
    } while (but_iter != but_head);
    but_iter = NULL;
}

void gui_basic_utils(int money, int year) {
    char num_buf[10];int text_pos=5;

    if (!gfx_present()) { return; }
    gfx_clear(0);

    int_to_str(year, num_buf);
    text_pos=gfx_draw_string(text_pos,5,"Year:",WHITE);
    text_pos=gfx_draw_string(text_pos,5,num_buf,WHITE);
    text_pos=gfx_draw_string(text_pos,5,"  ",WHITE);

    int_to_str(money, num_buf);
    text_pos=gfx_draw_string(text_pos,5,"Money:$",WHITE);
    text_pos=gfx_draw_string(text_pos,5,num_buf,WHITE);
}

void gui_farm_minerals(struct farm* farm_iter, struct crop* crop_iter,char farm_select,char farm_view) {
    char full_farm_name[] = "Farm _";
    int button_x=20,n,bar_height;
    char num_buf[10];

    if (!gfx_present()) { return; }
    gfx_clear(15);

    /* border around farm view window and buttons on top */
    gfx_rect(button_x,70,700,500,WHITE);
    while (farm_iter!=NULL) {
        if (farm_iter->name == farm_view) {
            /* bars showing minerals on farm */
            for (n=0;n<MINERALCOUNT;n++) {
                bar_height=15*(farm_iter->minerals[n]);
                gfx_rect_hatch(n*20+80,250-bar_height,10,bar_height,GREEN,4);
                gfx_rect(n*20+80,250-bar_height,10,bar_height,GREEN);
                gfx_draw_string(n*20+80,252,mineral_names[n],WHITE);
            }

            /* outer border and tick marks */
            gfx_draw_string(50,75,"Minerals",WHITE);
            gfx_rect(50,85,MINERALCOUNT*20+30,165,WHITE);
            for (n=1;n<=5;n++) {
                gfx_hline(50,60,250-30*n,WHITE);
                int_to_str(n*20, num_buf);
                gfx_draw_char(gfx_draw_string(50,240-30*n,num_buf,WHITE),240-30*n,'%',WHITE);
            }

            /* Crop Info Table */
            n=0;
            while (crop_iter!=NULL) {
                gfx_draw_string(300,90,"Choose to Plant:",WHITE);
                add_button(300,100+40*n,100,20,crop_iter->name,n,0);

                gfx_draw_string(450,90,"Add:",WHITE);
                gfx_draw_string(gfx_draw_char(450,100+40*n,'^', WHITE)
                    ,100+40*n,mineral_names[crop_iter->mineral_add],WHITE);

                gfx_draw_string(500,90,"Del:",WHITE);
                gfx_draw_string(gfx_draw_char(500,100+40*n,'v', WHITE)
                    ,100+40*n,mineral_names[crop_iter->mineral_del],WHITE);

                gfx_draw_string(550,90,"Price:",WHITE);
                int_to_str(crop_iter->price, num_buf);
                gfx_draw_string(gfx_draw_char(550,100+40*n,'$', WHITE)
                    ,100+40*n,num_buf,WHITE);

                crop_iter=crop_iter->next_crop;
                n++;
            }
        }

        full_farm_name[5]=farm_iter->name;
        add_button(button_x,40,100,30,full_farm_name,farm_iter->name,1);

        farm_iter=farm_iter->next_farm;
        button_x+=100;
    }
}

void gui_purchase_items_setup() {
    if (!gfx_present()) { return; }
    gfx_clear(15);

    add_button(50, 50,200,40,"Do Nothing",1,0);
    add_button(50,100,200,40,"Buy Farm (-$50)",2,0);
    add_button(50,150,200,40,"Sell Farm (+$50)",3,0);
}

#endif
