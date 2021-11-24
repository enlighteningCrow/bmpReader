#include "utils_pix.h"
#include "pixel.h"
#include "utils.h"


typedef struct pixArray pixArray;
typedef struct Pixel    Pixel;

size_t   size_pixArr(pixArray *self) { return self->m_size; }
pixArray *resize_pixArr(pixArray *self, size_t size) {

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
    Pixel *tmp        = (Pixel *)(realloc(self->m_data, (sizeof(Pixel) * self->m_allocated)));
    if (tmp != NULL)
        self->m_data = tmp;
    else
        fprintf(stderr, "ERROR: failed to realloc to %lu", size);
afterRealloc:
    if (self->m_size < size) {

        for (size_t i = self->m_size; i < size; ++i) { init_pix(self->m_data + i, 0, self->m_bpp); }
    }
    else if (self->m_size > size) {
        for (size_t i = size; i < self->m_size; ++i) { dest_pix(self->m_data + i); }
    }
    self->m_size = size;
    return self;
}

pixArray *remove_pixArr(pixArray *self, size_t start, size_t end) {
    memcpy(self->m_data + start, self->m_data + end, (self->m_size - end) * sizeof(Pixel));
    resize_pixArr(self, self->m_size - (end - start));
    return self;
}

pixArray *insert_pixArr(pixArray *self, Pixel value, size_t index) {
    resize_pixArr(self, self->m_size + 1);
    memmove(self->m_data + index + 1, self->m_data + index, (self->m_size - index - 1) * sizeof(Pixel));
    self->m_data[index] = value;
    return self;
}


pixArray *replace_pixArr(pixArray *self, Pixel value, size_t start, size_t end) {
    memcpy(self->m_data + start + 1, self->m_data + end, (self->m_size - end) * sizeof(Pixel));
    resize_pixArr(self, self->m_size - (end - start) + 1);
    self->m_data[start] = value;
    return self;
}

pixArray *pop_front_pixArr(pixArray *self, size_t indexes) {
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


pixArray *clear_pixArr(pixArray *self) {
    resize_pixArr(self, 0);
    return self;
}

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


pixArray *sort_pixArr(pixArray *self) {
    if (self->m_is_sorted) { return self; }


    fprintf(stderr, "Warning: Attempting to sort pixels");

    self->m_is_sorted = true;
    return self;
}

void init_pixArr(pixArray *self, size_t size, short int bpp) {


    self->m_size = 0;

    self->m_allocated = 0;

    self->m_data      = (Pixel *)NULL;
    self->m_is_sorted = false;
    self->_middle     = 0;
    self->m_bpp       = bpp;
    resize_pixArr(self, size);
}

void dest_pixArr(pixArray *self) {
    for (size_t i = 0; i < size_pixArr(self); ++i) { dest_pix(self->m_data + i); }
    free(self->m_data);
}

void swap_pixArr(pixArray *self, pixArray *other) {
#define swap(x, type)                                                                                                  \
    {                                                                                                                  \
        type tmp = self->x;                                                                                            \
        self->x  = other->x;                                                                                           \
        other->x = tmp;                                                                                                \
    }
    swap(m_allocated, size_t);
    swap(m_data, Pixel *);
    swap(m_is_sorted, bool);
    swap(m_size, size_t);
    swap(_middle, size_t);
    return;
}