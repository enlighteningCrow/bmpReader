#ifndef UTILS_CPTR_H
#define UTILS_CPTR_H

// #include "pixel.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef long long int size_t;
typedef char    int1_t;
typedef int1_t *int1_t_ptr;

struct cptrArray {
    size_t      m_size;
    size_t      m_allocated;
    int1_t_ptr *m_data;
    bool        m_is_sorted;
    size_t      _middle;
};

// #define cptrArray struct cptrArray
typedef struct cptrArray cptrArray;

size_t     size_cptr(const cptrArray *self);
cptrArray *resize_cptr(cptrArray *self, size_t size);

cptrArray *remove_arr_cptr(cptrArray *self, size_t start, size_t end);

cptrArray *insert_cptr(cptrArray *self, int1_t_ptr value, size_t index);


cptrArray *replace_cptr(cptrArray *self, int1_t_ptr value, size_t start, size_t end);

cptrArray *pop_front_cptr(cptrArray *self, size_t indexes);

cptrArray *push_front_cptr(cptrArray *self, int1_t_ptr val);

size_t find_cptr(cptrArray *self, int1_t_ptr target);
size_t findGreater_cptr(cptrArray *self, int1_t_ptr target);
size_t findGreaterEq_cptr(cptrArray *self, int1_t_ptr target);
size_t findLesser_cptr(cptrArray *self, int1_t_ptr target);
size_t findLesserEq_cptr(cptrArray *self, int1_t_ptr target);

cptrArray *clear_cptr(cptrArray *self);
size_t     _find_cptr(cptrArray *self, int1_t_ptr target, size_t left, size_t right);
size_t     _findg_cptr(cptrArray *self, int1_t_ptr target, size_t left, size_t right);
size_t     _findl_cptr(cptrArray *self, int1_t_ptr target, size_t left, size_t right);
size_t     _findge_cptr(cptrArray *self, int1_t_ptr target, size_t left, size_t right);
size_t     _findle_cptr(cptrArray *self, int1_t_ptr target, size_t left, size_t right);
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

void init_cptr(cptrArray *self, size_t size);
void dest_cptr(cptrArray *self);

// size_ut round_near(double n);

#endif // UTILS_CPTR_H
