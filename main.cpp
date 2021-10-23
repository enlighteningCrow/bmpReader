#include <alloca.h>
#include <bits/stdc++.h>
#include <cstring>
#include <fenv.h>
#include <initializer_list>
#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// #define int1_t char
typedef char int1_t;

// void printBinary(void* a, std::size_t size) {
//     if (!size) return;
//     putchar('\n');
//     for (int i{ 8 * (int)size - 1 }; i >= 0; --i) {
//         putchar('0' + ((*(std::size_t*)a >> i) & 1));
//         // printf("%d", (*(int*)a >> i) & 1);
//     }
// }

class Pixel;

template<typename T>
class Array {
protected:
    std::size_t m_size;
    std::size_t m_allocated;
    T *         m_data;
    friend class String;
    virtual void _print(std::ostream &out) const {
        // printf("{");
        // for (int i{ 0 }; i < m_size; ++i) {
        //     if (i) putchar(',');
        //     printf(" %d", m_data[i]);
        // }
        // printf(" }");
        out << ("{");
        for (int i{0}; i < m_size; ++i) {
            if (i) out << (',');
            out << ' ' << m_data[i];
        }
        out << (" }");
    }

public:
    Array(Array<T> &array) : m_size{array.m_size}, m_allocated{array.m_allocated}, m_data{array.m_data} {
        array.m_data = NULL;
    }
    Array(const Array<T> &array) : m_size{array.m_size}, m_allocated{array.m_allocated}, m_data{array.m_data} {
        memcpy(m_data, array.m_data, m_size * sizeof(T));
    }
    Array(std::size_t size) :
        m_size{size}, m_allocated{(std::size_t)(m_size * 1.3 + 1)}, m_data{(T *)(malloc(sizeof(T) * m_allocated))} {
        memset(m_data, 0, sizeof(T) * m_size);
    }
    Array(const std::initializer_list<T> &list) :
        m_size{list.size()}, m_allocated{(std::size_t)(m_size * 1.3 + 1)}, m_data{
                                                                               (T *)(malloc(sizeof(T) * m_allocated))} {
        int j{0};
        for (const T &i : list) {
            m_data[j] = i;
            ++j;
        }
    }
    virtual ~Array() { free(m_data); }
    virtual std::size_t size() const { return m_size; }
    Array<T> &          resize(std::size_t size) {
        if (m_size == size) return *this;
        bool expanded{(m_allocated < size)};
        if ((m_allocated < size) || ((std::size_t)(m_allocated * 0.7 + 1) > size)) {
            m_allocated = (std::size_t)((size * 1.3) + 1);
        }
        else {
            m_size = size;
            return *this;
        }
        T *tmp{(T *)(realloc(m_data, (sizeof(T) * m_allocated)))};
        if (tmp != NULL) m_data = tmp;
        if (expanded) {
            memset(m_data + m_size, 0, (size - m_size) * sizeof(T));
            if (tmp == NULL) throw "Out of memory.\n";
        }
        m_data = tmp;
        m_size = size;
        return *this;
    }
    T &operator[](std::size_t index) const {
        if (index < 0) index += m_size;
        if (index >= m_size || index < 0) throw "Out of range.\n";
        return m_data[index];
    }
    Array<T> operator+(const Array<T> &array) const {
        Array<T> arr(m_size + array.m_size);
        memcpy(arr.m_data, m_data, m_size * sizeof(T));
        memcpy(arr.m_data + m_size, array.m_data, array.m_size * sizeof(T));
        return arr;
    }
    Array<T> &operator+=(const Array<T> &array) {
        std::size_t old_size{m_size};
        resize(m_size + array.m_size);
        memcpy(m_data + old_size, array.m_data, array.m_size * sizeof(T));
        return *this;
    }
    Array<T> &operator=(const Array<T> &array) {
        resize(array.m_size);
        memcpy(m_data, array.m_data, array.m_size * sizeof(T));
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &out, const Array<T> &arr) {
        arr._print(out);
        return out;
    }

protected:
    // TODO: edit the comparison function!!!!
public:
    Array<T> &sort() {
        qsort(m_data, m_size, sizeof(T), [](const void *a, const void *b) -> int {
            // std::cout << a << " is " << ((*((T*)(a)) < *((T*)(a))) ? "less than" : "more than or equal to") << b;
            return *((T *)(a)) > *((T *)(b));
        });
        return *this;
    }
    inline bool operator==(const Array<T> &arr) const {
        if (m_size != arr.m_size) return 0;
        return !(memcmp(m_data, arr.m_data, m_size));
    }
    inline bool operator!=(const Array<T> &arr) const {
        if (m_size != arr.m_size) return 1;
        return (memcmp(m_data, arr.m_data, m_size));
    }
    operator T *() const { return m_data; }
};

