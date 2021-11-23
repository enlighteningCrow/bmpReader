#include "utils_cptr.h"
#include "utils.h"

// #define cptrArray struct cptrArray
typedef struct cptrArray cptrArray;

size_t     size_cptr(const cptrArray *self) { return self->m_size; }
cptrArray *resize_cptr(cptrArray *self, size_ut size) {
    // // printf("Realloc-ing from %llu ", sizeof(int1_t_ptr) * self->m_allocated);
    // if (self->m_size == size) return self;
    // if (!size) {
    //     free(self->m_data);
    //     self->m_data      = NULL;
    //     self->m_size      = size;
    //     self->m_allocated = size;
    //     return self;
    // }
    // bool expanded = (self->m_allocated < size);
    // if ((self->m_allocated < size) || ((size_ut)(self->m_allocated * 0.7 + 1) > size)) {
    //     self->m_allocated = (size_ut)((size * 1.3) + 1);
    // }
    // else {
    //     self->m_size = size;
    //     return self;
    // }
    // // printf("to %llu\n", sizeof(int1_t_ptr) * self->m_allocated);
    // // fflush(stdout);
    // int1_t_ptr *tmp = (int1_t_ptr *)(realloc(self->m_data, (sizeof(int1_t_ptr) * self->m_allocated)));
    // if (tmp != NULL) self->m_data = tmp;
    // if (expanded) {
    //     // memset(self->m_data + self->m_size, 0, (size - self->m_size) * sizeof(int1_t_ptr));
    //     if (tmp == NULL) {
    //         fprintf(stderr, "Out of memory.\n");
    //         return self;
    //     }

    //     self->m_is_sorted = false;
    // }
    // // self->m_data = tmp;
    // self->m_size = size;
    // return self;

    if (self->m_size == size) return self;
    if ((size <= self->m_allocated) && (size * 0.7 >= self->m_allocated)) {
        goto afterRealloc;
        // self->m_size = size;
        // return self;
    }

    if (!size) {
        free(self->m_data);
        self->m_allocated = size;
        self->m_size      = size;
        self->m_data      = NULL;
        return self;
    }

    // // size_ut sz        = self->m_size;
    // if ((self->m_allocated < size) || ((size_ut)(self->m_allocated * 0.7 + 1) > size)) {
    //     self->m_allocated = (size * 1.3 + 1);
    //     int1_t_ptr *tmp   = (int1_t_ptr *)(realloc(self->m_data, (sizeof(int1_t_ptr) * self->m_allocated)));
    //     if (tmp != NULL)
    //         self->m_data = tmp;
    //     else
    //         fprintf(stderr, "ERROR: failed to realloc to %lld", size);
    //     // if (sz < size) { for (size_ut i = sz; i < size; ++i) {
    //     //     self->m_data[i]
    //     // } }
    //     if (self->m_size < size) { memset(self->m_data + self->m_size, 0, (size - self->m_size) *
    //     sizeof(int1_t_ptr)); } self->m_size = size; return self;
    // }
    // if (size > self->m_size) { memset(self->m_data + self->m_size, 0, (size - self->m_size) * sizeof(int1_t_ptr)); }
    // self->m_size = size;
    // return self;

    // size_ut sz        = self->m_size;

    // self->m_allocated = size;

    self->m_allocated = (size_ut)(size * 1.3 + 1);
    int1_t_ptr *tmp   = (int1_t_ptr *)(realloc(self->m_data, (sizeof(int1_t_ptr) * self->m_allocated)));
    if (tmp != NULL)
        self->m_data = tmp;
    else
        fprintf(stderr, "ERROR: failed to realloc to %lld", size);
afterRealloc:
    // if (sz < size) { for (size_ut i = sz; i < size; ++i) {
    //     self->m_data[i]
    // } }
    if (self->m_size < size) { memset(self->m_data + self->m_size, 0, (size - self->m_size) * sizeof(int1_t_ptr)); }
    self->m_size = size;
    return self;
}

cptrArray *remove_arr_cptr(cptrArray *self, size_ut start, size_ut end) {
    memcpy(self->m_data + start, self->m_data + end, (self->m_size - end) * sizeof(int1_t_ptr));
    resize_cptr(self, self->m_size - (end - start));
    return self;
}

cptrArray *insert_cptr(cptrArray *self, int1_t_ptr value, size_ut index) {
    resize_cptr(self, self->m_size + 1);
    memmove(self->m_data + index + 1, self->m_data + index, (self->m_size - index - 1) * sizeof(int1_t_ptr));
    self->m_data[index] = value;
    return self;
}


cptrArray *replace_cptr(cptrArray *self, int1_t_ptr value, size_ut start, size_ut end) {
    memcpy(self->m_data + start + 1, self->m_data + end, (self->m_size - end) * sizeof(int1_t_ptr));
    resize_cptr(self, self->m_size - (end - start) + 1);
    self->m_data[start] = value;
    return self;
}

