#include "utils.h"

// #define intArray struct intArray
typedef struct intArray intArray;

size_t    size(const intArray *self) { return self->m_size; }
intArray *resize(intArray *self, size_ut size) {
    // // printf("Realloc-ing from %llu ", sizeof(int1_t) * self->m_allocated);
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
    // // printf("to %llu\n", sizeof(int1_t) * self->m_allocated);
    // // fflush(stdout);
    // int1_t *tmp = (int1_t *)(realloc(self->m_data, (sizeof(int1_t) * self->m_allocated)));
    // if (tmp != NULL)
    //     self->m_data = tmp;
    // else {
    //     fprintf(stderr, "Out of memory.\n");
    //     return self;
    // }
    // if (expanded) {
    //     // memset(self->m_data + self->m_size, 0, (size - self->m_size) * sizeof(int1_t));

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
    //     int1_t *tmp       = (int1_t *)(realloc(self->m_data, (sizeof(int1_t) * self->m_allocated)));
    //     if (tmp != NULL)
    //         self->m_data = tmp;
    //     else
    //         fprintf(stderr, "ERROR: failed to realloc to %lld", size);
    //     // if (sz < size) { for (size_ut i = sz; i < size; ++i) {
    //     //     self->m_data[i]
    //     // } }
    //     if (self->m_size < size) { memset(self->m_data + self->m_size, 0, size - self->m_size); }
    //     self->m_size = size;
    //     return self;
    // }
    // if (size > self->m_size) { memset(self->m_data + self->m_size, 0, size - self->m_size); }
    // self->m_size = size;
    // return self;

    // size_ut sz        = self->m_size;

    self->m_allocated = (size_ut)(size * 1.3 + 1);
    int1_t *tmp       = (int1_t *)(realloc(self->m_data, (sizeof(int1_t) * self->m_allocated)));
    if (tmp != NULL)
        self->m_data = tmp;
    else
        fprintf(stderr, "ERROR: failed to realloc to %lld", size);
// if (sz < size) { for (size_ut i = sz; i < size; ++i) {
//     self->m_data[i]
// } }
afterRealloc:
    if (self->m_size < size) { memset(self->m_data + self->m_size, 0, (size - self->m_size) * sizeof(int1_t)); }
    self->m_size = size;
    return self;
}

// intArray *reserve(intArray *self, size_ut size) {
//     size_ut old_size = self->m_size;
//     resize(self, size);
//     self->m_size = old_size;
//     return self;
// }

intArray *remove_arr(intArray *self, size_ut start, size_ut end) {
    memcpy(self->m_data + start, self->m_data + end, (self->m_size - end) * sizeof(int1_t));
    resize(self, self->m_size - (end - start));
    return self;
}

intArray *insert(intArray *self, int1_t value, size_ut index) {
    resize(self, self->m_size + 1);
    memmove(self->m_data + index + 1, self->m_data + index, (self->m_size - index - 1) * sizeof(int1_t));
    self->m_data[index] = value;
    return self;
}


intArray *replace(intArray *self, int1_t value, size_ut start, size_ut end) {
    memcpy(self->m_data + start + 1, self->m_data + end, (self->m_size - end) * sizeof(int1_t));
    resize(self, self->m_size - (end - start) + 1);
    self->m_data[start] = value;
    return self;
}

intArray *pop_front(intArray *self, size_ut indexes) {
    memcpy(self->m_data, self->m_data + indexes, self->m_size - indexes);
    resize(self, self->m_size - indexes);
    return self;
}

intArray *push_front(intArray *self, int1_t val) {
    resize(self, self->m_size + 1);
    memmove(self->m_data + 1, self->m_data, self->m_size - 1);
    *self->m_data = val;
    return self;
}


size_ut find(intArray *self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _find(self, target, 0, self->m_size - 1);
}
size_ut findGreater(intArray *self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _findg(self, target, 0, self->m_size - 1);
}
size_ut findGreaterEq(intArray *self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _findge(self, target, 0, self->m_size - 1);
}
size_ut findLesser(intArray *self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _findl(self, target, 0, self->m_size - 1);
}
size_ut findLesserEq(intArray *self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _findle(self, target, 0, self->m_size - 1);
}


