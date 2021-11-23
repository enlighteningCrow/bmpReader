#ifndef UTILS_PIX_H
#define UTILS_PIX_H

#include "pixel.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Pixel Pixel;

typedef long long int size_ut;
typedef char          int1_t;

struct pixArray {
    size_ut m_size;
    size_ut m_allocated;
    Pixel  *m_data;
    bool    m_is_sorted;
    size_ut _middle;
    int     m_bpp;
};


typedef struct pixArray pixArray;

size_ut   size_pixArr(pixArray *self);
pixArray *resize_pixArr(pixArray *self, size_ut size);

pixArray *remove_pixArr(pixArray *self, size_ut start, size_ut end);

pixArray *insert_pixArr(pixArray *self, Pixel value, size_ut index);


pixArray *replace_pixArr(pixArray *self, Pixel value, size_ut start, size_ut end);

pixArray *pop_front_pixArr(pixArray *self, size_ut indexes);

pixArray *push_front_pixArr(pixArray *self, Pixel val);


pixArray *clear_pixArr(pixArray *self);


pixArray *push_back_pixArr(pixArray *self, Pixel element);
pixArray *pop_back_pixArr(pixArray *self);

pixArray *sort_pixArr(pixArray *self);

void init_pixArr(pixArray *self, size_ut size, short int bpp);
void dest_pixArr(pixArray *self);

void swap_pixArr(pixArray *self, pixArray *other);


#endif // UTILS_PIX_H
