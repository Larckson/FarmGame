#ifndef GFX
#define GFX

extern void int_to_str(int num,char* buf);

#ifdef _WIN32
    #include "gfxwindows.c"
#else
    #include "gfxlinux.c"
#endif
#include "initfarmsetup.c"

#ifdef _WIN32

    /* --- Windows thread API (manual declarations, no headers) --- */
    void * __stdcall CreateThread(void *,unsigned long,unsigned long(__stdcall *)(void *),void *,unsigned long,unsigned long *);
    void __stdcall WaitForSingleObject(void *,unsigned long);
    void __stdcall TerminateThread(void *,unsigned long);

#else

    /* --- Linux syscalls (no pthreads, no libc dependency required) --- */
    extern long clone(long (*fn)(void *),void *stack,int flags,void *arg);
    extern int tgkill(int tgid,int tid,int sig);
    extern int getpid(void);
    extern int gettid(void);

    #define STACK_SIZE 65536

    /* clone flags: thread-like behavior */
    #define CLONE_FLAGS (0x00000100 | 0x00000200 | 0x00000400)

    /* --- CreateThread replacement --- */
    static void *CreateThread(void *lpThreadAttributes,
                              unsigned long dwStackSize,
                              long (*lpStartAddress)(void *),
                              void *lpParameter,
                              unsigned long dwCreationFlags,
                              unsigned long *lpThreadId)
    {
        static char stack[STACK_SIZE];

        (void)lpThreadAttributes;
        (void)dwStackSize;
        (void)dwCreationFlags;

        void *tid = (void*)clone(lpStartAddress, stack + STACK_SIZE, CLONE_FLAGS, lpParameter);

        if (lpThreadId) {
            *lpThreadId = (unsigned long)tid;
        }

        return tid;
    }

    /* --- WaitForSingleObject (stub/no-op for now) --- */
    static void WaitForSingleObject(void *handle,unsigned long milliseconds)
    {
        (void)handle;
        (void)milliseconds;
        /* no-op (could be implemented with futex if needed) */
    }

    /* --- TerminateThread replacement --- */
    static void TerminateThread(void *thread,unsigned long exit_code)
    {
        (void)exit_code;
        tgkill(getpid(), (int)(long)thread, 9); /* SIGKILL */
    }

#endif

struct button {
    int left_x,top_y,right_x,bot_y;
    struct button* next_button;
    int user_input;
};

struct button* but_iter=NULL;

void gfx_put_pixel(int x,int y,unsigned int color) {
    frame_buffer[y*SCREENW+x]=color;
}

void gfx_hline(int x_0,int x_1,int y,unsigned int color) {
    unsigned int *pixel;
    int pixel_iter;
    if ((unsigned int)y>=SCREENH) { return; }
    if (x_0<0) { x_0=0; }
    if (x_1>=SCREENW) { x_1=SCREENW-1; }
    pixel=frame_buffer+y*SCREENW+x_0;
    pixel_iter=x_1-x_0+1;
    while (pixel_iter--) { *pixel++=color; }
}

void gfx_vline(int x,int y_0,int y_1,unsigned int color) {
    unsigned int *pixel;
    int pixel_iter;
    if ((unsigned int)x >= SCREENW) { return; }
    if (y_0<0) { y_0=0; }
    if (y_1>=SCREENH) { y_1=SCREENH-1; }
    pixel=frame_buffer+y_0*SCREENW+x;
    pixel_iter=y_1-y_0+1;
    while (pixel_iter--) { *pixel=color;pixel+=SCREENW; }
}

void gfx_rect(int left_x,int top_y,int width,int height,unsigned int color) {
    gfx_hline(left_x,left_x+width-1,top_y,color);
    gfx_hline(left_x,left_x+width-1,top_y+height-1,color);
    gfx_vline(left_x,top_y,top_y+height-1,color);
    gfx_vline(left_x+width-1,top_y,top_y+height-1,color);
}

void gfx_rect_fill(int left_x,int top_y,int width,int height,unsigned int color) {
    int row;
    for (row=top_y;row<top_y+height;row++) {
        gfx_hline(left_x,left_x+width-1,row,color);
    }
}

