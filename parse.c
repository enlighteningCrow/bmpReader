#include "bmp.h"

Bmp *parse(Bmp *self, FILE *f) {
    intArray  str_val;
    intArray *str = &str_val;

    // resize(&self->whole_str, 1);

    // Note: if broken change it to 4
    init(str, 0);


    readFile(str, f, 2);
    concatEq(&self->whole_str, str);
    // whole_str

    if (!strEqC(str, "BM")) fprintf(stderr, "Error: not a bmp file.\n");
    // self->bh.field[0] = str->m_data[0];
    // self->bh.field[1] = str->m_data[1];
    writeVar(str, self->bh.field);


    intArray  arr_val;
    intArray *arr = &arr_val;
    init(arr, 4);
    readFile(arr, f, 4);
    concatEq(&self->whole_str, arr);


    writeVar(arr, &(self->bh.file_size));


    readFile(str, f, 4);
    concatEq(&self->whole_str, str);


    readFile(str, f, 4);
    concatEq(&self->whole_str, str);


    writeVar(str, &(self->bh.starting_address));


    readFile(str, f, 4);
    concatEq(&self->whole_str, str);


    writeVar(str, &(self->dh.header_size));
    switch ((self->dh.header_size)) {
    case 12: (self->dh.type) = (BITMAPCOREHEADER); break;
    case 64:
    case 16: (self->dh.type) = (OS22XBITMAPHEADER); break;
    case 40: (self->dh.type) = (OS22XBITMAPHEADER); goto after;
    case 52: (self->dh.type) = (OS22XBITMAPHEADER); goto after;
    case 56: (self->dh.type) = (OS22XBITMAPHEADER); goto after;
    case 108: (self->dh.type) = (OS22XBITMAPHEADER); goto after;
    case 124:
        (self->dh.type) = (OS22XBITMAPHEADER);
        goto after;
    after:


        readFile(str, f, 4);
        concatEq(&self->whole_str, str);


        writeVar(str, &(self->dh.bm_width));

        readFile(str, f, 4);
        concatEq(&self->whole_str, str);


        writeVar(str, &(self->dh.bm_height));

        if ((self->dh.bm_height) < 0) {
            (self->dh.bm_height)        = -(self->dh.bm_height);
            (self->dh.is_top_to_bottom) = true;
        }

        readFile(str, f, 2);
        concatEq(&self->whole_str, str);

        writeVar(str, &(self->dh.color_panes));


        readFile(str, f, 2);
        concatEq(&self->whole_str, str);
        writeVar(str, &(self->dh.bits_per_pixel));

        readFile(str, f, 4);
        concatEq(&self->whole_str, str);
        writeVar(str, &(self->dh.compression_method));


        readFile(str, f, 4);
        concatEq(&self->whole_str, str);
        writeVar(str, &(self->dh.image_size));

        readFile(str, f, 4);
        concatEq(&self->whole_str, str);
        writeVar(str, &(self->dh.hor_res));

        readFile(str, f, 4);
        concatEq(&self->whole_str, str);
        writeVar(str, &(self->dh.ver_res));

        readFile(str, f, 4);
        concatEq(&self->whole_str, str);
        writeVar(str, &(self->dh.num_colours));

        readFile(str, f, 4);
        concatEq(&self->whole_str, str);
        writeVar(str, &(self->dh.num_colours_used));
        break;
    default: fprintf(stderr, "File might be corrupted. \n");
    }


    resize_pixArr(&(self->pixels), (self->dh.bm_width) * (self->dh.bm_height));

    readFile(str, f, self->bh.starting_address - ftell(f));
    concatEq(&self->whole_str, str);

    // fseek(f, self->bh.starting_address, SEEK_SET);

    size_ut times = (self->dh.bm_width) * (self->dh.bm_height);

    int  a_val;
    int *a = &a_val;

    FILE *fi = fopen("/home/twistingcamel/programs/kmitl/c++/bmpReader/trial.txt", "w+");

    size_ut overflow = (self->dh.bits_per_pixel * self->dh.bm_width) % 32;
    size_ut padding  = overflow ? 4 - overflow / 8 : 0;

    for (size_ut i = 0; i < times; ++i) {

        readFile(str, f, (self->dh.bits_per_pixel + 7) / 8);
        writeVar(str, a);
        concatEq(&self->whole_str, str);


        setBpp((self->pixels.m_data) + i, self->dh.bits_per_pixel);

        // TODO!: The configString is probably wrong, maybe use bitwise operations manually instead.

        configString((self->pixels.m_data) + i, str);
        // writeFile(str, fi);
        // times = times + 1 - 1;
        // fputc(times, stdout);
        if (!((i + 1) % self->dh.bm_width)) { readFile(str, f, padding); }
    }
    fclose(fi);
    // fprint(&self->whole_str, stdout);
    // printf("Whole_str size: %lu", size(&(self->whole_str)));


    return self;
}

Bmp *parse_bmp(Bmp *self, intArray *fileName) {
    strAssign(&self->filename, &fileName);
    // printf("%s", c_str(fileName));
    fflush(stdout);
    FILE *f = fopen(c_str(fileName), "r+");
    parse(self, f);
    fclose(f);
    return self;
}