// template<typename T = char>
class String : public Array<char> {
protected:
    friend class Pixel;
    virtual void _print(std::ostream &out) const override {
        for (int i{0}; i < m_size; ++i) {
            if (m_data[i] == '\0') return;
            out << (m_data[i]);
        }
        return;
    }
    String(String &array) : Array<char>{array} {}

public:
    String(std::size_t size) : Array(size) {}
    String(const char *str) : Array<char>((std::size_t)strlen(str)) { strcpy(m_data, str); }
    String() : Array<char>(0UL) {}
    String operator+(String &array) const {
        String arr{m_size + array.m_size};
        memcpy(arr.m_data, m_data, m_size);
        memcpy(arr.m_data + m_size, array.m_data, array.m_size);
        return arr;
    }
    String operator+(const char *array) const {
        String arr{m_size + strlen(array)};
        memcpy(arr.m_data, m_data, m_size);
        strcpy(arr.m_data + m_size, array);
        return arr;
    }
    String operator+(char ch) const {
        String arr{m_size + 1};
        memcpy(arr.m_data, m_data, m_size);
        arr.m_data[m_size] = ch;
        return arr;
    }
    String &operator+=(String &array) {
        std::size_t old_size{m_size};
        resize(m_size + array.m_size);
        memcpy(m_data + old_size, array.m_data, array.m_size);
        return *this;
    }
    String &operator+=(const char *array) {
        std::size_t old_size{m_size};
        resize(m_size + strlen(array));
        strcpy(m_data + old_size, array);
        return *this;
    }
    String &operator+=(char ch) {
        std::size_t old_size{m_size};
        resize(m_size + 1);
        m_data[old_size] = ch;
        return *this;
    }
    String &operator=(String &array) {
        resize(array.m_size);
        memcpy(m_data, array.m_data, array.m_size);
        return *this;
    }
    String &operator=(const char *array) {
        resize(strlen(array));
        strcpy(m_data, array);
        return *this;
    }
    String &operator=(char ch) {
        resize(1);
        m_data[0] = ch;
        return *this;
    }
    inline bool operator==(const String &arr) const {
        if (m_size != arr.m_size) return 0;
        return !(memcmp(m_data, arr.m_data, m_size));
    }
    inline bool operator!=(const String &arr) const {
        if (m_size != arr.m_size) return 1;
        return (memcmp(m_data, arr.m_data, m_size));
    }
        operator char *() const { return m_data; }
    int readChars(FILE *f, std::size_t count) {
        resize(count);
        std::size_t i{0};
        for (char *d{m_data}; i < count; ++i) {
            *(d++) = fgetc(f);
            if (*(d - 1) == EOF) return -1;
        }
        return 0;
    }
    // friend std::ostream& operator<<(std::ostream& out, const String& str) {
    //     str._print();
    //     return out;
    // }
};

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
//     String(std::size_t size) : Array(size) {}
//     String(const char* str) : Array<char>((std::size_t)strlen(str)) {
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
//         std::size_t old_size{ strlen(m_data) };
//         resize(strlen(m_data) + strlen(array.m_data));
//         strcpy(m_data + old_size, array.m_data);
//         return *this;
//     }
//     String& operator+= (const char* array) {
//         std::size_t old_size{ strlen(m_data) };
//         resize(strlen(m_data) + strlen(array));
//         strcpy(m_data + old_size, array);
//         return *this;
//     }
//     String& operator+= (char ch) {
//         std::size_t old_size{ strlen(m_data) };
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
class Binary {
protected:
    std::size_t     size;
    std::size_t     allocated;
    decltype(0ULL) *m_data;

public:
    static void *writeBits(void *address, std::size_t size_of_each, std::size_t count, ...) {
        va_list vl;
        va_start(vl, count);
        int1_t *    ptr{(int1_t *)(address)};
        std::size_t index{0};
        for (std::size_t i{0}, holder{0}; i < count; ++i /* , (ptr += size_of_each) */) {
            holder = va_arg(vl, std::size_t);
            // printBinary(holder);
            for (int j{0}; j < size_of_each; ++j, ++ptr) {
                *ptr = (int1_t)(holder >> (8 * j));
                // printBinary(ptr, sizeof(int1_t));
            }
        }
        va_end(vl);
        return address;
    }

