#include <alloca.h>
// #include <bits/stdc++.h>
// #include <cstring>
#include <fenv.h>
// #include <initializer_list>
// #include <iostream>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pixel.h"
#include "utils.h"
#include "utils_pix.h"

#define intArray struct intArray
#define pixArray struct pixArray

// #define int1_t char
typedef char int1_t;

// void printBinary(void* a, size_t size) {
//     if (!size) return;
//     putchar('\n');
//     for (int i{ 8 * (int)size - 1 }; i >= 0; --i) {
//         putchar('0' + ((*(size_t*)a >> i) & 1));
//         // printf("%d", (*(int*)a >> i) & 1);
//     }
// }

// class Pixel;

// template<typename T>
// class Array {
// protected:
//     size_t m_size;
//     size_t m_allocated;
//     T* m_data;
//     friend class String;
//     virtual void _print(std::ostream& out) const {
//         // printf("{");
//         // for (int i{ 0 }; i < m_size; ++i) {
//         //     if (i) putchar(',');
//         //     printf(" %d", m_data[i]);
//         // }
//         // printf(" }");
//         out << ("{");
//         for (int i{ 0 }; i < m_size; ++i) {
//             if (i) out << (',');
//             out << ' ' << m_data[i];
//         }
//         out << (" }");
//     }

// public:
//     Array(Array<T>& array) : m_size{ array.m_size }, m_allocated{ array.m_allocated }, m_data{ array.m_data } {
//         array.m_data = NULL;
//     }
//     Array(const Array<T>& array) : m_size{ array.m_size }, m_allocated{ array.m_allocated }, m_data{ array.m_data } {
//         memcpy(m_data, array.m_data, m_size * sizeof(T));
//     }
//     Array(size_t size) :
//         m_size{ size }, m_allocated{ (size_t)(m_size * 1.3 + 1) }, m_data{ (T*)(malloc(sizeof(T) * m_allocated))
//         } { memset(m_data, 0, sizeof(T)* m_size);
//     }
//     Array(const std::initializer_list<T>& list) :
//         m_size{ list.size() }, m_allocated{ (size_t)(m_size * 1.3 + 1) }, m_data{
//                                                                                (T*)(malloc(sizeof(T) * m_allocated))
//                                                                                } {
//         int j{ 0 };
//         for (const T& i : list) {
//             m_data[j] = i;
//             ++j;
//         }
//     }
//     virtual ~Array() { free(m_data); }
//     virtual size_t size() const { return m_size; }
//     Array<T>& resize(size_t size) {
//         if (m_size == size) return *this;
//         bool expanded{ (m_allocated < size) };
//         if ((m_allocated < size) || ((size_t)(m_allocated * 0.7 + 1) > size)) {
//             m_allocated = (size_t)((size * 1.3) + 1);
//         }
//         else {
//             m_size = size;
//             return *this;
//         }
//         T* tmp{ (T*)(realloc(m_data, (sizeof(T) * m_allocated))) };
//         if (tmp != NULL) m_data = tmp;
//         if (expanded) {
//             memset(m_data + m_size, 0, (size - m_size) * sizeof(T));
//             if (tmp == NULL) throw "Out of memory.\n";
//         }
//         m_data = tmp;
//         m_size = size;
//         return *this;
//     }
//     T& operator[](size_t index) const {
//         if (index < 0) index += m_size;
//         if (index >= m_size || index < 0) throw "Out of range.\n";
//         return m_data[index];
//     }
//     Array<T> operator+(const Array<T>& array) const {
//         Array<T> arr(m_size + array.m_size);
//         memcpy(arr.m_data, m_data, m_size * sizeof(T));
//         memcpy(arr.m_data + m_size, array.m_data, array.m_size * sizeof(T));
//         return arr;
//     }
//     Array<T>& operator+=(const Array<T>& array) {
//         size_t old_size{ m_size };
//         resize(m_size + array.m_size);
//         memcpy(m_data + old_size, array.m_data, array.m_size * sizeof(T));
//         return *this;
//     }
//     Array<T>& operator=(const Array<T>& array) {
//         resize(array.m_size);
//         memcpy(m_data, array.m_data, array.m_size * sizeof(T));
//         return *this;
//     }
//     friend std::ostream& operator<<(std::ostream& out, const Array<T>& arr) {
//         arr._print(out);
//         return out;
//     }

