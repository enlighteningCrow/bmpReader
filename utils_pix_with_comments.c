#include "utils_pix.h"
#include "pixel.h"
#include "utils.h"

// #define pixArray struct pixArray
// #define Pixel struct Pixel
typedef struct pixArray pixArray;
typedef struct Pixel    Pixel;

size_ut   size_pixarr(pixArray *self) { return self->m_size; }
pixArray *resize_pixArr(pixArray *self, size_ut size) {
    /*
    if (self->m_size == size) return self;
    bool expanded = (self->m_allocated < size);
    if ((self->m_allocated < size) || ((size_ut)(self->m_allocated * 0.7 + 1) > size)) {
        self->m_allocated = (size_ut)((size * 1.3) + 1);
    }
    else {
        self->m_size = size;
        return self;
    }
    Pixel *tmp = (Pixel *)(realloc(self->m_data, (sizeof(Pixel) * self->m_allocated)));
    if (tmp != NULL) self->m_data = tmp;
    if (expanded) {
        memset(self->m_data + self->m_size, 0, (size - self->m_size) * sizeof(Pixel));
        if (tmp == NULL) {
            fprintf(stderr, "Out of memory.\n");
            return self;
        }

        self->m_is_sorted = false;
    }
    self->m_data = tmp;
    self->m_size = size;
    return self; */
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

    // self->m_allocated = size;

    self->m_allocated = (size_ut)(size * 1.3 + 1);
    Pixel *tmp        = (Pixel *)(realloc(self->m_data, (sizeof(Pixel) * self->m_allocated)));
    if (tmp != NULL)
        self->m_data = tmp;
    else
        fprintf(stderr, "ERROR: failed to realloc to %lld", size);
afterRealloc:
    if (self->m_size < size) {

        for (size_ut i = self->m_size; i < size; ++i) {
            init_pix(self->m_data + i, 0, self->m_bpp);
            // init(&self->m_data[i].m_array, 0);
        }
    }
    else if (self->m_size > size) {
        for (size_ut i = size; i < self->m_size; ++i) {
            dest_pix(self->m_data + i);
            // free(&self->m_data[i].m_array);
        }
    }
    self->m_size = size;
    return self;
}

pixArray *remove_pixArr(pixArray *self, size_ut start, size_ut end) {
    memcpy(self->m_data + start, self->m_data + end, (self->m_size - end) * sizeof(Pixel));
    resize_pixArr(self, self->m_size - (end - start));
    return self;
}

pixArray *insert_pixArr(pixArray *self, Pixel value, size_ut index) {
    resize_pixArr(self, self->m_size + 1);
    memmove(self->m_data + index + 1, self->m_data + index, (self->m_size - index - 1) * sizeof(Pixel));
    self->m_data[index] = value;
    return self;
}


pixArray *replace_pixArr(pixArray *self, Pixel value, size_ut start, size_ut end) {
    memcpy(self->m_data + start + 1, self->m_data + end, (self->m_size - end) * sizeof(Pixel));
    resize_pixArr(self, self->m_size - (end - start) + 1);
    self->m_data[start] = value;
    return self;
}

pixArray *pop_front_pixArr(pixArray *self, size_ut indexes) {
    memcpy(self->m_data, self->m_data + indexes, self->m_size - indexes);
    resize_pixArr(self, self->m_size - indexes);
    return self;
}

pixArray *push_front_pixArr(pixArray *self, Pixel val) {
    resize_pixArr(self, self->m_size + 1);
    memmove(self->m_data + 1, self->m_data, self->m_size - 1);
    *self->m_data = val;
    return self;
}

/*
size_ut find_pix(pixArray *self, Pixel target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort_pix(self); }
    return _find_pix(self, target, 0, self->m_size - 1);
}
size_ut findGreater_pix(pixArray *self, Pixel target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort_pix(self); }
    return _findg_pix(self, target, 0, self->m_size - 1);
}
size_ut findGreaterEq_pix(pixArray *self, Pixel target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort_pix(self); }
    return _findge_pix(self, target, 0, self->m_size - 1);
}
size_ut findLesser_pix(pixArray *self, Pixel target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort_pix(self); }
    return _findl_pix(self, target, 0, self->m_size - 1);
}
size_ut findLesserEq_pix(pixArray *self, Pixel target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort_pix(self); }
    return _findle_pix(self, target, 0, self->m_size - 1);
} */