void gfx_rect_hatch(int left_x,int top_y,int width,int height,unsigned int color,int spacing) {
    int x_iter,y_iter;
    for (y_iter=0;y_iter<height;y_iter++) {
        for (x_iter=0;x_iter<width;x_iter++) {
            if (((x_iter+y_iter)%spacing) == 0) {
                gfx_put_pixel(left_x+x_iter,top_y+y_iter,color);
            }
        }
    }
}

int gfx_draw_char(int char_x,int char_y,char char_in,unsigned int color) {
    int x_iter,y_iter,char_index=(unsigned char)char_in-32;
    unsigned char char_bitmap;
    if (char_index<0||char_index>95) { return 0; }
    for (x_iter=0;x_iter<8;x_iter++) {
        char_bitmap=gfx_font[char_index][x_iter];
        for (y_iter=0;y_iter<8;y_iter++) {
            if (char_bitmap&(0x80>>y_iter)) {
                gfx_put_pixel(char_x+y_iter,char_y+x_iter,color);
            }
        }
    }
    return char_x+8;
}

int gfx_draw_string(int char_x,int char_y,const char *string,unsigned int color) {
    while (*string) {
        if (*string=='\n') {
            char_x=0;char_y+=8;
        } else {
            gfx_draw_char(char_x,char_y,*string,color);
            if ((char_x+=8)+8>SCREENW) {
                char_x=0;char_y+=8;
            }
        }
        string++;
    }
    return char_x;
}

