#include "bmp.h"

void write_bmp(Bmp *self, intArray *name) {
    // char *c = (char *)malloc(size(name) + 1);
    // memcpy(c, name->m_data, size(name));
    // c[size(name)] = 0;
    FILE *f = fopen(c_str(name), "wb+");
    refresh_buf(self);
    fprint(&(self->whole_str), f);
    fclose(f);
    // free(c);
}

void refresh_buf(Bmp *self) {
    // Note: ci = current_index
    size_t    ci = 0;
    intArray *ws = &(self->whole_str);
    intArray  str_val;
    intArray *str = &str_val;
    init(str, 0);
    // intArray  buf_val;
    // intArray *buf = &buf_val;
    // init(buf, 0);

    readVar(str, self->bh.field, 2);
    replaceArr(ws, str, ci, ci + 2, 0, size(str));
    ci += 2;

// Note: sfp : self pointer; sfv : self value
#define sfp(arg) &(self->arg)
#define sfv(arg) (self->arg)
#define replaceSame(var, counter)                                                                                      \
    readVar(str, sfp(var), sizeof(sfv(var)));                                                                          \
    replaceArr(ws, str, counter, counter + sizeof(sfv(var)), 0, size(str));                                            \
    counter += sizeof(sfv(var));
#define replaceDifferent(var, counter, increment)                                                                      \
    readVar(str, sfp(var), sizeof(sfv(var)));                                                                          \
    replaceArr(ws, str, counter, counter + increment, 0, size(str));                                                   \
    counter += increment;
    // #define block(var, counter)
    //     readVar(str, &(self->var), sizeof((self->var)));
    //     replaceArr(ws, str, counter, counter + sizeof(var), 0, size(str));
    //     counter += sizeof(var);

    // replaceSame(bh.file_size, ci);
    readVar(str, sfp(bh.file_size), sizeof(sfv(bh.file_size)));
    replaceArr(ws, str, ci, ci + sizeof(sfv(bh.file_size)), 0, size(str));
    ci += sizeof(sfv(bh.file_size));

    ci += 4;
    replaceSame(bh.starting_address, ci);
    replaceSame(dh.header_size, ci);
    replaceSame(dh.bm_width, ci);
    replaceSame(dh.bm_height, ci);
    replaceSame(dh.color_panes, ci);
    replaceSame(dh.bits_per_pixel, ci);
    replaceSame(dh.compression_method, ci);
    replaceSame(dh.image_size, ci);
    replaceSame(dh.hor_res, ci);
    replaceSame(dh.ver_res, ci);
    replaceSame(dh.num_colours, ci);
    replaceSame(dh.num_colours_used, ci);
    ci = sfv(bh.starting_address);
    replaceArr(sfp(whole_str), str, ci, size(sfp(whole_str)), 0, 0);
    // self->
    // self->pixels.

    size_ut overflow = (self->dh.bits_per_pixel * self->dh.bm_width) % 32;
    size_ut padding  = overflow ? 4 - overflow / 8 : 0;

    for (size_t i = 0; i < (size_t)(size_pixArr(sfp(pixels))); ++i) {
        concatEq(sfp(whole_str), &(sfv(pixels).m_data[i].m_array));
        if (!((i + 1) % self->dh.bm_width)) { resize(sfp(whole_str), size(sfp(whole_str)) + padding); }
    }
    sfv(bh.file_size) = size(sfp(whole_str));

    readVar(str, sfp(bh.file_size), sizeof(sfv(bh.file_size)));
    replaceArr(ws, str, 2, 2 + sizeof(sfv(bh.file_size)), 0, size(str));
    dest(str);
#undef replaceDifferent
#undef replaceSame
#undef sfv
#undef sfp
    return;
    // replace

    // replaceSame(bh.)

    // readVar(str, sfp(bh.file_size), sizeof(sfv(bh.file_size)));
    // replaceArr(ws)

    // concatEq(str, buf);
}