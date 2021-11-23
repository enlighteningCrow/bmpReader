#ifndef UTILS_CPTR_H
#define UTILS_CPTR_H

// #include "pixel.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long int size_ut;
typedef char          int1_t;
typedef int1_t       *int1_t_ptr;

struct cptrArray {
    size_ut     m_size;
    size_ut     m_allocated;
    int1_t_ptr *m_data;
    bool        m_is_sorted;
    size_ut     _middle;
};

// #define cptrArray struct cptrArray
typedef struct cptrArray cptrArray;

size_t     size_cptr(const cptrArray *self);
cptrArray *resize_cptr(cptrArray *self, size_ut size);

cptrArray *remove_arr_cptr(cptrArray *self, size_ut start, size_ut end);

cptrArray *insert_cptr(cptrArray *self, int1_t_ptr value, size_ut index);


cptrArray *replace_cptr(cptrArray *self, int1_t_ptr value, size_ut start, size_ut end);

cptrArray *pop_front_cptr(cptrArray *self, size_ut indexes);

cptrArray *push_front_cptr(cptrArray *self, int1_t_ptr val);

size_ut find_cptr(cptrArray *self, int1_t_ptr target);
size_ut findGreater_cptr(cptrArray *self, int1_t_ptr target);
size_ut findGreaterEq_cptr(cptrArray *self, int1_t_ptr target);
size_ut findLesser_cptr(cptrArray *self, int1_t_ptr target);
size_ut findLesserEq_cptr(cptrArray *self, int1_t_ptr target);

cptrArray *clear_cptr(cptrArray *self);
size_ut    _find_cptr(cptrArray *self, int1_t_ptr target, size_ut left, size_ut right);
size_ut    _findg_cptr(cptrArray *self, int1_t_ptr target, size_ut left, size_ut right);
size_ut    _findl_cptr(cptrArray *self, int1_t_ptr target, size_ut left, size_ut right);
size_ut    _findge_cptr(cptrArray *self, int1_t_ptr target, size_ut left, size_ut right);
size_ut    _findle_cptr(cptrArray *self, int1_t_ptr target, size_ut left, size_ut right);
cptrArray *push_back_cptr(cptrArray *self, int1_t_ptr element);
cptrArray *pop_back_cptr(cptrArray *self);

cptrArray *sort_cptr(cptrArray *self);
// bool       strEq_cptr(const cptrArray *self, const cptrArray *arr);
// bool       strEqC_cptr(const cptrArray *self, const char *arr);
// cptrArray *concat_cptr(const cptrArray *self, const cptrArray *arr);
// cptrArray *concatEq_cptr(cptrArray *self, const cptrArray *arr);

// cptrArray *strAssign_cptr(cptrArray *self, const cptrArray *arr);
// cptrArray *strAssignC_cptr(cptrArray *self, const char *arr);
// const char *c_str(cptrArray *self);

cptrArray *fprint_cptr(cptrArray *self, FILE *f);

void init_cptr(cptrArray *self, size_ut size);
void dest_cptr(cptrArray *self);

// size_ut round_near(double n);

#endif // UTILS_CPTR_H
