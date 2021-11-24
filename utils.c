#include "utils.h"


typedef struct intArray intArray;

size_t    size(const intArray *self) { return self->m_size; }
intArray *resize(intArray *self, size_t size) {


    if (self->m_size == size) return self;
    if ((size <= self->m_allocated) && (size * 0.7 >= self->m_allocated)) { goto afterRealloc; }

    if (!size) {
        free(self->m_data);
        self->m_allocated = size;
        self->m_size      = size;
        self->m_data      = NULL;
        return self;
    }


    self->m_allocated = (size_t)(size * 1.3 + 1);
    {
        int1_t *tmp = (int1_t *)(realloc(self->m_data, (sizeof(int1_t) * self->m_allocated)));
        if (tmp != NULL)
            self->m_data = tmp;
        else
            fprintf(stderr, "ERROR: failed to realloc to %lu", size);
    }

afterRealloc:
    if (self->m_size < size) { memset(self->m_data + self->m_size, 0, (size - self->m_size) * sizeof(int1_t)); }
    self->m_size = size;
    return self;
}


intArray *remove_arr(intArray *self, size_t start, size_t end) {
    memcpy(self->m_data + start, self->m_data + end, (self->m_size - end) * sizeof(int1_t));
    resize(self, self->m_size - (end - start));
    return self;
}

intArray *insert(intArray *self, int1_t value, size_t index) {
    resize(self, self->m_size + 1);
    memmove(self->m_data + index + 1, self->m_data + index, (self->m_size - index - 1) * sizeof(int1_t));
    self->m_data[index] = value;
    return self;
}


intArray *replace(intArray *self, int1_t value, size_t start, size_t end) {
    memcpy(self->m_data + start + 1, self->m_data + end, (self->m_size - end) * sizeof(int1_t));
    resize(self, self->m_size - (end - start) + 1);
    self->m_data[start] = value;
    return self;
}