    template<typename T>
    static void *writeBits(void *address, const Array<T> &array, std::size_t size_of_each = sizeof(T)) {
        int1_t *    ptr{(int1_t *)(address)};
        std::size_t index{0};
        for (std::size_t i{0}, holder{0}; i < array.size(); ++i /* , (ptr += size_of_each) */) {
            holder = (std::size_t)(array[i]);
            // printBinary(holder);
            for (int j{0}; j < size_of_each; ++j, ++ptr) {
                *ptr = (int1_t)(holder >> (8 * j));
                // printBinary(ptr, sizeof(int1_t));
            }
        }
        return address;
    }

    template<typename T>
    static void printBinary(const Array<T> &arr) {
        // if (!size) return;
        putchar('\n');
        for (std::size_t i{8 * (arr.size() * sizeof(T)) - 1};; --i) {
            // std::cout << "\nNow:\t" << i << '\n';
            putchar('0' + ((*(std::size_t *)(T *)(arr) >> i) & 1));
            // printf("%d", (*(int*)a >> i) & 1);
            if (!i) break;
        }
    }

    template<typename T>
    static void printBinary(const Array<T> &arr, std::ostream &out = std::cout) {
        // if (!size) return;
        for (std::size_t i{((arr.size() * sizeof(T)) / sizeof(std::size_t))}; i <) {}
        // while ()
        for (std::size_t i{8 * (arr.size() * sizeof(T)) - 1};; --i) {
            // std::cout << "\nNow:\t" << i << '\n';
            out << ((*(std::size_t *)(T *)(arr) >> i) & 1);
            // printf("%d", (*(int*)a >> i) & 1);
            if (!i) break;
        }
    }

    // template<typename T>
    // static void printBinary(const T& a) {
    //     // if (!size) return;
    //     putchar('\n');
    //     for (std::size_t i{ 8 * sizeof(a) - 1 };; --i) {
    //         putchar('0' + (((std::size_t)a >> i) & 1));
    //         // printf("%d", (*(int*)a >> i) & 1);
    //         if (!i) break;
    //     }
    // }

    template<typename T>
    static void printBinary(const T *a, std::size_t size = sizeof(T)) {
        // if (!size) return;
        putchar('\n');
        for (std::size_t i{8 * size - 1};; --i) {
            // std::cout << "\nNow:\t" << i << '\n';
            putchar('0' + ((*(std::size_t *)a >> i) & 1));
            // printf("%d", (*(int*)a >> i) & 1);
            if (!i) break;
        }
    }

    template<typename T>
    static int readChars(FILE *f, T *ptr, std::size_t count) {
        std::size_t i{0};
        for (char *d{ptr}; i < count; ++i) {
            *(d++) = fgetc(f);
            if (*(d - 1) == EOF) return -1;
        }
        return 0;
    }
};

class Pixel : public Array<int1_t> {
protected:
    // Array<int1_t> m_array;
    int1_t m_bpp;

public:
    Pixel() : Array(0), m_bpp{0} {}
    Pixel(const Pixel &pixel) : Array(pixel.m_size), m_bpp{0} { memcpy(m_data, pixel.m_data, pixel.m_size); }
    Pixel &fill(int1_t bpp, Array<int1_t> &array) {
        m_bpp = bpp;
        if (array.size() != ((bpp + 7) / 8)) throw "Size of array and from bpp not equal!\n";
        resize(array.size());
        memcpy(m_data, (int1_t *)array, array.size());
    }
    Pixel &operator=(const Pixel &pixel) {
        resize(pixel.m_size);
        // m_size = pixel.m_size;
        memcpy(m_data, pixel.m_data, pixel.m_size);
    }
    // Bpp stands for bits per pixel
    Pixel &setBpp(int1_t bpp) {
        m_bpp = bpp;
        resize((bpp + 7) / 8);
        return *this;
    }