intArray *clear(intArray *self) {
    resize(self, 0);
    return self;
}
size_ut _find(intArray *self, int1_t target, size_ut left, size_ut right) {
    if (right < left) return self->m_size;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target)
        return self->_middle;
    else if (self->m_data[self->_middle] > target)
        return _find(self, target, left, self->_middle - 1);
    else
        return _find(self, target, self->_middle + 1, right);
}
size_ut _findg(intArray *self, int1_t target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target)
        return _findg(self, target, self->_middle + 1, right);
    else if (self->m_data[self->_middle] > target) {
        if (self->_middle == 0) { return self->_middle; }
        if (!(self->m_data[self->_middle - 1] > target)) return self->_middle;
        return _findg(self, target, left, self->_middle - 1);
    }
    else
        return _findg(self, target, self->_middle + 1, right);
}
size_ut _findl(intArray *self, int1_t target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target)
        return _findl(self, target, self->_middle + 1, right);
    else if (self->m_data[self->_middle] > target) {
        return _findl(self, target, left, self->_middle - 1);
    }
    else {
        if (self->_middle == self->m_size - 1) { return self->_middle; }
        if (!(self->m_data[self->_middle + 1] < target)) return self->_middle;
        return _findl(self, target, self->_middle + 1, right);
    }
}
size_ut _findge(intArray *self, int1_t target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target) {
        if (self->_middle == self->m_size - 1) { return self->_middle; }
        return _findge(self, target, self->_middle + 1, right);
    }
    else if (self->m_data[self->_middle] > target) {
        if (self->_middle == 0) { return self->_middle; }
        if (!(self->m_data[self->_middle - 1] > target)) return self->_middle - 1;
        return _findge(self, target, left, self->_middle - 1);
    }
    else
        return _findge(self, target, self->_middle + 1, right);
}
size_ut _findle(intArray *self, int1_t target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target) {
        if (self->_middle == 0) { return self->_middle; }
        return _findle(self, target, self->_middle + 1, right);
    }
    else if (self->m_data[self->_middle] > target) {
        return _findle(self, target, left, self->_middle - 1);
    }
    else {
        if (self->_middle == self->m_size - 1) { return self->_middle; }
        if (!(self->m_data[self->_middle + 1] < target)) return self->_middle + 1;
        return _findle(self, target, self->_middle + 1, right);
    }
}
intArray *push_back(intArray *self, int1_t element) {
    resize(self, self->m_size + 1);
    self->m_data[self->m_size - 1] = element;
    self->m_is_sorted              = false;
    return self;
}
intArray *pop_back(intArray *self) {
    resize(self, self->m_size - 1);
    return self;
}

int intCmp(const void *a, const void *b) { return a < b; }

intArray *sort(intArray *self) {
    if (self->m_is_sorted) { return self; }
    // qsort(self->m_data, self->m_size, sizeof(int1_t), [](const void *a, const void *b) -> int {
    //     return *((int1_t *)(a)) > *((int1_t *)(b));
    // });
    qsort(self->m_data, self->m_size, sizeof(int1_t), intCmp);
    self->m_is_sorted = true;
    return self;
}

bool strEq(const intArray *self, const intArray *arr) {
    if (self->m_size != arr->m_size) return 0;
    return !(memcmp(self->m_data, arr->m_data, self->m_size));
}

bool strEqC(const intArray *self, const char *arr) {
    if (self->m_size != (size_ut)strlen(arr)) return 0;
    return !(memcmp(self->m_data, arr, self->m_size));
}

intArray *concat(const intArray *self, const intArray *array) {
    // intArray arr(self->m_size + array.self->m_size);
    intArray  arr_val;
    intArray *arr = &arr_val;
    init(arr, size(self) + size(array));

    // memcpy(arr.self->m_data, self->m_data, self->m_size * sizeof(int1_t));
    memcpy(arr->m_data, self->m_data, self->m_size * sizeof(int1_t));
    // memcpy(arr->m_data + self->m_size, array.self->m_data, array.self->m_size * sizeof(int1_t));
    memcpy(arr->m_data + size(self), array->m_data, size(array) * sizeof(int1_t));
    // self->m_is_sorted = false;
    return arr;
}

intArray *concatEq(intArray *self, const intArray *array) {
    // intArray arr(self->m_size + array.self->m_size);
    // intArray  arr_val;
    // intArray *arr = &arr_val;
    // init(arr, size(self) + size(array));
    // printf("resized from %lld to %lld\n", size(self), size(self) + size(array));
    // fflush(stdout);
    // size_ut sz = size(self);
    resize(self, (size_ut)(size(self) + size(array)));
    // memcpy(arr.self->m_data, self->m_data, self->m_size * sizeof(int1_t));
    // memcpy(arr->m_data, self->m_data, self->m_size * sizeof(int1_t));
    // memcpy(arr->m_data + self->m_size, array.self->m_data, array.self->m_size * sizeof(int1_t));

    // TODO: Note: Not sure to use memcpy or memmove here
    memcpy(self->m_data + size(self) - size(array), array->m_data, size(array) * sizeof(int1_t));
    // self->m_is_sorted = false;
    return self;
}

