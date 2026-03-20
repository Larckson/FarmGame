#ifndef INITFARMSETUP
#define INITFARMSETUP

#include <stdio.h>

#define mineral_count 5

extern void string_copy(char* s,char* d);
extern void* malloc_c(size_t size);
extern void  free_c(void* ptr);

const char mineral_names[mineral_count][3] = {"N","K","Mo","P","C"};

struct farm {
    int minerals[mineral_count];
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

    struct farm *new_farm = (struct farm*)malloc_c(sizeof(struct farm));
    if (new_farm == NULL) {
        printf("Memory allocation failed\n");
        return farms;
    }

    new_farm->current_crop = 0;
    new_farm->name = (farms==NULL) ? 'A' : farms->name+1;

    for (i=0;i<mineral_count;i++) {
        new_farm->minerals[i] = 2;
    }

    new_farm->next_farm = farms;
    return new_farm;
}

struct crop* create_initial_crops() {
    int crop_length = 4;
    struct crop *crops=(struct crop*)malloc_c(crop_length*sizeof(struct crop));
    struct crop *crop_iter=crops;

    string_copy(crop_iter->name,"Corn");
    crop_iter->mineral_add=0;
    crop_iter->mineral_del=1;
    crop_iter->price=40;
    crop_iter->next_crop=crop_iter+1;
    crop_iter=crop_iter->next_crop;
    string_copy(crop_iter->name,"Beans");
    crop_iter->mineral_add=1;
    crop_iter->mineral_del=2;
    crop_iter->price=40;
    crop_iter->next_crop=crop_iter+1;
    crop_iter=crop_iter->next_crop;
    string_copy(crop_iter->name,"Squash");
    crop_iter->mineral_add=3;
    crop_iter->mineral_del=4;
    crop_iter->price=40;
    crop_iter->next_crop=crop_iter+1;
    crop_iter=crop_iter->next_crop;
    string_copy(crop_iter->name,"Potatoes");
    crop_iter->mineral_add=4;
    crop_iter->mineral_del=0;
    crop_iter->price=40;
    crop_iter->next_crop=NULL;

    return crops;
}

#endif