// protected:
//     // TODO: edit the comparison function!!!!
// public:
//     Array<T>& sort() {
//         qsort(m_data, m_size, sizeof(T), [](const void* a, const void* b) -> int {
//             // std::cout << a << " is " << ((*((T*)(a)) < *((T*)(a))) ? "less than" : "more than or equal to") << b;
//             return *((T*)(a)) > *((T*)(b));
//             });
//         return *this;
//     }
//     inline bool operator==(const Array<T>& arr) const {
//         if (m_size != arr.m_size) return 0;
//         return !(memcmp(m_data, arr.m_data, m_size));
//     }
//     inline bool operator!=(const Array<T>& arr) const {
//         if (m_size != arr.m_size) return 1;
//         return (memcmp(m_data, arr.m_data, m_size));
//     }
//     operator T* () const { return m_data; }
// };

// // template<typename T = char>
// class String : public Array<char> {
// protected:
//     friend class Pixel;
//     virtual void _print(std::ostream& out) const override {
//         for (int i{ 0 }; i < m_size; ++i) {
//             if (m_data[i] == '\0') return;
//             out << (m_data[i]);
//         }
//         return;
//     }
//     String(String& array) : Array<char>{ array } {}

// public:
//     String(size_t size) : Array(size) {}
//     String(const char* str) : Array<char>((size_t)strlen(str)) { strcpy(m_data, str); }
//     String() : Array<char>(0UL) {}
//     String operator+(String& array) const {
//         String arr{ m_size + array.m_size };
//         memcpy(arr.m_data, m_data, m_size);
//         memcpy(arr.m_data + m_size, array.m_data, array.m_size);
//         return arr;
//     }
//     String operator+(const char* array) const {
//         String arr{ m_size + strlen(array) };
//         memcpy(arr.m_data, m_data, m_size);
//         strcpy(arr.m_data + m_size, array);
//         return arr;
//     }
//     String operator+(char ch) const {
//         String arr{ m_size + 1 };
//         memcpy(arr.m_data, m_data, m_size);
//         arr.m_data[m_size] = ch;
//         return arr;
//     }
//     String& operator+=(String& array) {
//         size_t old_size{ m_size };
//         resize(m_size + array.m_size);
//         memcpy(m_data + old_size, array.m_data, array.m_size);
//         return *this;
//     }
//     String& operator+=(const char* array) {
//         size_t old_size{ m_size };
//         resize(m_size + strlen(array));
//         strcpy(m_data + old_size, array);
//         return *this;
//     }
//     String& operator+=(char ch) {
//         size_t old_size{ m_size };
//         resize(m_size + 1);
//         m_data[old_size] = ch;
//         return *this;
//     }
//     String& operator=(String& array) {
//         resize(array.m_size);
//         memcpy(m_data, array.m_data, array.m_size);
//         return *this;
//     }
//     String& operator=(const char* array) {
//         resize(strlen(array));
//         strcpy(m_data, array);
//         return *this;
//     }
//     String& operator=(char ch) {
//         resize(1);
//         m_data[0] = ch;
//         return *this;
//     }
//     inline bool operator==(const String& arr) const {
//         if (m_size != arr.m_size) return 0;
//         return !(memcmp(m_data, arr.m_data, m_size));
//     }
//     inline bool operator!=(const String& arr) const {
//         if (m_size != arr.m_size) return 1;
//         return (memcmp(m_data, arr.m_data, m_size));
//     }
//     operator char* () const { return m_data; }
//     int readChars(FILE* f, size_t count) {
//         resize(count);
//         fread(m_data, 1, count, f);
//         // resize(count);
//         // size_t i{0};
//         // for (char *d{m_data}; i < count; ++i) {
//         //     *(d++) = fgetc(f);
//         //     if (*(d - 1) == EOF) return -1;
//         // }
//         return 0;
//     }
//     const char* c_str() const { return m_data; }
//     // friend std::ostream& operator<<(std::ostream& out, const String& str) {
//     //     str._print();
//     //     return out;
//     // }
// };