intArray *pop_front(intArray *self, size_t indexes) {
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


size_t find(intArray *self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _find(self, target, 0, self->m_size - 1);
}
size_t findGreater(intArray *self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _findg(self, target, 0, self->m_size - 1);
}
size_t findGreaterEq(intArray *self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _findge(self, target, 0, self->m_size - 1);
}
size_t findLesser(intArray *self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _findl(self, target, 0, self->m_size - 1);
}
size_t findLesserEq(intArray *self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _findle(self, target, 0, self->m_size - 1);
}


intArray *clear(intArray *self) {
    resize(self, 0);
    return self;
}
size_t _find(intArray *self, int1_t target, size_t left, size_t right) {
    if (right < left) return self->m_size;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target)
        return self->_middle;
    else if (self->m_data[self->_middle] > target)
        return _find(self, target, left, self->_middle - 1);
    else
        return _find(self, target, self->_middle + 1, right);
}
size_t _findg(intArray *self, int1_t target, size_t left, size_t right) {
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
size_t _findl(intArray *self, int1_t target, size_t left, size_t right) {
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
size_t _findge(intArray *self, int1_t target, size_t left, size_t right) {
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
size_t _findle(intArray *self, int1_t target, size_t left, size_t right) {
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


    qsort(self->m_data, self->m_size, sizeof(int1_t), intCmp);
    self->m_is_sorted = true;
    return self;
}

bool strEq(const intArray *self, const intArray *arr) {
    if (self->m_size != arr->m_size) return 0;
    return !(memcmp(self->m_data, arr->m_data, self->m_size));
}

bool strEqC(const intArray *self, const char *arr) {
    if (self->m_size != (size_t)strlen(arr)) return 0;
    return !(memcmp(self->m_data, arr, self->m_size));
}

intArray *concat(const intArray *self, const intArray *array) {

    intArray  arr_val;
    intArray *arr = &arr_val;
    init(arr, size(self) + size(array));


    memcpy(arr->m_data, self->m_data, self->m_size * sizeof(int1_t));

    memcpy(arr->m_data + size(self), array->m_data, size(array) * sizeof(int1_t));

    return arr;
}

intArray *concatEq(intArray *self, const intArray *array) {


    resize(self, (size_t)(size(self) + size(array)));


    memcpy(self->m_data + size(self) - size(array), array->m_data, size(array) * sizeof(int1_t));

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

    return self;
}

int1_t readLine(intArray *self, FILE *f) {
    int input;
    // clear(self);
    for (size_t i = 0;; ++i) {
        bool strip_end = false;
    restart:
        input = fgetc(f);
        if (i == 0UL) {
            switch (input) {
            case '\t':
            case ' ': goto restart;
            case '\n': return 2;
            case EOF: return 1;
            default: break;
            }
        }
        switch (input) {
        case '\t':
        case ' ':
            strip_end = true;
            goto restart;
            // for (size_t i = 1; (input = fgetc(stdin)) != '\n'; ++i) {
            //     if (input >= 'a' && input <= 'z') ||
            // }
            return 0;
        case '\n': return 2;
        case EOF: return 1;
        default:
            if (strip_end) {
                ungetc(input, stdin);
                return 0;
            }
            push_back(self, input);
        }
    }
}

int1_t readLineThroughSpaces(intArray *self, FILE *f) {
    int    input;
    int1_t return_val;
    // clear(self);
    for (size_t i = 0;; ++i) {
    restart:
        input = fgetc(f);
        if (i == 0UL) {
            switch (input) {
            case '\t':
            case ' ': goto restart;
            case '\n': return 2;
            case EOF: return 1;
            default: break;
            }
        }
        switch (input) {
        case '\n': return_val = 2; goto after_loop;
        case EOF: return_val = 1; goto after_loop;
        default: push_back(self, input);
        }
    }
after_loop:
    while (self->m_data[size(self) - 1] == ' ' || self->m_data[size(self) - 1] == '\t') {
        pop_back(self);
        if (!size(self)) break;
    }
    return return_val;
}

// prompt_user(intArray* self, FILE* f, )

char *c_str(intArray *self) {
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

void free_c_str(intArray *self, char *str) {
    size_t index = find_cptr(&self->m_ptrs, str);
    // for (size_t i = 0; i < size_cptr(&(self->m_ptrs)); ++i) {
    //     if (self->m_ptrs.m_data[i] == str) {
    //         remove_arr_cptr(&(self->m_ptrs), i, i + 1);
    //         return;
    //     }
    // }
    if (index == size_cptr(&self->m_ptrs)) {
        fprintf(stderr, "No c_str with address %p is generated by this string. \n", str);
        return;
    }
    remove_arr_cptr(&self->m_ptrs, index, index + 1);
    return;
}

void init(intArray *self, size_t size) {


    self->m_size = 0;

    self->m_allocated = 0;

    self->m_data      = (int1_t *)NULL;
    self->m_is_sorted = false;
    self->_middle     = 0;
    resize(self, size);
    init_cptr(&(self->m_ptrs), 0);
}

void dest(intArray *self) {
    for (size_t i = 0; i < size_cptr(&(self->m_ptrs)); ++i) { free(self->m_ptrs.m_data[i]); }
    dest_cptr(&(self->m_ptrs));
    free(self->m_data);
}

size_t round_near(double n) { return (size_t)(n + 0.5); }
size_t round_down(double n) { return (size_t)(n); }


const char *help_message = "Commands:\n"
                           "(h)elp\t\t\t\t\t\t\tDisplay help message\n"
                           "(o)pen <path>\t\t\t\t\t\tOpen a file with name <path>\n"
                           "(f)ill [<x0> <y0> <x1> <y1> <colour>]\t\t\tFill the pixels within the area specified \n"
                           "\t\t\t\t\t\t\twith <colour>((A)RGB) (specified in hexadecimal)\n"
                           "\t\t\t\t\t\t\t(leave empty to enter prompt mode)\n"
                           "(r)esize <width> <height>\t\t\t\tResize the image to the specified <width> and <height>\n"
                           "(s)cale <factor>\t\t\t\t\tResize the image by <factor>\n"
                           "(c)rop [<x0> <y0> <x1> <y1>]\t\t\t\tCrop the image to the area specified\n"
                           "\t\t\t\t\t\t\t(leave empty to enter prompt mode)\n"
                           "(e)dit <id>\t\t\t\t\t\tChoose bmp file currently open to edit\n"
                           "(w)rite [<filename>]\t\t\t\t\tWrite the currently open bitmap file to <filename>\n"
                           "\t\t\t\t\t\t\t(Leave blank to update file)\n"
                           "(l)ist\t\t\t\t\t\t\tList all open bitmap files\n"
                           "(q)uit\t\t\t\t\t\t\tQuit the program\n";