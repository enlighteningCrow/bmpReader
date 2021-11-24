#include "bmp.h"

typedef struct intArray     intArray;
typedef struct pixArray     pixArray;
typedef char                int1_t;
typedef enum Type           Type;
typedef struct Header       Header;
typedef struct BitmapHeader BitmapHeader;
typedef struct DIBHeader    DIBHeader;

size_t min_64(size_t x, size_t y) { return x > y ? y : x; }

int readFile(intArray *self, FILE *f, size_t count) {
    // static size_ut counter = 0;
    // printf("%lli\n", (counter += count));

    resize(self, count);
    // int a;
    fread(self->m_data, 1, count, f);
    // fread(&a, 1, count, f);
    // printf("Read: %d", a);
    // fprint(self, stdout);
    // printf(". \n");
    return 0;
}

int readArr(intArray *self, intArray *arr, size_t start, size_t end) {
    // static size_ut counter = 0;
    // printf("%lli\n", (counter += count));

    // Note: this reads from [start, end)
    if (start > end) { return start - end; }

    resize(self, (size_t)(end - start));
    memcpy(self, arr + start, end - start);
    // int a;

    // fread(self->m_data, 1, size(arr), f);

    // fread(&a, 1, count, f);
    // printf("Read: %d", a);
    // fprint(self, stdout);
    // printf(". \n");
    return 0;
}

int readVar(intArray *self, void *var, size_t size) {
    // static size_ut counter = 0;
    // printf("%lli\n", (counter += count));

    resize(self, size);
    // int a;

    // fread(self->m_data, 1, count, f);
    memcpy(self->m_data, var, size);

    // fread(&a, 1, count, f);
    // printf("Read: %d", a);
    // fprint(self, stdout);
    // printf(". \n");
    return 0;
}

int writeVar(intArray *self, void *var) {
    memcpy(var, self->m_data, size(self));
    return 0;
}

int writeFile(intArray *self, FILE *f) {
    fwrite(self->m_data, sizeof(int1_t), size(self), f);
    return 0;
}

// struct Bmp {
//     Header       h;
//     BitmapHeader bh;
//     DIBHeader    dh;
//     // int1_t      *m_data;
//     // int      a;
//     pixArray pixels;
//     intArray whole_str;
// };

typedef struct Bmp Bmp;

void fill(Bmp *self, size_t x0, size_t y0, size_t x1, size_t y1, const intArray *str, int1_t opacity) {
    opacity = opacity + x0;

    if (x0 > x1) {
        size_t a = x0;
        x0       = x1;
        x1       = a;
    }
    if (y0 > y1) {
        size_t a = y0;
        y0       = y1;
        y1       = a;
    }
    if (!self->dh.is_top_to_bottom) {
        size_t y_tmp = self->dh.bm_height - y0 - 1;
        y0           = self->dh.bm_height - y1 - 1;
        y1           = y_tmp;
    }
    // y0 = self->dh.bm_height - y0 - 1;
    // y1 = self->dh.bm_height - y1 - 1;
    for (size_t x = x0; x <= x1; ++x) {

        for (size_t y = y0; y <= y1; ++y) {
            configString(&(self->pixels.m_data[y * self->dh.bm_width + x]), str);
            // printf("%lu / %lld\n", y * self->dh.bm_width + x, size_pixArr(&self->pixels));
        }
    }
    return;
}

