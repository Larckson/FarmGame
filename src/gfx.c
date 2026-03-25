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
    if (but_iter == NULL) { return; } /* they closed the GUI */
    while (1) {
        if (click_x>but_iter->left_x&&click_x<but_iter->right_x&&click_y>but_iter->top_y&&click_y<but_iter->bot_y) {
            print_int(but_iter->user_input);
            print_text("\n");
            *ans = but_iter->user_input;
            click_x=click_y=0;
        }
        but_iter = but_iter->next_button;
    }
    return 1;
}

void add_button(int set_left_x,int set_top_y,int set_width,int set_height,char* set_text,int set_user_input) {
    int text_pos;char num_buf[12];
    struct button* prev_but_iter = but_iter;

    but_iter = mem_alloc(sizeof(struct button));
    if (prev_but_iter == NULL) {
        but_iter->next_button = but_iter;
    } else {
        but_iter->next_button = prev_but_iter->next_button;
        prev_but_iter->next_button = but_iter;
    }
    but_iter->user_input=set_user_input;
    but_iter->left_x=set_left_x;
    but_iter->top_y=set_top_y;
    but_iter->right_x=set_left_x+set_width;
    but_iter->bot_y=set_top_y+set_height;
    gfx_rect_fill(set_left_x,set_top_y,set_width,set_height,BLUE);
    gfx_rect(set_left_x,set_top_y,set_width,set_height,WHITE);

    int_to_str(set_user_input, num_buf);
    text_pos=gfx_draw_string(set_left_x+10,set_top_y+10, num_buf, WHITE);
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

void gui_purchase_items_setup() {
    if (!gfx_present()) { return; }
    gfx_clear(BLACK);

    add_button(50, 50,200,40,"Do Nothing",1);
    add_button(50,100,200,40,"Buy Farm (-$50)",2);
    add_button(50,150,200,40,"Sell Farm (+$50)",3);
}

void gui_prompt_new_crops_setup(struct crop* crops) {
    int button_y=50,crop_num=1;
    if (!gfx_present()) { return; }
    gfx_clear(BLACK);

    while (crops!=NULL) {
        add_button(50,button_y,200,40,crops->name,crop_num);

        crops=crops->next_crop;
        button_y+=50;crop_num++;
    }
}

#endif
