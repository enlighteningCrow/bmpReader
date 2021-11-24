#ifndef UTILS_PIX_H
#define UTILS_PIX_H

#include "pixel.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Pixel Pixel;

// typedef long long int size_t;
typedef char          int1_t;

struct pixArray {
    size_t m_size;
    size_t m_allocated;
    Pixel  *m_data;
    bool    m_is_sorted;
    size_t _middle;
    int     m_bpp;
};


typedef struct pixArray pixArray;

size_t   size_pixArr(pixArray *self);
pixArray *resize_pixArr(pixArray *self, size_t size);

pixArray *remove_pixArr(pixArray *self, size_t start, size_t end);

pixArray *insert_pixArr(pixArray *self, Pixel value, size_t index);


pixArray *replace_pixArr(pixArray *self, Pixel value, size_t start, size_t end);

pixArray *pop_front_pixArr(pixArray *self, size_t indexes);

pixArray *push_front_pixArr(pixArray *self, Pixel val);


pixArray *clear_pixArr(pixArray *self);


pixArray *push_back_pixArr(pixArray *self, Pixel element);
pixArray *pop_back_pixArr(pixArray *self);

pixArray *sort_pixArr(pixArray *self);

void init_pixArr(pixArray *self, size_t size, short int bpp);
void dest_pixArr(pixArray *self);

void swap_pixArr(pixArray *self, pixArray *other);


#endif // UTILS_PIX_H