// // template<typename T = char>
// class String : public Array<char> {
// protected:
//     virtual void _print() const override {
//         for (int i{ 0 }; i < m_size; ++i) {
//             if (m_data[i] == '\0') return;
//             putchar(m_data[i]);
//         }
//         return;
//     }
//     String(String& array) : Array<char>{ array } {}
// public:
//     String(size_t size) : Array(size) {}
//     String(const char* str) : Array<char>((size_t)strlen(str)) {
//         strcpy(m_data, str);
//     }
//     String() : Array<char>(0UL) {}
//     String operator+ (String& array) const {
//         String arr{ strlen(m_data) + array.m_size };
//         strcpy(arr.m_data, m_data);
//         strcpy(arr.m_data + strlen(m_data), array.m_data);
//         return arr;
//     }
//     String operator+ (const char* array) const {
//         String arr{ strlen(m_data) + strlen(array) };
//         strcpy(arr.m_data, m_data);
//         strcpy(arr.m_data + strlen(m_data), array);
//         return arr;
//     }
//     String operator+ (char ch) const {
//         String arr{ strlen(m_data) + 1 };
//         strcpy(arr.m_data, m_data);
//         arr.m_data[m_size] = ch;
//         return arr;
//     }
//     String& operator+= (String& array) {
//         size_t old_size{ strlen(m_data) };
//         resize(strlen(m_data) + strlen(array.m_data));
//         strcpy(m_data + old_size, array.m_data);
//         return *this;
//     }
//     String& operator+= (const char* array) {
//         size_t old_size{ strlen(m_data) };
//         resize(strlen(m_data) + strlen(array));
//         strcpy(m_data + old_size, array);
//         return *this;
//     }
//     String& operator+= (char ch) {
//         size_t old_size{ strlen(m_data) };
//         resize(strlen(m_data) + 1);
//         m_data[old_size] = ch;
//         return *this;
//     }
//     String& operator= (String& array) {
//         resize(strlen(array.m_data));
//         strcpy(m_data, array.m_data);
//         return *this;
//     }
//     String& operator= (const char* array) {
//         resize(strlen(array));
//         strcpy(m_data, array);
//         return *this;
//     }
//     String& operator= (char ch) {
//         resize(1);
//         m_data[0] = ch;
//         return *this;
//     }
//     inline bool operator==(const String& arr) const {
//         if (m_size != arr.m_size) return 0;
//         return !(memcmp(m_data, arr.m_data, m_size));
//     }
//     inline bool operator!=(const String& arr) const {
//         if (m_size != arr.m_size) return 1;
//         return (memcmp(m_data, arr.m_data, m_size));
//     }
//     // friend std::ostream& operator<<(std::ostream& out, const String& str) {
//     //     str._print();
//     //     return out;
//     // }
// };


// template<typename T>
struct Binary {
    // protected:
    size_t  size;
    size_t  allocated;
    size_t *m_data;

    // public:
    // static void* writeBits(void* address, size_t size_of_each, size_t count, ...) {
    //     va_list vl;
    //     va_start(vl, count);
    //     int1_t* ptr{ (int1_t*)(address) };
    //     size_t index{ 0 };
    //     for (size_t i{ 0 }, holder{ 0 }; i < count; ++i /* , (ptr += size_of_each) */) {
    //         holder = va_arg(vl, size_t);
    //         // printBinary(holder);
    //         for (int j{ 0 }; j < size_of_each; ++j, ++ptr) {
    //             *ptr = (int1_t)(holder >> (8 * j));
    //             // printBinary(ptr, sizeof(int1_t));
    //         }
    //     }
    //     va_end(vl);
    //     return address;
    // }

    // template<typename T>
    // static void* writeBits(void* address, const Array<T>& array, size_t size_of_each = sizeof(T)) {
    //     int1_t* ptr{ (int1_t*)(address) };
    //     size_t index{ 0 };
    //     for (size_t i{ 0 }, holder{ 0 }; i < array.size(); ++i /* , (ptr += size_of_each) */) {
    //         holder = (size_t)(array[i]);
    //         // printBinary(holder);
    //         for (int j{ 0 }; j < size_of_each; ++j, ++ptr) {
    //             *ptr = (int1_t)(holder >> (8 * j));
    //             // printBinary(ptr, sizeof(int1_t));
    //         }
    //     }
    //     return address;
    // }

    // template<typename T>
    // static void printBinary(const Array<T>& arr) {
    //     // if (!size) return;
    //     putchar('\n');
    //     for (size_t i{ 8 * (arr.size() * sizeof(T)) - 1 };; --i) {
    //         // std::cout << "\nNow:\t" << i << '\n';
    //         putchar('0' + ((*(size_t*)(T*)(arr) >> i) & 1));
    //         // printf("%d", (*(int*)a >> i) & 1);
    //         if (!i) break;
    //     }
    // }

    // template<typename T>
    // static void printBinary(const Array<T>& arr, std::ostream& out = std::cout) {
    //     // if (!size) return;
    //     // for (size_t i{((arr.size() * sizeof(T)) / sizeof(size_t))}; i <) {}
    //     // while ()
    //     for (size_t i{ 8 * (arr.size() * sizeof(T)) - 1 };; --i) {
    //         // std::cout << "\nNow:\t" << i << '\n';
    //         out << ((*(size_t*)(T*)(arr) >> i) & 1);
    //         // printf("%d", (*(int*)a >> i) & 1);
    //         if (!i) break;
    //     }
    // }