    Pixel &configString(const String &str) {
        memcpy(m_data, str.m_data, str.size());
        //std::memcpy(m_data, )
        //fill()
    }
    Pixel &setColour(int1_t colour, int1_t index) { m_data[index] = colour; }

    Pixel &setA(int1_t colour) {
        if (m_bpp < 24) throw "Alpha channel not supported in this bitmap file. \n";
        setColour(colour, 0);
    }
    Pixel &setR(int1_t colour) { setColour(colour, m_bpp >= 24 ? (m_bpp >= 32 ? 1 : 0) : 0); }
    Pixel &setG(int1_t colour) { setColour(colour, m_bpp >= 24 ? (m_bpp >= 32 ? 2 : 1) : 1); }
    Pixel &setB(int1_t colour) { setColour(colour, m_bpp >= 24 ? (m_bpp >= 32 ? 3 : 2) : 2); }

    int1_t &getA() {
        if (m_bpp < 24) throw "Alpha channel not supported in this bitmap file. \n";
        //setColour(colour, 0);
        return m_data[0];

    }
    int1_t &getR() { 
        //setColour(colour, m_bpp >= 24 ? (m_bpp >= 32 ? 1 : 0) : 0);
        return m_data[m_bpp >= 24 ? (m_bpp >= 32 ? 1 : 0) : 0];
    }
    int1_t &getG() { 
        //setColour(colour, m_bpp >= 24 ? (m_bpp >= 32 ? 2 : 1) : 1); 
        return m_data[m_bpp >= 24 ? (m_bpp >= 32 ? 2 : 1) : 1]; 
    }
    int1_t &getB() { 
        //setColour(colour, m_bpp >= 24 ? (m_bpp >= 32 ? 3 : 2) : 2); 
        return m_data[m_bpp >= 24 ? (m_bpp >= 32 ? 3 : 2) : 2];
    }
};

// union Pixel{
//     struct Pixel_
// }

class Bmp {
protected:
    // int1_t* m_header;
    int1_t *m_data;
    struct Header {
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
            type{BITMAPINFOHEADER}, header_size{0}, bm_width{0}, bm_height{0}, color_panes{0}, bits_per_pixel{0},
            compression_method{0}, image_size{0}, hor_res{0}, ver_res{0}, is_top_to_bottom{false}, num_colours{0},
            num_colours_used{0} {}
    } dh;
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
            Binary::writeBits(&dh.bm_width, str);
            str.readChars(f, 4);
            Binary::writeBits(&dh.bm_height, str);
            if (dh.bm_height < 0) {
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


        for (int i{0}; i < (dh.bm_width * dh.bm_height); i += (dh.bits_per_pixel / 8)) {
            str.readChars(f, dh.bits_per_pixel);

            // Binary::writeBits(&pixels[i], str);
            pixels[i].setBpp(dh.bits_per_pixel);
            pixels[i].configString(str);
        }
        std::fstream fs("pixels.txt", std::fstream::out | std::fstream::trunc);
        Binary::printBinary(pixels, std::cout);
        Binary::printBinary(pixels, fs);
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
    void fill(std::size_t x0, std::size_t y0, std::size_t x1, std::size_t y1, const String& str) {

        if (x0 > x1) {
            std::size_t a = x0;
            x0            = x1;
            x1            = a;
        }
        if (y0 > y1) {
            std::size_t a = y0;
            y0            = y1;
            y1            = a;
        }
        for (std::size_t x = x0; x <= x1; ++x) {
            for (std::size_t y = y0; y <= y1; ++y) {
                pixels[y * dh.bm_width + x].configString(str);
            }
        }
        return;
    }
};

int main(void) {
    int        a;
    FILE *     f{fopen("rainbow.bmp", "rb")};
    String     s{"hellos"}, ss{" world!\n"};
    Array<int> b{1, 2, 3, 6, 3, 6, 83, 24, 6}, c{124, 43, 5, 4, 346, 32};
    Array<int> d(b + c);
    std::cout << s << ss << (s + ss) << b << c << (b + c) << std::endl
              << d << std::endl
              << d.sort() << std::endl
              << s.sort();
    Bmp bmp1;
    bmp1.parse(f);
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
}
