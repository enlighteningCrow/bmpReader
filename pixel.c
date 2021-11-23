#include "pixel.h"
#include "utils.h"


// TODO: The things held in each of the pixels have to unsigned, maybe there is a workaround


// #define Pixel struct Pixel
// #define intArray struct intArray


Pixel *setBpp(Pixel *self, int1_t bpp) {
    self->m_bpp = bpp;
    resize(&(self->m_array), (bpp + 7) / 8);
    return self;
}

Pixel *configString(Pixel *self, const intArray *str) {
    memcpy(self->m_array.m_data, str->m_data, size(str));
    // memmove(self->m_array.m_data, str->m_data, size(str));
    return self;
}

// bool debugCheckpointToggler(Pixel *self, Pixel *prev) {
//     if (prev == NULL) return 1;
//     return strEq(&(self->m_array), &(prev->m_array));
// }
Pixel *setColour(Pixel *self, int1_t colour, int1_t index) {
    // static Pixel *prev                  = NULL;
    self->m_array.m_data[(size_t)index] = colour;
    // TODO: Debug this part!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // prev = self;
    return self;
}

Pixel *setA(Pixel *self, int1_t colour) {
    /* if (self->m_bpp < 24) throw "Alpha channel not supported in this bitmap file. \n"; */
    if (self->m_bpp < 24) fprintf(stderr, "Alpha channel not supported in this bitmap file. \n");
    setColour(self, colour, 3);
    return self;
}
Pixel *setR(Pixel *self, int1_t colour) {
    // setColour(self, colour, self->m_bpp >= 24 ? (self->m_bpp >= 32 ? 1 : 0) : 0);
    setColour(self, colour, 2);
    return self;
}
Pixel *setG(Pixel *self, int1_t colour) {
    // setColour(self, colour, self->m_bpp >= 24 ? (self->m_bpp >= 32 ? 2 : 1) : 1);
    setColour(self, colour, 1);
    return self;
}
Pixel *setB(Pixel *self, int1_t colour) {
    // setColour(self, colour, self->m_bpp >= 24 ? (self->m_bpp >= 32 ? 3 : 2) : 2);
    setColour(self, colour, 0);
    return self;
}

int1_t getA(Pixel *self) {
    // if (self->m_bpp < 24) throw "Alpha channel not supported in this bitmap file. \n";
    if (self->m_bpp < 24) fprintf(stderr, "Alpha channel not supported in this bitmap file. \n");

    return self->m_array.m_data[3];
}
int1_t getR(Pixel *self) { return self->m_array.m_data[2]; }
int1_t getG(Pixel *self) { return self->m_array.m_data[1]; }
int1_t getB(Pixel *self) { return self->m_array.m_data[0]; }

Pixel *copy_pix(Pixel *self, Pixel *other) {
    self->m_bpp = other->m_bpp;
    strAssign(&(self->m_array), &(other->m_array));
    return self;
}

void init_pix(Pixel *self, size_t size, short int bpp) {
    init(&self->m_array, size);
    self->m_bpp = bpp;
}

void dest_pix(Pixel *self) { dest(&self->m_array); }