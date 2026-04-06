#ifndef INITFARMSETUP
#define INITFARMSETUP

#define NULL ((void *)0)

extern int print_text(const char* s);
extern void copy_string(char* s,char* d);
extern void* mem_alloc(unsigned long size);
extern void  mem_free(void* ptr);

#define MINERALCOUNT 5
const char mineral_names[MINERALCOUNT][3]={ "N","K","Mo","P","C" };
const unsigned int mineral_colors[MINERALCOUNT]={ RED,GREEN,BLUE,MAGENTA,YELLOW };

struct farm {
    int minerals[MINERALCOUNT];
    int current_crop;
    char name;
    struct farm* next_farm;
};

struct crop {
    int price;
    int mineral_add;
    int mineral_del;
    char name[8];
    struct crop* next_crop;
};

struct farm* add_farm(struct farm* farms) {
    int i;

    struct farm *new_farm=(struct farm*)mem_alloc(sizeof(struct farm));
    if (new_farm==NULL) {
        print_text("Memory allocation failed\n");
        return farms;
    }

    new_farm->current_crop=0;
    new_farm->name=(farms==NULL)?'A':farms->name+1;

    for (i=0;i<MINERALCOUNT;i++) {
        new_farm->minerals[i]=2;
    }

    new_farm->next_farm=farms;
    return new_farm;
}

struct crop* create_initial_crops() {
    int crop_length=4;
    struct crop *crops=(struct crop*)mem_alloc(crop_length*sizeof(struct crop));
    struct crop *crop_iter=crops;

    copy_string(crop_iter->name,"Corn");
    crop_iter->mineral_add=0;
    crop_iter->mineral_del=1;
    crop_iter->price=40;
    crop_iter->next_crop=crop_iter+1;
    crop_iter=crop_iter->next_crop;
    copy_string(crop_iter->name,"Beans");
    crop_iter->mineral_add=1;
    crop_iter->mineral_del=2;
    crop_iter->price=40;
    crop_iter->next_crop=crop_iter+1;
    crop_iter=crop_iter->next_crop;
    copy_string(crop_iter->name,"Squash");
    crop_iter->mineral_add=3;
    crop_iter->mineral_del=4;
    crop_iter->price=40;
    crop_iter->next_crop=crop_iter+1;
    crop_iter=crop_iter->next_crop;
    copy_string(crop_iter->name,"Potato");
    crop_iter->mineral_add=4;
    crop_iter->mineral_del=0;
    crop_iter->price=40;
    crop_iter->next_crop=NULL;

    return crops;
}

#endif
