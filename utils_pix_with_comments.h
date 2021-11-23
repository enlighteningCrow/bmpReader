#ifndef UTILS_PIX_H
#define UTILS_PIX_H

#include "pixel.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// #define Pixel struct Pixel
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

// #define pixArray struct pixArray
typedef struct pixArray pixArray;

size_ut   size_pixArr(pixArray *self);
pixArray *resize_pixArr(pixArray *self, size_ut size);

pixArray *remove_pixArr(pixArray *self, size_ut start, size_ut end);

pixArray *insert_pixArr(pixArray *self, Pixel value, size_ut index);


pixArray *replace_pixArr(pixArray *self, Pixel value, size_ut start, size_ut end);

pixArray *pop_front_pixArr(pixArray *self, size_ut indexes);

pixArray *push_front_pixArr(pixArray *self, Pixel val);

/*
size_ut find_pix(pixArray *self, Pixel target);
size_ut findGreater_pix(pixArray *self, Pixel target);
size_ut findGreaterEq_pix(pixArray *self, Pixel target);
size_ut findLesser_pix(pixArray *self, Pixel target);
size_ut findLesserEq_pix(pixArray *self, Pixel target);
 */

pixArray *clear_pixArr(pixArray *self);

/*
size_ut   _find_pix(pixArray *self, Pixel target, size_ut left, size_ut right);
size_ut   _findg_pix(pixArray *self, Pixel target, size_ut left, size_ut right);
size_ut   _findl_pix(pixArray *self, Pixel target, size_ut left, size_ut right);
size_ut   _findge_pix(pixArray *self, Pixel target, size_ut left, size_ut right);
size_ut   _findle_pix(pixArray *self, Pixel target, size_ut left, size_ut right);
 */

pixArray *push_back_pixArr(pixArray *self, Pixel element);
pixArray *pop_back_pixArr(pixArray *self);

pixArray *sort_pixArr(pixArray *self);

void init_pixArr(pixArray *self, size_ut size, short int bpp);
void dest_pixArr(pixArray *self);

void swap_pixArr(pixArray *self, pixArray *other);
// #undef Pixel

#endif // UTILS_PIX_H
