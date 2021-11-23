#ifndef UTILS_H
#define UTILS_H


#include "utils_cptr.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define for_each(arr, type, name) for (type *name = (arr)->m_data; name < (arr)->m_data + size(arr); ++name)
#define for_each_pix(arr, type, name) for (type *name = (arr)->m_data; name < (arr)->m_data + size_pix(arr); ++name)

typedef long long int size_ut;
typedef char          int1_t;

struct intArray {
    cptrArray m_ptrs;
    size_ut   m_size;
    size_ut   m_allocated;
    int1_t   *m_data;
    bool      m_is_sorted;
    size_ut   _middle;
};


typedef struct intArray intArray;

size_t    size(const intArray *self);
intArray *resize(intArray *self, size_ut size);


intArray *remove_arr(intArray *self, size_ut start, size_ut end);

intArray *insert(intArray *self, int1_t value, size_ut index);


intArray *replace(intArray *self, int1_t value, size_ut start, size_ut end);

intArray *pop_front(intArray *self, size_ut indexes);

intArray *push_front(intArray *self, int1_t val);

size_ut find(intArray *self, int1_t target);
size_ut findGreater(intArray *self, int1_t target);
size_ut findGreaterEq(intArray *self, int1_t target);
size_ut findLesser(intArray *self, int1_t target);
size_ut findLesserEq(intArray *self, int1_t target);

intArray *clear(intArray *self);
size_ut   _find(intArray *self, int1_t target, size_ut left, size_ut right);
size_ut   _findg(intArray *self, int1_t target, size_ut left, size_ut right);
size_ut   _findl(intArray *self, int1_t target, size_ut left, size_ut right);
size_ut   _findge(intArray *self, int1_t target, size_ut left, size_ut right);
size_ut   _findle(intArray *self, int1_t target, size_ut left, size_ut right);
intArray *push_back(intArray *self, int1_t element);
intArray *pop_back(intArray *self);

intArray *sort(intArray *self);
bool      strEq(const intArray *self, const intArray *arr);
bool      strEqC(const intArray *self, const char *arr);
intArray *concat(const intArray *self, const intArray *arr);
intArray *concatEq(intArray *self, const intArray *arr);

intArray *strAssign(intArray *self, const intArray *arr);
intArray *strAssignC(intArray *self, const char *arr);


intArray *fprint(intArray *self, FILE *f);

void   init(intArray *self, size_ut size);
void   dest(intArray *self);
int1_t readLine(intArray *self, FILE *f);

size_ut round_near(double n);
size_ut round_down(double n);
char   *c_str(intArray *self);

#endif // UTILS_H