    // // template<typename T>
    // // static void printBinary(const T& a) {
    // //     // if (!size) return;
    // //     putchar('\n');
    // //     for (size_t i{ 8 * sizeof(a) - 1 };; --i) {
    // //         putchar('0' + (((size_t)a >> i) & 1));
    // //         // printf("%d", (*(int*)a >> i) & 1);
    // //         if (!i) break;
    // //     }
    // // }

    // template<typename T>
    // static void printBinary(const T* a, size_t size = sizeof(T)) {
    //     // if (!size) return;
    //     putchar('\n');
    //     for (size_t i{ 8 * size - 1 };; --i) {
    //         // std::cout << "\nNow:\t" << i << '\n';
    //         putchar('0' + ((*(size_t*)a >> i) & 1));
    //         // printf("%d", (*(int*)a >> i) & 1);
    //         if (!i) break;
    //     }
    // }

    // template<typename T>
    // static int readChars(FILE* f, T* ptr, size_t count) {
    //     size_t i{ 0 };
    //     for (char* d{ ptr }; i < count; ++i) {
    //         *(d++) = fgetc(f);
    //         if (*(d - 1) == EOF) return -1;
    //     }
    //     return 0;
    // }
};

/*
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
// std::ostream& operator<<(std::ostream& out, const Pixel& pix) {
//     out << "Alpha: " << pix.getA() << "Red: " << pix.getR() << "Green: " << pix.getG() << "Blue: " << pix.getB()
//         << std::endl;
//     return out;
// }

// union Pixel{
//     struct Pixel_
// }
 */
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

#define Type enum Type

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
    /*         DIBHeader() :
                type{ BITMAPINFOHEADER }, header_size{ 0 }, bm_width{ 0 }, bm_height{ 0 }, color_panes{ 0 },
       bits_per_pixel{ 0 }, compression_method{ 0 }, image_size{ 0 }, hor_res{ 0 }, ver_res{ 0 }, is_top_to_bottom{
       false }, num_colours{ 0 }, num_colours_used{ 0 } {} */
    /*         friend std::ostream& operator<<(std::ostream& out, const DIBHeader& d) {
                std::cout << "header_size:\t" << d.header_size << std::endl
                    << "bm_width:\t" << d.bm_width << std::endl
                    << "bm_height:\t" << d.bm_height << std::endl
                    << "color_panes:\t" << d.color_panes << std::endl
                    << "bits_per_pixel:\t" << d.bits_per_pixel << std::endl
                    << "compression_method:\t" << d.compression_method << std::endl
                    << "image_size:\t" << d.image_size << std::endl
                    << "hor_res:\t" << d.hor_res << std::endl
                    << "ver_res:\t" << d.ver_res << std::endl
                    << "is_top_to_bottom:\t" << d.is_top_to_bottom << std::endl
                    << "num_colours:\t" << d.num_colours << std::endl
                    << "num_colours_used:\t" << d.num_colours_used << std::endl;
                return out;
            } */
};

#define Header struct Header
#define BitmapHeader struct BitmapHeader
#define DIBHeader struct DIBHeader
// #

int read(intArray *self, FILE *f, size_t count) {
    resize(self, count);
    fread(self->m_data, 1, count, f);
    // resize(count);
    // size_t i{0};
    // for (char *d{m_data}; i < count; ++i) {
    //     *(d++) = fgetc(f);
    //     if (*(d - 1) == EOF) return -1;
    // }
    return 0;
}

int write(intArray *self, void *f) {
    // resize(self, count);
    memcpy(f, self->m_data, size(self));
    // fread(self->m_data, 1, count, f);
    // resize(count);
    // size_t i{0};
    // for (char *d{m_data}; i < count; ++i) {
    //     *(d++) = fgetc(f);
    //     if (*(d - 1) == EOF) return -1;
    // }
    return 0;
}

struct Bmp {
    Header       h;
    BitmapHeader bh;
    DIBHeader    dh;
    int1_t      *m_data;
    int          a;
    pixArray     pixels;
};

#define Bmp struct Bmp