pixArray *clear_pixArr(pixArray *self) {
    resize_pixArr(self, 0);
    return self;
}
/*
size_ut   _find_pix(pixArray *self, Pixel target, size_ut left, size_ut right) {
    if (right < left) return self->m_size;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target)
        return self->_middle;
    else if (self->m_data[self->_middle] > target)
        return _find_pix(self, target, left, self->_middle - 1);
    else
        return _find_pix(self, target, self->_middle + 1, right);
}
size_ut _findg_pix(pixArray *self, Pixel target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target)
        return _find_pix(self, target, self->_middle + 1, right);
    else if (self->m_data[self->_middle] > target) {
        if (self->_middle == 0) { return self->_middle; }
        if (!(self->m_data[self->_middle - 1] > target)) return self->_middle;
        return _find_pix(self, target, left, self->_middle - 1);
    }
    else
        return _find_pix(self, target, self->_middle + 1, right);
}
size_ut _findl_pix(pixArray *self, Pixel target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target)
        return _find_pix(self, target, self->_middle + 1, right);
    else if (self->m_data[self->_middle] > target) {
        return _find_pix(self, target, left, self->_middle - 1);
    }
    else {
        if (self->_middle == self->m_size - 1) { return self->_middle; }
        if (!(self->m_data[self->_middle + 1] < target)) return self->_middle;
        return _find_pix(self, target, self->_middle + 1, right);
    }
}
size_ut _findge_pix(pixArray *self, Pixel target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target) {
        if (self->_middle == self->m_size - 1) { return self->_middle; }
        return _find_pix(self, target, self->_middle + 1, right);
    }
    else if (self->m_data[self->_middle] > target) {
        if (self->_middle == 0) { return self->_middle; }
        if (!(self->m_data[self->_middle - 1] > target)) return self->_middle - 1;
        return _find_pix(self, target, left, self->_middle - 1);
    }
    else
        return _find_pix(self, target, self->_middle + 1, right);
}
size_ut _findle_pix(pixArray *self, Pixel target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target) {
        if (self->_middle == 0) { return self->_middle; }
        return _find_pix(self, target, self->_middle + 1, right);
    }
    else if (self->m_data[self->_middle] > target) {
        return _find_pix(self, target, left, self->_middle - 1);
    }
    else {
        if (self->_middle == self->m_size - 1) { return self->_middle; }
        if (!(self->m_data[self->_middle + 1] < target)) return self->_middle + 1;
        return _find_pix(self, target, self->_middle + 1, right);
    }
} */
pixArray *push_back_pixArr(pixArray *self, Pixel element) {
    resize_pixArr(self, self->m_size + 1);
    self->m_data[self->m_size - 1] = element;
    self->m_is_sorted              = false;
    return self;
}
pixArray *pop_back_pixArr(pixArray *self) {
    resize_pixArr(self, self->m_size - 1);
    return self;
}

// int pixCmp(const void *a, const void *b) { return 0; }


pixArray *sort_pixArr(pixArray *self) {
    if (self->m_is_sorted) { return self; }
    // qsort(self->m_data, self->m_size, sizeof(Pixel), [](const void *a, const void *b) -> int {
    //     return *((Pixel *)(a)) > *((Pixel *)(b));
    // });
    fprintf(stderr, "Warning: Attempting to sort pixels");
    // qsort(self->m_data, self->m_size, sizeof(Pixel), pixCmp);
    self->m_is_sorted = true;
    return self;
}

void init_pixArr(pixArray *self, size_ut size, short int bpp) {
    // intArray(size_ut size) :
    // self->m_size      = size;
    self->m_size = 0;
    // self->m_allocated = (size_ut)(size * 1.3 + 1);
    self->m_allocated = 0;
    // self->m_data      = (Pixel *)(malloc(sizeof(Pixel) * self->m_allocated));
    self->m_data      = (Pixel *)NULL;
    self->m_is_sorted = false;
    self->_middle     = 0;
    self->m_bpp       = bpp;
    resize_pixArr(self, size);
    // memset(self->m_data, 0, sizeof(Pixel) * self->m_size);
}

void dest_pixArr(pixArray *self) {
    for (size_ut i = 0; i < size_pixarr(self); ++i) {
        dest_pix(self->m_data + i); /* dest(&self->m_data[i].m_array); */
    }
    free(self->m_data);
}

void swap_pixArr(pixArray *self, pixArray *other) {
#define swap(x, type)                                                                                                  \
    {                                                                                                                  \
        type tmp = self->x;                                                                                            \
        self->x  = other->x;                                                                                           \
        other->x = tmp;                                                                                                \
    }
    swap(m_allocated, size_ut);
    swap(m_data, Pixel *);
    swap(m_is_sorted, bool);
    swap(m_size, size_ut);
    swap(_middle, size_ut);
    return;
}