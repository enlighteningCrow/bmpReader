#include "utils_bmp.h"
#include "bmp.h"
#include "utils.h"


typedef struct bmpArray bmpArray;
typedef struct Bmp      Bmp;

size_ut   size_bmpArr(bmpArray *self) { return self->m_size; }
bmpArray *resize_bmpArr(bmpArray *self, size_ut size) {

    if (self->m_size == size) return self;
    if ((size <= self->m_allocated) && (size * 0.7 >= self->m_allocated)) { goto afterRealloc; }

    if (!size) {
        free(self->m_data);
        self->m_allocated = size;
        self->m_size      = size;
        self->m_data      = NULL;
        return self;
    }


    self->m_allocated = (size_ut)(size * 1.3 + 1);
    {
        Bmp *tmp = (Bmp *)(realloc(self->m_data, (sizeof(Bmp) * self->m_allocated)));
        if (tmp != NULL)
            self->m_data = tmp;
        else
            fprintf(stderr, "ERROR: failed to realloc to %lld", size);
    }
afterRealloc:
    if (self->m_size < size) {

        for (size_ut i = self->m_size; i < size; ++i) { init_bmp(self->m_data + i); }
    }
    else if (self->m_size > size) {
        for (size_ut i = size; i < self->m_size; ++i) { dest_bmp(self->m_data + i); }
    }
    self->m_size = size;
    return self;
}

bmpArray *remove_bmpArr(bmpArray *self, size_ut start, size_ut end) {
    memcpy(self->m_data + start, self->m_data + end, (self->m_size - end) * sizeof(Bmp));
    resize_bmpArr(self, self->m_size - (end - start));
    return self;
}

bmpArray *insert_bmpArr(bmpArray *self, Bmp value, size_ut index) {
    resize_bmpArr(self, self->m_size + 1);
    memmove(self->m_data + index + 1, self->m_data + index, (self->m_size - index - 1) * sizeof(Bmp));
    self->m_data[index] = value;
    return self;
}


bmpArray *replace_bmpArr(bmpArray *self, Bmp value, size_ut start, size_ut end) {
    memcpy(self->m_data + start + 1, self->m_data + end, (self->m_size - end) * sizeof(Bmp));
    resize_bmpArr(self, self->m_size - (end - start) + 1);
    self->m_data[start] = value;
    return self;
}

bmpArray *pop_front_bmpArr(bmpArray *self, size_ut indexes) {
    memcpy(self->m_data, self->m_data + indexes, self->m_size - indexes);
    resize_bmpArr(self, self->m_size - indexes);
    return self;
}

bmpArray *push_front_bmpArr(bmpArray *self, Bmp val) {
    resize_bmpArr(self, self->m_size + 1);
    memmove(self->m_data + 1, self->m_data, self->m_size - 1);
    *self->m_data = val;
    return self;
}


bmpArray *clear_bmpArr(bmpArray *self) {
    resize_bmpArr(self, 0);
    return self;
}

bmpArray *push_back_bmpArr(bmpArray *self, Bmp element) {
    resize_bmpArr(self, self->m_size + 1);
    self->m_data[self->m_size - 1] = element;
    self->m_is_sorted              = false;
    return self;
}
bmpArray *pop_back_bmpArr(bmpArray *self) {
    resize_bmpArr(self, self->m_size - 1);
    return self;
}


bmpArray *sort_bmpArr(bmpArray *self) {
    if (self->m_is_sorted) { return self; }


    fprintf(stderr, "Warning: Attempting to sort pixels");

    self->m_is_sorted = true;
    return self;
}

void init_bmpArr(bmpArray *self, size_ut size) {


    self->m_size = 0;

    self->m_allocated = 0;

    self->m_data      = (Bmp *)NULL;
    self->m_is_sorted = false;
    self->_middle     = 0;
    resize_bmpArr(self, size);
}

void dest_bmpArr(bmpArray *self) {
    for (size_ut i = 0; i < size_bmpArr(self); ++i) { dest_bmp(self->m_data + i); }
    free(self->m_data);
}

void swap_bmpArr(bmpArray *self, bmpArray *other) {
#define swap(x, type)                                                                                                  \
    {                                                                                                                  \
        type tmp = self->x;                                                                                            \
        self->x  = other->x;                                                                                           \
        other->x = tmp;                                                                                                \
    }
    swap(m_allocated, size_ut);
    swap(m_data, Bmp *);
    swap(m_is_sorted, bool);
    swap(m_size, size_ut);
    swap(_middle, size_ut);
    return;
}