#ifdef _WIN32
static unsigned long __stdcall button_detect_async(void* arg) {
#else
static long button_detect_async(void* arg) {
#endif
    int *ans=(int *)arg;
    if (but_iter==NULL) { return 0; }
    while (1) {
        if (click_x>but_iter->left_x&&click_x<but_iter->right_x&&click_y>but_iter->top_y&&click_y<but_iter->bot_y) {
            if (but_iter->user_input>=0) {
                print_int(but_iter->user_input);
                print_text("\n");
            }
            *ans=but_iter->user_input;
            click_x=click_y=0;
        }
        but_iter=but_iter->next_button;
    }
}

void add_button(int set_left_x,int set_top_y,int set_width,int set_height,char* set_text,int set_user_input,int is_char,int selected) {
    int text_pos;char num_buf[10];
    struct button* prev_but_iter=but_iter;

    but_iter=mem_alloc(sizeof(struct button));
    if (prev_but_iter==NULL) {
        but_iter->next_button=but_iter;
    } else {
        but_iter->next_button=prev_but_iter->next_button;
        prev_but_iter->next_button=but_iter;
    }
    but_iter->left_x=set_left_x;
    but_iter->top_y=set_top_y;
    but_iter->right_x=set_left_x+set_width;
    but_iter->bot_y=set_top_y+set_height;

    if (is_char) {
        but_iter->user_input=-set_user_input;
        gfx_rect_fill(set_left_x,set_top_y,set_width,set_height,RED);
        text_pos=gfx_draw_char(set_left_x+10,set_top_y+10,set_user_input,WHITE);
    } else {
        but_iter->user_input=set_user_input;
        gfx_rect_fill(set_left_x,set_top_y,set_width,set_height,BLUE);
        int_to_str(set_user_input,num_buf);
        text_pos=gfx_draw_string(set_left_x+10,set_top_y+10,num_buf,WHITE);
    }
    gfx_rect(set_left_x,set_top_y,set_width,set_height,selected?YELLOW:WHITE);
    text_pos=gfx_draw_char(text_pos,set_top_y+10,':',WHITE);
    text_pos=gfx_draw_string(text_pos,set_top_y+10,set_text,WHITE);
}

void free_buttons() {
    struct button *but_head=but_iter;
    struct button *next;
    if (but_iter==NULL) { return; }
    do {
        next=but_iter->next_button;
        mem_free(but_iter);
        but_iter=next;
    } while (but_iter!=but_head);
    but_iter=NULL;
}

void gui_basic_utils(int money,int year) {
    char num_buf[10];int text_pos=5;

    if (!gfx_present()) { return; }
    gfx_clear(0);

    int_to_str(year,num_buf);
    text_pos=gfx_draw_string(text_pos,5,"Year:",WHITE);
    text_pos=gfx_draw_string(text_pos,5,num_buf,WHITE);
    text_pos=gfx_draw_string(text_pos,5,"  ",WHITE);

    int_to_str(money,num_buf);
    text_pos=gfx_draw_string(text_pos,5,"Money:$",WHITE);
    text_pos=gfx_draw_string(text_pos,5,num_buf,WHITE);
}

void feedback_update(char* string) {
    print_text(string);
    if (!gfx_present()) { return; }
    gfx_clear(580);
    gfx_draw_string(gfx_draw_string(10,580,"Invalid Input:",RED),580,string,RED);
}

void gui_farm_minerals(struct farm* farm_iter,struct crop* crop_iter,char farm_select,char farm_view) {
    char full_farm_name[]="Farm _";
    int button_x=20,n,bar_height;
    char num_buf[10];

    if (!gfx_present()) { return; }
    gfx_clear(15);

    gfx_rect(button_x,70,700,500,WHITE);
    while (farm_iter!=NULL) {
        if (farm_iter->name == farm_view) {
            for (n=0;n<MINERALCOUNT;n++) {
                bar_height=15*(farm_iter->minerals[n]);
                gfx_rect_hatch(n*20+80,250-bar_height,10,bar_height,mineral_colors[n],4);
                gfx_rect(n*20+80,250-bar_height,10,bar_height,mineral_colors[n]);
                gfx_draw_string(n*20+80,252,mineral_names[n],mineral_colors[n]);
            }

            gfx_draw_string(50,75,"Minerals",WHITE);
            gfx_rect(50,85,MINERALCOUNT*20+30,165,WHITE);
            for (n=1;n<=5;n++) {
                gfx_hline(50,60,250-30*n,WHITE);
                int_to_str(n*20,num_buf);
                gfx_draw_char(gfx_draw_string(50,240-30*n,num_buf,WHITE),240-30*n,'%',WHITE);
            }

            n=0;
            gfx_draw_string(300,90,farm_select==farm_view?"Choose to Plant:":"Crop Name:",WHITE);
            gfx_draw_string(450,90,"Add:",WHITE);
            gfx_draw_string(500,90,"Del:",WHITE);
            gfx_draw_string(550,90,"Price:",WHITE);
            while (crop_iter!=NULL) {
                if (farm_select==farm_view) {
                    add_button(300,100+40*n,100,20,crop_iter->name,n+1,0,0);
                } else {
                    gfx_draw_string(300,100+40*n,crop_iter->name,WHITE);
                }
                gfx_draw_string(gfx_draw_char(450,100+40*n,'^',WHITE),100+40*n,mineral_names[crop_iter->mineral_add],mineral_colors[crop_iter->mineral_add]);
                gfx_draw_string(gfx_draw_char(500,100+40*n,'v',WHITE),100+40*n,mineral_names[crop_iter->mineral_del],mineral_colors[crop_iter->mineral_del]);
                int_to_str(crop_iter->price,num_buf);gfx_draw_string(gfx_draw_char(550,100+40*n,'$',WHITE),100+40*n,num_buf,WHITE);
                crop_iter=crop_iter->next_crop;
                n++;
            }
        }

        full_farm_name[5]=farm_iter->name;
        add_button(button_x,40,100,30,full_farm_name,farm_iter->name,1,farm_iter->name==farm_view);
        farm_iter=farm_iter->next_farm;
        button_x+=100;
    }
}

void gui_purchase_items_setup() {
    if (!gfx_present()) { return; }
    gfx_clear(15);

    add_button(50,50,200,40,"Do Nothing",1,0,0);
    add_button(50,100,200,40,"Buy Farm (-$50)",2,0,0);
    add_button(50,150,200,40,"Sell Farm (+$50)",3,0,0);
}

#endif
