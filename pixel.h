#ifndef PIXEL_H
#define PIXEL_H

#include <stdbool.h>

typedef char int1_t;

#include "utils.h"

// #define intArray struct intArray
typedef struct intArray intArray;

struct Pixel {
    intArray m_array;
    int1_t   m_bpp;
};

// #define Pixel struct Pixel
typedef struct Pixel Pixel;


Pixel *setBpp(Pixel *self, int1_t bpp);

Pixel *configString(Pixel *self, const intArray *str);
Pixel *setColour(Pixel *self, int1_t colour, int1_t index);

Pixel *setA(Pixel *self, int1_t colour);
Pixel *setR(Pixel *self, int1_t colour);
Pixel *setG(Pixel *self, int1_t colour);
Pixel *setB(Pixel *self, int1_t colour);

int1_t getA(Pixel *self);
int1_t getR(Pixel *self);
int1_t getG(Pixel *self);
int1_t getB(Pixel *self);

Pixel *copy_pix(Pixel *self, Pixel *other);
void   init_pix(Pixel *self, size_t size, short int bpp);
void   dest_pix(Pixel *self);
// #undef intArray

#endif // PIXEL_H
