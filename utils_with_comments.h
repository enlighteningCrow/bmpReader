#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long int size_ut;
typedef char int1_t;
// typedef int bool;

// template<class int1_t>

struct intArray {
    // protected:
    size_ut  m_size;
    size_ut  m_allocated;
    int1_t* m_data;
    /* mutable */ bool m_is_sorted;
    size_ut         _middle;
    // friend class String;

    // virtual void _print(std::ostream& out) const {
    //     out << ("{");
    //     for (int i{ 0 }; i < m_size; ++i) {
    //         if (i) out << (',');
    //         out << ' ' << m_data[i];
    //     }
    //     out << (" }");
    // }
    // virtual void _print(FILE& out) const {
    //     out << ("{");
    //     for (int i{ 0 }; i < m_size; ++i) {
    //         if (i) out << (',');
    //         out << ' ' << m_data[i];
    //     }
    //     out << (" }");
    // }

// public:
    /*
    Array(Array<T>& array)
        : m_size{ array.m_size }
        , m_allocated{ array.m_allocated }
        , m_data{ array.m_data }
        , m_is_sorted{ m_is_sorted }
        , _middle{ 0 }
    {
        array.m_data = NULL;
    }
    Array(const Array<T>& array)
        : m_size{ array.m_size }
        , m_allocated{ array.m_allocated }
        , m_data{ array.m_data }
        , m_is_sorted{ array.m_is_sorted }
        , _middle{ 0 }
    {
        memcpy(m_data, array.m_data, m_size * sizeof(T));
    } */
    /*     intArray(intArray& array) :
            m_size{ array.m_size }, m_allocated{ array.m_allocated }, m_data{ (int1_t*)malloc(sizeof(int1_t) * array.m_size) },
            m_is_sorted{ array.m_is_sorted }, _middle{ 0 } {
            memcpy(m_data, array.m_data, m_size * sizeof(int1_t));
            // array.m_data = NULL;
        }
        intArray(intArray&& array) :
            m_size{ array.m_size }, m_allocated{ array.m_allocated }, m_data{ array.m_data },
            m_is_sorted{ array.m_is_sorted }, _middle{ 0 } {
            array.m_data = NULL;
            // memcpy(m_data, array.m_data, m_size * sizeof(T));
        }
        intArray(size_ut size) :
            m_size{ size }, m_allocated{ (size_ut)(size * 1.3 + 1) }, m_data{ (int1_t*)(malloc(sizeof(int1_t) * m_allocated)) },
            m_is_sorted{ false }, _middle{ 0 } {
            memset(m_data, 0, sizeof(int1_t)* m_size);
        }
        intArray() : intArray(0UL) {}
        intArray(const std::initializer_list<T>& list) :
            m_size{ list.size() }, m_allocated{ (size_ut)(m_size * 1.3 + 1) },
            m_data{ (int1_t*)(malloc(sizeof(int1_t) * m_allocated)) }, m_is_sorted{ false } {
            int j{ 0 };
            for (const int1_t& i : list) {
                m_data[j] = i;
                ++j;
            }
        }
    virtual ~intArray() { free(m_data); } */
    // explicit operator int1_t* () const { return m_data; }
    //   friend std::ostream& operator<<(std::ostream& out, const Array<T>& arr) {
    //       for (int i{ 0 }; i < arr.size(); ++i) {
    //           out << i;
    //       }
    //       return arr;
    //   }
};

#define intArray struct intArray

size_ut size(intArray* self);
intArray* resize(intArray* self, size_ut size);

intArray* remove(intArray* self, size_ut start, size_ut end);

intArray* insert(intArray* self, int1_t value, size_ut index);

// NOTE!!!!!: this replace is NON-INCLUSIVE, like for loops.
intArray* replace(intArray* self, int1_t value, size_ut start, size_ut end);

intArray* pop_front(intArray* self, size_ut indexes = 1ULL);

intArray* push_front(intArray* self, int1_t val);

size_ut find(intArray* self, int1_t target);
size_ut findGreater(intArray* self, int1_t target);
size_ut findGreaterEq(intArray* self, int1_t target);
size_ut findLesser(intArray* self, int1_t target);
size_ut findLesserEq(intArray* self, int1_t target);

intArray* clear(intArray* self);
size_ut _find(intArray* self, int1_t target, size_ut left, size_ut right);
size_ut _findg(intArray* self, int1_t target, size_ut left, size_ut right);
size_ut _findl(intArray* self, int1_t target, size_ut left, size_ut right);
size_ut _findge(intArray* self, int1_t target, size_ut left, size_ut right);
size_ut _findle(intArray* self, int1_t target, size_ut left, size_ut right);
intArray* push_back(intArray* self, int1_t element);
intArray* pop_back(intArray* self);

intArray* sort(intArray* self);