intArray *strAssign(intArray *self, const intArray *arr) {
    resize(self, size(arr));
    memcpy(self->m_data, arr->m_data, size(self));
    return self;
}

intArray *strAssignC(intArray *self, const char *arr) {
    resize(self, strlen(arr));
    memcpy(self->m_data, arr, size(self));
    return self;
}

intArray *fprint(intArray *self, FILE *f) {
    fwrite(self->m_data, sizeof(int1_t), size(self), f);
    // for (size_ut i = 0; i < size(self); ++i) { fputc(self->m_data[i], f); }
    return self;
}

int1_t readLine(intArray *self, FILE *f) {
    int input;
    clear(self);
    for (size_t i = 1;; ++i) {
    restart:
        input = fgetc(f);
        if (i == 1UL) {
            switch (input) {
            case '\t':
            case ' ': goto restart;
            case '\n': return 0;
            case EOF: return 1;
            default: break;
            }
        }
        switch (input) {
        case '\n':
        case '\t':
        case ' ': return 0;
        case EOF: return 1;
        default:
            // if ((size_t)(self->m_size) <= i) { resize(self, i * 2); }
            // self->m_data[i - 1] = input;
            push_back(self, input);
        }
    }
}


char *c_str(intArray *self) {
// static bool first = true;
// if (first) {}
#define ptr (&(self->m_ptrs))
    resize_cptr(&(self->m_ptrs), size_cptr(&(self->m_ptrs)) + 1);
#define data_last (self->m_ptrs.m_data[size_cptr(&(self->m_ptrs)) - 1])
    self->m_ptrs.m_data[size_cptr(&(self->m_ptrs)) - 1] = (char *)malloc(size(self) + 1);
    memcpy(self->m_ptrs.m_data[size_cptr(&(self->m_ptrs)) - 1], self->m_data, size(self));
    self->m_ptrs.m_data[size_cptr(&(self->m_ptrs)) - 1][size(self)] = '\0';
    return self->m_ptrs.m_data[size_cptr(&(self->m_ptrs)) - 1];
#undef data_last
#undef ptr
}

void init(intArray *self, size_ut size) {
    // intArray(size_ut size) :
    // self->m_size      = size;
    self->m_size = 0;
    // self->m_allocated = (size_ut)(size * 1.3 + 1);
    self->m_allocated = 0;
    // self->m_data      = (int1_t *)(malloc(sizeof(int1_t) * self->m_allocated));
    self->m_data      = (int1_t *)NULL;
    self->m_is_sorted = false;
    self->_middle     = 0;
    resize(self, size);
    init_cptr(&(self->m_ptrs), 0);
    // memset(self->m_data, 0, sizeof(int1_t) * self->m_size);
}

void dest(intArray *self) {
    for (size_t i = 0; i < size_cptr(&(self->m_ptrs)); ++i) { free(self->m_ptrs.m_data[i]); }
    dest_cptr(&(self->m_ptrs));
    free(self->m_data);
}

size_ut round_near(double n) { return (size_ut)(n + 0.5); }
size_ut round_down(double n) { return (size_ut)(n); }


const char *help_message = "Commands:\n"
                           "(h)elp\t\t\t\t\t\t\t\t\tDisplay help message\n"
                           "(o)pen <path>\t\t\t\t\t\t\tOpen a file with name <path>\n"
                           "(f)ill <x0> <y0> <x1> <y1> <colour>     Fill the pixels within the area specified \n"
                           "\t\t\t\t\t\t\t\t\t\twith <colour> (specified in hexadecimal)\n"
                           "(r)esize <width> <height>\t\t\t\tResize the image to the specified <width> and <height>\n"
                           "(s)cale <factor>\t\t\t\t\t\tResize the image by <factor>\n"
                           "(c)rop <x0> <y0> <x1> <y1>\t\t\t\tCrop the image to the area specified\n"
                           "(e)xit\t\t\t\t\t\t\t\t\tExit the program\n"
                           "(q)uit\t\t\t\t\t\t\t\t\tAlias for (e)xit\n";