Bmp *parse(Bmp *self, FILE *f) {
    intArray  str_val;
    intArray *str = &str_val;
    init(str, 4);

    // String   str;
    // readChars()
    // str.readChars(f, 2);
    read(str, f, 2);
    // if (str.operator!=("BM")) throw "Error: not a bmp file.\n";
    if (!strEqC(str, "BM")) fprintf(stderr, "Error: not a bmp file.\n");
    self->bh.field[0] = str->m_data[0];
    self->bh.field[1] = str->m_data[1];
    // char check[2];
    // Binary::readChars(f, check, 2);
    // if (strcmp(check, "BM")) throw "Error: not a bmp file.\n";
    // for (char i{ 0 }, * d{ check }; i < 4; ++i) {
    //     *(d++) = fgetc(f);
    //     Binary::printBinary(check + i, sizeof(char));
    // }
    // putchar(fgetc(f));
    // putchar(fgetc(f));
    // int size = 0;
    // int b{ 0 };
    intArray  arr_val;
    intArray *arr = &arr_val;
    init(arr, 4);
    read(arr, f, 4);
    // arr.readChars(f, 4);
    // Binary::writeBits(&bh.file_size, arr);
    write(arr, &(self->bh.file_size));
    // bh.file_size = 0;
    // str.readChars(f, 4);
    read(str, f, 4);
    // std::cout << str;
    // str.readChars(f, 4);
    read(str, f, 4);

    // std::cout << str;

    // int start_address{};
    // Binary::writeBits(&bh.starting_address, str);
    write(str, &(self->bh.starting_address));
    // std::cout << std::endl << bh.starting_address << std::endl;
    // DIBHeader dh;
    // int header_size;
    // str.readChars(f, 4);
    read(str, f, 4);
    // Binary::writeBits(&dh.header_size, str);
    // self->dh.header_size;
    write(str, &(self->dh.header_size));
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
        // str.readChars(f, 4);
        // Binary::writeBits(&dh.header_size, str);
        // str.readChars(f, 4);
        read(str, f, 4);
        // memcpy(&(self->dh.bm_width), str.m_data, str.size());
        // Binary::writeBits(&(self->dh.bm_width), str);
        write(str, &(self->dh.bm_width));
        // str.readChars(f, 4);
        read(str, f, 4);
        // Binary::writeBits(&(self->dh.bm_height), str) if (dh.bm_height < 0) {
        //     dh.bm_height        = -dh.bm_height;
        //     dh.is_top_to_bottom = true;
        // }
        write(str, &(self->dh.bm_height));

        if ((self->dh.bm_height) < 0) {
            (self->dh.bm_height)        = -(self->dh.bm_height);
            (self->dh.is_top_to_bottom) = true;
        }
        // str.readChars(f, 2);
        read(str, f, 2);
        // Binary::writeBits(&(self->dh.color_panes), str);
        write(str, &(self->dh.color_panes));
        // str.readChars(f, 2);
        // str.readChars(f, 2);
        read(str, f, 2);
        write(str, &(self->dh.bits_per_pixel));
        // str.readChars(f, 4);
        read(str, f, 4);
        write(str, &(self->dh.compression_method));
        // std::cout << "Compression method:\t" << str << std::endl;
        // str.readChars(f, 4);
        read(str, f, 4);
        write(str, &(self->dh.image_size));
        // str.readChars(f, 4);
        read(str, f, 4);
        write(str, &(self->dh.hor_res));
        // str.readChars(f, 4);
        read(str, f, 4);
        write(str, &(self->dh.ver_res));
        // str.readChars(f, 4);
        read(str, f, 4);
        write(str, &(self->dh.num_colours));
        // str.readChars(f, 4);
        read(str, f, 4);
        write(str, &(self->dh.num_colours_used));
        break;
    default:
        // throw "File might be corrupted. \n";
        fprintf(stderr, "File might be corrupted. \n");
    }
    // pixels.resize(((dh.bits_per_pixel * dh.bm_width + 7) / 8) * dh.bm_height);
    // pixels.resize((self->dh.bm_width) * (self->dh.bm_height));
    // self->pixels.resize((self->dh.bm_width) * (self->dh.bm_height));
    resize_pixArr(&(self->pixels), (self->dh.bm_width) * (self->dh.bm_height));
    // std::cout << (((dh.bits_per_pixel * dh.bm_width + 7) / 8) * dh.bm_height);
    // switch (dh.bits_per_pixel) {
    // case 1:
    //     for (int i{ 0 }; i < (dh.bm_width * dh.bm_height); ++i) {
    //         str.readChars(f, dh.bits_per_pixel);
    //         Binary::writeBits(&pixels[i], str);

    //     }
    //     break;
    // case 24:
    //     for (int i{ 0 }; i < (dh.bm_width * dh.bm_height); i += (dh.bits_per_pixel / 8)) {
    //         str.readChars(f, dh.bits_per_pixel);
    //         Binary::writeBits(&pixels[i], str);
    //         std::cout << pixels;


    //     }
    // }

    // std::cout << "HEEEEEEERRRRRRRRRRRRRRRREEEEEEEEEEEEEEEEEE!!!!!!" << dh;


    // for (int i = 0; i < ((self->dh.bm_width) * (self->dh.bm_height)); i += (self->dh.bits_per_pixel / 8)) {
    //     // str.readChars(f, dh.bits_per_pixel);
    //     read(str, f, self->dh.bits_per_pixel);

    //     // Binary::writeBits(&pixels[i], str);
    //     // pixels[i].setBpp(dh.bits_per_pixel);
    //     setBpp(&(self->pixels.m_data[i]), self->dh.bits_per_pixel);
    //     // pixels[i].configString(str);
    //     configString(&(self->pixels.m_data[i]), str);
    //     // std::cout << "Pixel #" << i << ":\t" << pixels[i];
    // }


    for (int i = 0; i < ((self->dh.bm_width) * (self->dh.bm_height)); ++i) {
        // str.readChars(f, dh.bits_per_pixel);
        read(str, f, (self->dh.bits_per_pixel + 7) / 8);

        // Binary::writeBits(&pixels[i], str);
        // pixels[i].setBpp(dh.bits_per_pixel);
        setBpp((self->pixels.m_data) + i, self->dh.bits_per_pixel);
        // pixels[i].configString(str);
        configString((self->pixels.m_data) + i, str);
        // std::cout << "Pixel #" << i << ":\t" << pixels[i];
    }
    // std::cout << pixels[0].getA()

    // std::fstream fs("pixels.txt", std::fstream::out | std::fstream::trunc);

    // Binary::printBinary(pixels, std::cout);
    // Binary::printBinary(pixels, fs);
    // fs << pixels;
    // std::cout << pixels;


    // header[4] = 0;


    // Binary::printBinary((char*)arr, arr.size() * sizeof(char));
    // Binary::printBinary(arr);
    // Binary::writeBits<char>(&size, arr);
    // Binary::printBinary((char*)arr, arr.size() * sizeof(char));


    // char c[4];
    // // Binary::readChars(f, c, 4);
    // for (int i{ 0 }; i < 4; ++i) { c[i] = arr[i]; }
    // // for (char i{ 0 }, * d{ c }; i < 4; ++i) {
    // //     *(d++) = fgetc(f);
    // //     Binary::printBinary(c + i, sizeof(char));
    // // }
    // Binary::printBinary(c, sizeof(c));
    // Binary::writeBits(&size, sizeof(c[0]), 4, c[0], c[1], c[2], c[3]);
    // Binary::printBinary(&size, sizeof(size));
    // printf("%d", size);


    // return *this;
    return self;
}