cptrArray *pop_front_cptr(cptrArray *self, size_ut indexes) {
    memcpy(self->m_data, self->m_data + indexes, self->m_size - indexes);
    resize_cptr(self, self->m_size - indexes);
    return self;
}

cptrArray *push_front_cptr(cptrArray *self, int1_t_ptr val) {
    resize_cptr(self, self->m_size + 1);
    memmove(self->m_data + 1, self->m_data, self->m_size - 1);
    *self->m_data = val;
    return self;
}


size_ut find_cptr(cptrArray *self, int1_t_ptr target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort_cptr(self); }
    return _find_cptr(self, target, 0, self->m_size - 1);
}
size_ut findGreater_cptr(cptrArray *self, int1_t_ptr target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort_cptr(self); }
    return _findg_cptr(self, target, 0, self->m_size - 1);
}
size_ut findGreaterEq_cptr(cptrArray *self, int1_t_ptr target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort_cptr(self); }
    return _findge_cptr(self, target, 0, self->m_size - 1);
}
size_ut findLesser_cptr(cptrArray *self, int1_t_ptr target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort_cptr(self); }
    return _findl_cptr(self, target, 0, self->m_size - 1);
}
size_ut findLesserEq_cptr(cptrArray *self, int1_t_ptr target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort_cptr(self); }
    return _findle_cptr(self, target, 0, self->m_size - 1);
}


cptrArray *clear_cptr(cptrArray *self) {
    resize_cptr(self, 0);
    return self;
}
size_ut _find_cptr(cptrArray *self, int1_t_ptr target, size_ut left, size_ut right) {
    if (right < left) return self->m_size;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target)
        return self->_middle;
    else if (self->m_data[self->_middle] > target)
        return _find_cptr(self, target, left, self->_middle - 1);
    else
        return _find_cptr(self, target, self->_middle + 1, right);
}
size_ut _findg_cptr(cptrArray *self, int1_t_ptr target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target)
        return _findg_cptr(self, target, self->_middle + 1, right);
    else if (self->m_data[self->_middle] > target) {
        if (self->_middle == 0) { return self->_middle; }
        if (!(self->m_data[self->_middle - 1] > target)) return self->_middle;
        return _findg_cptr(self, target, left, self->_middle - 1);
    }
    else
        return _findg_cptr(self, target, self->_middle + 1, right);
}
size_ut _findl_cptr(cptrArray *self, int1_t_ptr target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target)
        return _findl_cptr(self, target, self->_middle + 1, right);
    else if (self->m_data[self->_middle] > target) {
        return _findl_cptr(self, target, left, self->_middle - 1);
    }
    else {
        if (self->_middle == self->m_size - 1) { return self->_middle; }
        if (!(self->m_data[self->_middle + 1] < target)) return self->_middle;
        return _findl_cptr(self, target, self->_middle + 1, right);
    }
}
size_ut _findge_cptr(cptrArray *self, int1_t_ptr target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target) {
        if (self->_middle == self->m_size - 1) { return self->_middle; }
        return _findge_cptr(self, target, self->_middle + 1, right);
    }
    else if (self->m_data[self->_middle] > target) {
        if (self->_middle == 0) { return self->_middle; }
        if (!(self->m_data[self->_middle - 1] > target)) return self->_middle - 1;
        return _findge_cptr(self, target, left, self->_middle - 1);
    }
    else
        return _findge_cptr(self, target, self->_middle + 1, right);
}
size_ut _findle_cptr(cptrArray *self, int1_t_ptr target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target) {
        if (self->_middle == 0) { return self->_middle; }
        return _findle_cptr(self, target, self->_middle + 1, right);
    }
    else if (self->m_data[self->_middle] > target) {
        return _findle_cptr(self, target, left, self->_middle - 1);
    }
    else {
        if (self->_middle == self->m_size - 1) { return self->_middle; }
        if (!(self->m_data[self->_middle + 1] < target)) return self->_middle + 1;
        return _findle_cptr(self, target, self->_middle + 1, right);
    }
}
cptrArray *push_back_cptr(cptrArray *self, int1_t_ptr element) {
    resize_cptr(self, self->m_size + 1);
    self->m_data[self->m_size - 1] = element;
    self->m_is_sorted              = false;
    return self;
}
cptrArray *pop_back_cptr(cptrArray *self) {
    resize_cptr(self, self->m_size - 1);
    return self;
}

int cptrCmp(const void *a, const void *b) { return a < b; }

