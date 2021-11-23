#ifndef UTILS_BMP_H
#define UTILS_BMP_H

#include "pixel.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Bmp Bmp;

typedef long long int size_ut;
typedef char          int1_t;

struct bmpArray {
    size_ut m_size;
    size_ut m_allocated;
    Bmp    *m_data;
    bool    m_is_sorted;
    size_ut _middle;
};


typedef struct bmpArray bmpArray;

size_ut   size_bmpArr(bmpArray *self);
bmpArray *resize_bmpArr(bmpArray *self, size_ut size);

bmpArray *remove_bmpArr(bmpArray *self, size_ut start, size_ut end);

bmpArray *insert_bmpArr(bmpArray *self, Bmp value, size_ut index);


bmpArray *replace_bmpArr(bmpArray *self, Bmp value, size_ut start, size_ut end);

bmpArray *pop_front_bmpArr(bmpArray *self, size_ut indexes);

bmpArray *push_front_bmpArr(bmpArray *self, Bmp val);


bmpArray *clear_bmpArr(bmpArray *self);


bmpArray *push_back_bmpArr(bmpArray *self, Bmp element);
bmpArray *pop_back_bmpArr(bmpArray *self);

bmpArray *sort_bmpArr(bmpArray *self);

void init_bmpArr(bmpArray *self, size_ut size);
void dest_bmpArr(bmpArray *self);

void swap_bmpArr(bmpArray *self, bmpArray *other);


#endif // UTILS_BMP_H
