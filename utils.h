#ifndef UTILS_H
#define UTILS_H


#include "utils_cptr.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define for_each(arr, type, name) for (type *name = (arr)->m_data; name < (arr)->m_data + size(arr); ++name)
#define for_each_pix(arr, type, name) for (type *name = (arr)->m_data; name < (arr)->m_data + size_pix(arr); ++name)

// typedef long long int size_t;
typedef char int1_t;

struct intArray {
    cptrArray m_ptrs;
    size_t    m_size;
    size_t    m_allocated;
    int1_t   *m_data;
    bool      m_is_sorted;
    size_t    _middle;
};


typedef struct intArray intArray;

size_t    size(const intArray *self);
intArray *resize(intArray *self, size_t size);


intArray *remove_arr(intArray *self, size_t start, size_t end);

intArray *insert(intArray *self, int1_t value, size_t index);


intArray *replace(intArray *self, int1_t value, size_t start, size_t end);

intArray *pop_front(intArray *self, size_t indexes);

intArray *push_front(intArray *self, int1_t val);

size_t find(intArray *self, int1_t target);
size_t findGreater(intArray *self, int1_t target);
size_t findGreaterEq(intArray *self, int1_t target);
size_t findLesser(intArray *self, int1_t target);
size_t findLesserEq(intArray *self, int1_t target);

intArray *clear(intArray *self);
size_t    _find(intArray *self, int1_t target, size_t left, size_t right);
size_t    _findg(intArray *self, int1_t target, size_t left, size_t right);
size_t    _findl(intArray *self, int1_t target, size_t left, size_t right);
size_t    _findge(intArray *self, int1_t target, size_t left, size_t right);
size_t    _findle(intArray *self, int1_t target, size_t left, size_t right);
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

void   init(intArray *self, size_t size);
void   dest(intArray *self);
int1_t readLine(intArray *self, FILE *f);
int1_t readLineThroughSpaces(intArray *self, FILE *f);

size_t round_near(double n);
size_t round_down(double n);
char  *c_str(intArray *self);
void   free_c_str(intArray *self, char *str);

#endif // UTILS_H