cptrArray *sort_cptr(cptrArray *self) {
    if (self->m_is_sorted) { return self; }
    // qsort(self->m_data, self->m_size, sizeof(int1_t_ptr), [](const void *a, const void *b) -> int {
    //     return *((int1_t_ptr *)(a)) > *((int1_t_ptr *)(b));
    // });
    qsort(self->m_data, self->m_size, sizeof(int1_t_ptr), cptrCmp);
    self->m_is_sorted = true;
    return self;
}

bool strEq_cptr(const cptrArray *self, const cptrArray *arr) {
    if (self->m_size != arr->m_size) return 0;
    return !(memcmp(self->m_data, arr->m_data, self->m_size));
}

bool strEqC_cptr(const cptrArray *self, const char *arr) {
    if (self->m_size != (size_ut)strlen(arr)) return 0;
    return !(memcmp(self->m_data, arr, self->m_size));
}

cptrArray *concat_cptr(const cptrArray *self, const cptrArray *array) {
    // cptrArray arr(self->m_size + array.self->m_size);
    cptrArray  arr_val;
    cptrArray *arr = &arr_val;
    init_cptr(arr, size_cptr(self) + size_cptr(array));

    // memcpy(arr.self->m_data, self->m_data, self->m_size * sizeof(int1_t_ptr));
    memcpy(arr->m_data, self->m_data, self->m_size * sizeof(int1_t_ptr));
    // memcpy(arr->m_data + self->m_size, array.self->m_data, array.self->m_size * sizeof(int1_t_ptr));
    memcpy(arr->m_data + size_cptr(self), array->m_data, size_cptr(array) * sizeof(int1_t_ptr));
    // self->m_is_sorted = false;
    return arr;
}

cptrArray *concatEq_cptr(cptrArray *self, const cptrArray *array) {
    // cptrArray arr(self->m_size + array.self->m_size);
    // cptrArray  arr_val;
    // cptrArray *arr = &arr_val;
    // init(arr, size(self) + size(array));
    // printf("resized from %lld to %lld\n", size(self), size(self) + size(array));
    // fflush(stdout);
    // size_ut sz = size(self);
    resize_cptr(self, (size_ut)(size_cptr(self) + size_cptr(array)));
    // memcpy(arr.self->m_data, self->m_data, self->m_size * sizeof(int1_t_ptr));
    // memcpy(arr->m_data, self->m_data, self->m_size * sizeof(int1_t_ptr));
    // memcpy(arr->m_data + self->m_size, array.self->m_data, array.self->m_size * sizeof(int1_t_ptr));

    // TODO: Note: Not sure to use memcpy or memmove here
    memcpy(self->m_data + size_cptr(self) - size_cptr(array), array->m_data, size_cptr(array) * sizeof(int1_t_ptr));
    // self->m_is_sorted = false;
    return self;
}

cptrArray *strAssign_cptr(cptrArray *self, const cptrArray *arr) {
    resize_cptr(self, size_cptr(arr));
    memcpy(self->m_data, arr->m_data, size_cptr(self));
    return self;
}

cptrArray *strAssignC_cptr(cptrArray *self, const char *arr) {
    resize_cptr(self, strlen(arr));
    memcpy(self->m_data, arr, size_cptr(self));
    return self;
}

cptrArray *fprint_cptr(cptrArray *self, FILE *f) {
    fwrite(self->m_data, sizeof(int1_t_ptr), size_cptr(self), f);
    // for (size_ut i = 0; i < size(self); ++i) { fputc(self->m_data[i], f); }
    return self;
}

cptrArray *readLine_cptr(cptrArray *self, FILE *f) {
    int input;
    for (size_t i = 1;; ++i) {
        input = fgetc(f);
        if (i == 1) {
            switch (input) {
            case '\n':
            case '\t':
            case ' ': continue;
            default: break;
            }
        }
        switch (input) {
        case '\n':
        case EOF: return self;
        default:
            if ((size_t)(self->m_size) <= i) { resize_cptr(self, i * 2); }
        }
    }
}


// const char *c_str(cptrArray *self) { static bool first = true;
// if(first) {

// }}

void init_cptr(cptrArray *self, size_ut size) {
    // cptrArray(size_ut size) :
    // self->m_size      = size;
    self->m_size = 0;
    // self->m_allocated = (size_ut)(size * 1.3 + 1);
    self->m_allocated = 0;
    // self->m_data      = (int1_t_ptr *)(malloc(sizeof(int1_t_ptr) * self->m_allocated));
    self->m_data      = (int1_t_ptr *)NULL;
    self->m_is_sorted = false;
    self->_middle     = 0;
    resize_cptr(self, size);
    // memset(self->m_data, 0, sizeof(int1_t_ptr) * self->m_size);
}

void dest_cptr(cptrArray *self) { free(self->m_data); }

// size_ut round_near_cptr(double n) { return (size_ut)(n + 0.5); }