void fill(Bmp *self, size_t x0, size_t y0, size_t x1, size_t y1, const intArray *str, int1_t opacity) {

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
    for (size_t x = x0; x <= x1; ++x) {
        // for (size_t y = y0; y <= y1; ++y) { self->pixels.m_data[y * self->dh.bm_width + x].configString(str); }
        for (size_t y = y0; y <= y1; ++y) {
            configString(&(self->pixels.m_data[y * self->dh.bm_width + x]), str);
            printf("%lu / %lld\n", y * self->dh.bm_width + x, size_pixarr(&self->pixels));
        }
    }
    return;
}
void write_bmp(Bmp *self, const intArray *name) { FILE *f = fopen(name->m_data, "w+"); 
    
}

/*
class Bmp {
    // protected:
    // int1_t* m_header;
    int1_t *m_data;
    /*     struct Header {
            int a;
        };
        struct BitmapHeader {
            int1_t       field[2];
            int          file_size;
            unsigned int res1;
            unsigned int res2;
            int          starting_address;
        } bh;
        struct DIBHeader {
            enum Type {
                BITMAPCOREHEADER,
                OS22XBITMAPHEADER,
                BITMAPINFOHEADER,
                BITMAPV2INFOHEADER,
                BITMAPV3INFOHEADER,
                BITMAPV4HEADER,
                BITMAPV5HEADER,
            } type;
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
            DIBHeader() :
                type{ BITMAPINFOHEADER }, header_size{ 0 }, bm_width{ 0 }, bm_height{ 0 }, color_panes{ 0 },
       bits_per_pixel{ 0 }, compression_method{ 0 }, image_size{ 0 }, hor_res{ 0 }, ver_res{ 0 }, is_top_to_bottom{
       false }, num_colours{ 0 }, num_colours_used{ 0 } {} friend std::ostream& operator<<(std::ostream& out, const
       DIBHeader& d) { std::cout << "header_size:\t" << d.header_size << std::endl
                    << "bm_width:\t" << d.bm_width << std::endl
                    << "bm_height:\t" << d.bm_height << std::endl
                    << "color_panes:\t" << d.color_panes << std::endl
                    << "bits_per_pixel:\t" << d.bits_per_pixel << std::endl
                    << "compression_method:\t" << d.compression_method << std::endl
                    << "image_size:\t" << d.image_size << std::endl
                    << "hor_res:\t" << d.hor_res << std::endl
                    << "ver_res:\t" << d.ver_res << std::endl
                    << "is_top_to_bottom:\t" << d.is_top_to_bottom << std::endl
                    << "num_colours:\t" << d.num_colours << std::endl
                    << "num_colours_used:\t" << d.num_colours_used << std::endl;
                return out;
            }
        } dh; **
Array<Pixel> pixels{0};

public:
int a;

Bmp &parse(FILE *f) {
    String str;
    str.readChars(f, 2);
    if (str.operator!=("BM")) throw "Error: not a bmp file.\n";
    bh.field[0] = str[0];
    bh.field[1] = str[1];
    // char check[2];
    // Binary::readChars(f, check, 2);
    // if (strcmp(check, "BM")) throw "Error: not a bmp file.\n";
    // for (char i{ 0 }, * d{ check }; i < 4; ++i) {
    //     *(d++) = fgetc(f);
    //     Binary::printBinary(check + i, sizeof(char));
    // }
    // putchar(fgetc(f));
    // putchar(fgetc(f));
    // int size = 0;
    // int b{ 0 };
    String arr{4};
    arr.readChars(f, 4);
    Binary::writeBits(&bh.file_size, arr);
    // bh.file_size = 0;
    str.readChars(f, 4);
    // std::cout << str;
    str.readChars(f, 4);
    std::cout << str;
    // int start_address{};
    Binary::writeBits(&bh.starting_address, str);
    std::cout << std::endl << bh.starting_address << std::endl;
    // DIBHeader dh;
    // int header_size;
    str.readChars(f, 4);
    Binary::writeBits(&dh.header_size, str);
    switch (dh.header_size) {
    case 12: dh.type = dh.BITMAPCOREHEADER; break;
    case 64:
    case 16: dh.type = dh.OS22XBITMAPHEADER; break;
    case 40: dh.type = dh.OS22XBITMAPHEADER; goto after;
    case 52: dh.type = dh.OS22XBITMAPHEADER; goto after;
    case 56: dh.type = dh.OS22XBITMAPHEADER; goto after;
    case 108: dh.type = dh.OS22XBITMAPHEADER; goto after;
    case 124:
        dh.type = dh.OS22XBITMAPHEADER;
        goto after;
    after:
        // str.readChars(f, 4);
        // Binary::writeBits(&dh.header_size, str);
        str.readChars(f, 4);
        memcpy(&dh.bm_width, str.m_data, str.size());
        Binary::writeBits(&dh.bm_width, str);
        str.readChars(f, 4);
        Binary::writeBits(&dh.bm_height, str) if (dh.bm_height < 0) {
            dh.bm_height        = -dh.bm_height;
            dh.is_top_to_bottom = true;
        }
        str.readChars(f, 2);
        Binary::writeBits(&dh.color_panes, str);
        str.readChars(f, 2);
        Binary::writeBits(&dh.bits_per_pixel, str);
        str.readChars(f, 4);
        Binary::writeBits(&dh.compression_method, str);
        std::cout << "Compression method:\t" << str << std::endl;
        str.readChars(f, 4);
        Binary::writeBits(&dh.image_size, str);
        str.readChars(f, 4);
        Binary::writeBits(&dh.hor_res, str);
        str.readChars(f, 4);
        Binary::writeBits(&dh.ver_res, str);
        str.readChars(f, 4);
        Binary::writeBits(&dh.num_colours, str);
        str.readChars(f, 4);
        Binary::writeBits(&dh.num_colours_used, str);
        break;
    default: throw "File might be corrupted. \n";
    }
    // pixels.resize(((dh.bits_per_pixel * dh.bm_width + 7) / 8) * dh.bm_height);
    pixels.resize(dh.bm_width * dh.bm_height);
    // std::cout << (((dh.bits_per_pixel * dh.bm_width + 7) / 8) * dh.bm_height);
    // switch (dh.bits_per_pixel) {
    // case 1:
    //     for (int i{ 0 }; i < (dh.bm_width * dh.bm_height); ++i) {
    //         str.readChars(f, dh.bits_per_pixel);
    //         Binary::writeBits(&pixels[i], str);

    //     }
    //     break;
    // case 24:
    //     for (int i{ 0 }; i < (dh.bm_width * dh.bm_height); i += (dh.bits_per_pixel / 8)) {
    //         str.readChars(f, dh.bits_per_pixel);
    //         Binary::writeBits(&pixels[i], str);
    //         std::cout << pixels;


    //     }
    // }

    std::cout << "HEEEEEEERRRRRRRRRRRRRRRREEEEEEEEEEEEEEEEEE!!!!!!" << dh;
    for (int i{0}; i < (dh.bm_width * dh.bm_height); i += (dh.bits_per_pixel / 8)) {
        str.readChars(f, dh.bits_per_pixel);

        // Binary::writeBits(&pixels[i], str);
        pixels[i].setBpp(dh.bits_per_pixel);
        pixels[i].configString(str);
        std::cout << "Pixel #" << i << ":\t" << pixels[i];
    }
    // std::cout << pixels[0].getA()
    std::fstream fs("pixels.txt", std::fstream::out | std::fstream::trunc);
    // Binary::printBinary(pixels, std::cout);
    // Binary::printBinary(pixels, fs);
    // fs << pixels;
    // std::cout << pixels;


    // header[4] = 0;


    // Binary::printBinary((char*)arr, arr.size() * sizeof(char));
    // Binary::printBinary(arr);
    // Binary::writeBits<char>(&size, arr);
    // Binary::printBinary((char*)arr, arr.size() * sizeof(char));


    // char c[4];
    // // Binary::readChars(f, c, 4);
    // for (int i{ 0 }; i < 4; ++i) { c[i] = arr[i]; }
    // // for (char i{ 0 }, * d{ c }; i < 4; ++i) {
    // //     *(d++) = fgetc(f);
    // //     Binary::printBinary(c + i, sizeof(char));
    // // }
    // Binary::printBinary(c, sizeof(c));
    // Binary::writeBits(&size, sizeof(c[0]), 4, c[0], c[1], c[2], c[3]);
    // Binary::printBinary(&size, sizeof(size));
    // printf("%d", size);


    return *this;
}

// TODO!: continue from here onwards.

void fill(size_t x0, size_t y0, size_t x1, size_t y1, const String &str, int1_t opacity) {

    if (x0 > x1) {
        size_t a = x0;
        x0            = x1;
        x1            = a;
    }
    if (y0 > y1) {
        size_t a = y0;
        y0            = y1;
        y1            = a;
    }
    for (size_t x = x0; x <= x1; ++x) {
        for (size_t y = y0; y <= y1; ++y) { pixels[y * dh.bm_width + x].configString(str); }
    }
    return;
}
void write(const String &name) { FILE *f = fopen(name.c_str(), "w+"); }
}
;
*/

