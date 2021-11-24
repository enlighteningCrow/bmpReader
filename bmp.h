#ifndef BMP_H
#define BMP_H

#include <alloca.h>
#include <fenv.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pixel.h"
#include "utils.h"
#include "utils_pix.h"

typedef struct intArray intArray;
typedef struct pixArray pixArray;


typedef char int1_t;


struct Binary {

    size_t  size;
    size_t  allocated;
    size_t *m_data;
};


struct Header {
    int a;
};
struct BitmapHeader {
    int1_t       field[2];
    int          file_size;
    unsigned int res1;
    unsigned int res2;
    int          starting_address;
};

enum Type {
    BITMAPCOREHEADER,
    OS22XBITMAPHEADER,
    BITMAPINFOHEADER,
    BITMAPV2INFOHEADER,
    BITMAPV3INFOHEADER,
    BITMAPV4HEADER,
    BITMAPV5HEADER,
};

typedef enum Type Type;

struct DIBHeader {
    Type      type;
    int       header_size;
    int       bm_width;
    int       bm_height;
    short int color_panes;
    short int bits_per_pixel;
    int       compression_method;
    int       image_size;
    int       hor_res;
    int       ver_res;
    bool      is_top_to_bottom;
    int       num_colours;
    int       num_colours_used;
};

typedef struct Header       Header;
typedef struct BitmapHeader BitmapHeader;
typedef struct DIBHeader    DIBHeader;


int readFile(intArray *self, FILE *f, size_t count);
int readArr(intArray *self, intArray *arr, size_t start, size_t end);

int readVar(intArray *self, void *var, size_t size);
int writeVar(intArray *self, void *f);

int writeFile(intArray *self, FILE *f);

struct Bmp {
    Header       h;
    BitmapHeader bh;
    DIBHeader    dh;
    // int1_t      *m_data;
    // int      a;
    pixArray pixels;
    intArray whole_str;
    intArray filename;
};

typedef struct Bmp Bmp;

Bmp *parse(Bmp *self, FILE *f);

void fill(Bmp *self, size_t x0, size_t y0, size_t x1, size_t y1, const intArray *str, int1_t opacity);
void fill_num(Bmp *self, size_t x0, size_t y0, size_t x1, size_t y1, ...);
int  fill_prompt(Bmp *self);
void scale_bmp(Bmp *self, long double factor);
void write_bmp(Bmp *self, intArray *name);
void resize_bmp(Bmp *self, size_t width, size_t height);
void crop_bmp(Bmp *self, size_t x0, size_t y0, size_t x1, size_t y1);
void refresh_buf(Bmp *self);

int replaceArr(intArray *self, intArray *other, size_t self_f, size_t self_t, size_t other_f, size_t other_t);

void init_bmp(Bmp *self);
void dest_bmp(Bmp *self);

Bmp *parse_bmp(Bmp *self, intArray *fileName);

#endif