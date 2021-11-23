#include "utils.h"

// struct intArray;

struct Pixel {
    // protected:
    // Array<int1_t> m_array;
    intArray m_array;
    int1_t   m_bpp;

    // public:

    // Pixel() : Array(0), m_bpp{ 0 } {}
    // Pixel(const Pixel& pixel) : Array(pixel.m_size), m_bpp{ 0 } { memcpy(m_array.m_data, pixel.m_data, pixel.m_size);
    // } Pixel& fill(int1_t bpp, Array<int1_t>& array) {
    //     m_bpp = bpp;
    //     if (array.size() != ((bpp + 7) / 8)) throw "Size of array and from bpp not equal!\n";
    //     resize(array.size());
    //     memcpy(m_data, (int1_t*)array, array.size());
    // }
    // Pixel& operator=(const Pixel& pixel) {
    //     resize(pixel.m_size);
    //     // m_size = pixel.m_size;
    //     memcpy(m_data, pixel.m_data, pixel.m_size);
    //     return *this;
    // }
};

#define Pixel struct Pixel

// Bpp stands for bits per pixel
Pixel *setBpp(Pixel *self, int1_t bpp) {
    self->m_bpp = bpp;
    resize(&(self->m_array), (bpp + 7) / 8);
    return self;
}

Pixel *configString(Pixel *self, intArray *str) {
    memcpy(self->m_array.m_data, str->m_data, size(str));
    // std::memcpy(m_data, )
    // fill()
    return self;
}
Pixel *setColour(Pixel *self, int1_t colour, int1_t index) {
    self->m_array.m_data[index] = colour;
    return self;
}

Pixel *setA(Pixel *self, int1_t colour) {
    if (self->m_bpp < 24) throw "Alpha channel not supported in this bitmap file. \n";
    setColour(self, colour, 0);
    return self;
}
Pixel *setR(Pixel *self, int1_t colour) {
    setColour(self, colour, self->m_bpp >= 24 ? (self->m_bpp >= 32 ? 1 : 0) : 0);
    return self;
}
Pixel *setG(Pixel *self, int1_t colour) {
    setColour(self, colour, self->m_bpp >= 24 ? (self->m_bpp >= 32 ? 2 : 1) : 1);
    return self;
}
Pixel *setB(Pixel *self, int1_t colour) {
    setColour(self, colour, self->m_bpp >= 24 ? (self->m_bpp >= 32 ? 3 : 2) : 2);
    return self;
}

int1_t &getA(Pixel *self) {
    if (self->m_bpp < 24) throw "Alpha channel not supported in this bitmap file. \n";
    // setColour(colour, 0);
    return self->m_array.m_data[0];
}
int1_t &getR(Pixel *self) {
    // setColour(colour, m_bpp >= 24 ? (m_bpp >= 32 ? 1 : 0) : 0);
    return self->m_array.m_data[self->m_bpp >= 24 ? (self->m_bpp >= 32 ? 1 : 0) : 0];
}
int1_t &getG(Pixel *self) {
    // setColour(colour, m_bpp >= 24 ? (m_bpp >= 32 ? 2 : 1) : 1);
    return self->m_array.m_data[self->m_bpp >= 24 ? (self->m_bpp >= 32 ? 2 : 1) : 1];
}
int1_t &getB(Pixel *self) {
    // setColour(colour, m_bpp >= 24 ? (m_bpp >= 32 ? 3 : 2) : 2);
    return self->m_array.m_data[self->m_bpp >= 24 ? (self->m_bpp >= 32 ? 3 : 2) : 2];
}