int main(void) {
    // int   a;
    FILE *f = fopen("../rainbow copy.bmp", "r");
    // String     s{"hellos"}, ss{" world!\n"};
    // intArray   s, ss;
    // init(s);
    // init_cstr(ss)
    // Array<int> b{1, 2, 3, 6, 3, 6, 83, 24, 6}, c{124, 43, 5, 4, 346, 32};
    // Array<int> d(b + c);
    // std::cout << s << ss << (s + ss) << b << c << (b + c) << std::endl
    //           << d << std::endl
    //           << d.sort() << std::endl
    //           << s.sort();
    Bmp bmp1;
    init_pix(&bmp1.pixels, 0);
    // fgetc(f);
    parse(&bmp1, f);
    intArray black;
    init(&black, 3);
    for (size_t i = 0; i < 3; ++i) { black.m_data[i] = 0; }
    fill(&bmp1, 100, 100, 121, 121, &black, (char)(127));
    // bmp1.parse(f);
    // while ((a = fgetc(f)) != -1) {
    //     // printf("%d ", a);
    //     putchar(a);
    // }

    // for (int i{ 0 }; i < 4; ++i) {
    //     size <<= 8;
    //     b = fgetc(f);
    //     printBinary(&b, sizeof(char));
    //     size |= (int)b;
    //     printBinary(&size, sizeof(int));
    // }
    // printf("%d\t", size);
    // printBinary(&size, sizeof(size));
    // printf("%d\t", fgetc(f));
    // printf("%d\t", fgetc(f));
    // printf("%d\t", fgetc(f));
    // printf("%d\t", fgetc(f));
    return 0;

    // Call destructors for all the arrays
}