int fill_prompt(Bmp *self) {
#define prompt(name, word, type, scan_target, scan_type)                                                               \
    printf("Enter " #word " " #name ":\t");                                                                            \
    type name;                                                                                                         \
    {                                                                                                                  \
        scan_type tmp;                                                                                                 \
        if (scanf("%" #scan_target, &tmp) < 0) return -1;                                                              \
        name = ((type)tmp);                                                                                            \
    }
    // printf("Enter point x0: ");
    prompt(x0, point, size_t, lu, size_t);
    prompt(y0, point, size_t, lu, size_t);
    prompt(x1, point, size_t, lu, size_t);
    prompt(y1, point, size_t, lu, size_t);
    prompt(r, red channel, int1_t, x, int);
    prompt(g, green channel, int1_t, x, int);
    prompt(b, blue channel, int1_t, x, int);
    // size_t x0 = ;
    if (self->dh.bits_per_pixel >= 32) {
        prompt(a, alpha channel, int1_t, x, int);
        fill_num(self, x0, y0, x1, y1, a, r, g, b);
    }
    else {
        fill_num(self, x0, y0, x1, y1, r, g, b);
    }
    return 0;
#undef prompt
}

int crop_prompt(Bmp *self) {
#define prompt(name, word, type, scan_target, scan_type)                                                               \
    printf("Enter " #word " " #name ":\t");                                                                            \
    type name;                                                                                                         \
    {                                                                                                                  \
        scan_type tmp;                                                                                                 \
        if (scanf("%" #scan_target, &tmp) < 0) return -1;                                                              \
        name = ((type)tmp);                                                                                            \
    }
    // printf("Enter point x0: ");
    prompt(x0, point, size_t, lu, size_t);
    prompt(y0, point, size_t, lu, size_t);
    prompt(x1, point, size_t, lu, size_t);
    prompt(y1, point, size_t, lu, size_t);
    crop_bmp(self, x0, y0, x1, y1);
    return 0;
#undef prompt
}

void fill_num(Bmp *self, size_t x0, size_t y0, size_t x1, size_t y1, ...) {
    bool    mode = self->dh.bits_per_pixel >= 32;
    va_list list;
    va_start(list, y1);

    if (x0 > x1) {
        size_t a = x0;
        x0       = x1;
        x1       = a;
    }
    if (y0 > y1) {
        size_t a = y0;
        y0       = y1;
        y1       = a;
    }
    if (!self->dh.is_top_to_bottom) {
        size_t y_tmp = self->dh.bm_height - y0 - 1;
        y0           = self->dh.bm_height - y1 - 1;
        y1           = y_tmp;
    }
    // size_t y_tmp = self->dh.bm_height - y0 - 1;
    // y0           = self->dh.bm_height - y1 - 1;
    // y1           = y_tmp;
    if ((int)y1 >= self->dh.bm_height) {
        fprintf(stderr, "Warning: y1 is above height of the bmp file.\n");
        y1 = self->dh.bm_height - 1;
    }
    if ((int)x1 >= self->dh.bm_width) {
        fprintf(stderr, "Warning: x1 is above width of the bmp file.\n");
        x1 = self->dh.bm_width - 1;
    }
    // &(self->pixels);
    int1_t val;
#define pix_ptr (&(self->pixels))
// #define setPixels(channel)
//     val = (int1_t)va_arg(list, int);
//     for_each_pix(pix_ptr, Pixel, i) { set##channel(i, val); }
#define setPixels(channel)                                                                                             \
    val = (int1_t)va_arg(list, int);                                                                                   \
    for (size_t i = x0; i <= x1; ++i) {                                                                                \
        for (size_t j = y0; j <= y1; ++j) { set##channel(self->pixels.m_data + i + (j * self->dh.bm_width), val); }    \
    }
    // self->pixels.m_data
    if (mode) {
        // for (size_t i = x0; i < self->dh.)
        // val = va_arg(list, int1_t);
        // for_each(pix_ptr, Pixel, i) { setA(i, val); }

        setPixels(A);
        setPixels(R);
        setPixels(G);
        setPixels(B);

        // val = (int1_t)va_arg(list, int);
        // for (size_t i = x0; i <= x1; ++i) {
        //     for (size_t j = y1; j <= y0; ++j) {
        //         ;
        //         setA(self->pixels.m_data + i + (j * self->dh.bm_width), val);
        //     }
        // }
        // val = (int1_t)va_arg(list, int);
        // for (size_t i = x0; i <= x1; ++i) {
        //     for (size_t j = y1; j <= y0; ++j) {
        //         ;
        //         setR(self->pixels.m_data + i + (j * self->dh.bm_width), val);
        //     }
        // }
        // val = (int1_t)va_arg(list, int);
        // for (size_t i = x0; i <= x1; ++i) {
        //     for (size_t j = y1; j <= y0; ++j) {
        //         ;
        //         setG(self->pixels.m_data + i + (j * self->dh.bm_width), val);
        //     }
        // }
        // val = (int1_t)va_arg(list, int);
        // for (size_t i = x0; i <= x1; ++i) {
        //     for (size_t j = y1; j <= y0; ++j) {
        //         ;
        //         setB(self->pixels.m_data + i + (j * self->dh.bm_width), val);
        //     }
        // }

        // setA(pix_ptr, va_arg(list, int1_t));
        // setR(pix_ptr, va_arg(list, int1_t));
        // setG(pix_ptr, va_arg(list, int1_t));
        // setB(pix_ptr, va_arg(list, int1_t));
        // setB(pix_ptr, )
    }
    else {
        setPixels(R);
        setPixels(G);
        setPixels(B);
        // setR(pix_ptr, va_arg(list, int1_t));
        // setG(pix_ptr, va_arg(list, int1_t));
        // setB(pix_ptr, va_arg(list, int1_t));
    }
    va_end(list);
#undef pix_ptr
    return;

    // setB(pix_ptr, )
}

void scale_bmp(Bmp *self, long double factor) {
    size_t    new_width  = round_down(factor * self->dh.bm_width);
    size_t    new_height = round_down(factor * self->dh.bm_height);
    pixArray  pixels;
    pixArray *pix = &pixels;
    init_pixArr(pix, new_width * new_height, self->dh.bits_per_pixel);
    for (size_t i = 0; i < new_width; ++i) {
        for (size_t j = 0; j < new_height; ++j) {
            copy_pix(
                pixels.m_data + (i + j * new_width),
                // self->pixels.m_data + (round_down(i / factor) + self->dh.bm_width * round_down(j / factor)));
                self->pixels.m_data +
                    (min_64(round_down(i / factor), self->dh.bm_width - 1) +
                     self->dh.bm_width * min_64(round_down(j / factor), self->dh.bm_height - 1)));
            // pixels.m_data[i + j * new_width] =
            //     self->pixels.m_data[round_down(i / factor) + self->dh.bm_width * round_down(j / factor)];
        }
    }
    self->dh.bm_width  = new_width;
    self->dh.bm_height = new_height;
    swap_pixArr(&(self->pixels), pix);
    dest_pixArr(pix);
}

void resize_bmp(Bmp *self, size_t width, size_t height) {
    size_t new_width  = width;
    size_t new_height = height;
    // long double factor     = round_near(
    //         (round_near(width / (long double)(self->dh.bm_width)) +
    //      round_near(height / (long double)(self->dh.bm_height))) /
    //         2.0L);
    long double factorx = round_near(width / (long double)(self->dh.bm_width)),
                factory = round_near(height / (long double)(self->dh.bm_height));
    pixArray  pixels;
    pixArray *pix = &pixels;
    init_pixArr(pix, new_width * new_height, self->dh.bits_per_pixel);
    for (size_t i = 0; i < new_width; ++i) {
        for (size_t j = 0; j < new_height; ++j) {
            copy_pix(
                pixels.m_data + (i + j * new_width),
                self->pixels.m_data +
                    (min_64(round_down(i / factorx), self->dh.bm_width - 1) +
                     self->dh.bm_width * min_64(round_down(j / factory), self->dh.bm_height - 1)));
            // pixels.m_data[i + j * new_width] =
            //     self->pixels.m_data[round_down(i / factor) + self->dh.bm_width * round_down(j / factor)];
        }
    }
    self->dh.bm_width  = new_width;
    self->dh.bm_height = new_height;
    swap_pixArr(&(self->pixels), pix);
    dest_pixArr(pix);
}

void crop_bmp(Bmp *self, size_t x0, size_t y0, size_t x1, size_t y1) {
    if (x0 > x1) {
        size_t a = x0;
        x0       = x1;
        x1       = a;
    }
    if (y0 > y1) {
        size_t a = y0;
        y0       = y1;
        y1       = a;
    }
    if (!self->dh.is_top_to_bottom) {
        size_t y_tmp = self->dh.bm_height - y0 - 1;
        y0           = self->dh.bm_height - y1 - 1;
        y1           = y_tmp;
    }
    // size_t y_tmp = self->dh.bm_height - y0 - 1;
    // y0           = self->dh.bm_height - y1 - 1;
    // y1           = y_tmp;
    if ((int)y1 >= self->dh.bm_height) {
        fprintf(stderr, "Warning: y1 is above height of the bmp file.\n");
        y1 = self->dh.bm_height - 1;
    }
    if ((int)x1 >= self->dh.bm_width) {
        fprintf(stderr, "Warning: x1 is above width of the bmp file.\n");
        x1 = self->dh.bm_width - 1;
    }


    pixArray  pixels;
    pixArray *pix       = &pixels;
    size_t    new_width = (x1 - x0 + 1), new_height = (y1 - y0 + 1);
    init_pixArr(pix, new_width * new_height, self->dh.bits_per_pixel);
    for (size_t i = 0; i < new_width; ++i) {
        for (size_t j = 0; j < new_height; ++j) {
            copy_pix(
                pixels.m_data + (i + j * new_width), self->pixels.m_data + ((i + x0) + (j + y0) * self->dh.bm_width));
            // pixels.m_data[i + j * new_width] =
            //     self->pixels.m_data[round_down(i / factor) + self->dh.bm_width * round_down(j / factor)];
        }
    }
    self->dh.bm_width  = new_width;
    self->dh.bm_height = new_height;
    swap_pixArr(&(self->pixels), pix);
    dest_pixArr(pix);
}

// void doNothing(void *a, ...) { return; }

int replaceArr(intArray *self, intArray *other, size_t self_f, size_t self_t, size_t other_f, size_t other_t) {
    if (self_f > self_t) return self_f - self_t;
    if (other_f > other_t) return other_f - other_t;
    if (self_t > size(self)) return self_t - size(self);
    if (other_t > size(other)) return other_t - size(other);
    size_t other_dif = (other_t - other_f), self_dif = (self_t - self_f);
    // if (self_dif > other_dif) {
    //     size_ut difference = ((self_t - self_f) - (other_t - other_f));

    //     memcpy(self_f + other_dif, self_t, size(self) - self_t);
    // }
    // else if (self_dif < other_dif) {
    //     // TODO!: This difference might be useless.
    //     size_ut difference = ((other_t - other_f) - (self_t - self_f));

    //     memmove(self_f + other_dif, self_t, size(self) - self_t);
    // }
    if (self_dif != other_dif) {
        // (self_dif > other_dif       ? memcpy
        //      : self_dif < other_dif ? memmove
        //                             : doNothing)(self_f + other_dif, self_t, size(self) - self_t);
        (self_dif > other_dif ? memcpy
                              : memmove)(self->m_data + self_f + other_dif, self->m_data + self_t, size(self) - self_t);
        resize(self, size(self) + other_dif - self_dif);
    }
    if (other_dif) { memcpy(self->m_data + self_f, other->m_data + other_f, other_dif); }
    return 0;
}

void init_bmp(Bmp *self) {
    init_pixArr(&(self->pixels), 0, self->dh.bits_per_pixel);
    init(&(self->whole_str), 0);
    init(&(self->filename), 0);
}

void dest_bmp(Bmp *self) {
    dest_pixArr(&(self->pixels));
    dest(&(self->whole_str));
    dest(&(self->filename));
}