#include "utils.h"

#define intArray struct intArray

size_ut size(intArray* self) { return self->m_size; }
intArray* resize(intArray* self, size_ut size) {
    if (self->m_size == size) return self;
    bool expanded{ (self->m_allocated < size) };
    if ((self->m_allocated < size) || ((size_ut)(self->m_allocated * 0.7 + 1) > size)) {
        self->m_allocated = (size_ut)((size * 1.3) + 1);
    }
    else {
        self->m_size = size;
        return self;
    }
    int1_t* tmp{ (int1_t*)(realloc(self->m_data, (sizeof(int1_t) * self->m_allocated))) };
    if (tmp != NULL) self->m_data = tmp;
    if (expanded) {
        memset(self->m_data + self->m_size, 0, (size - self->m_size) * sizeof(int1_t));
        if (tmp == NULL) {
            fprintf(stderr, "Out of memory.\n");
            return self;
        }
        // throw "Out of memory.\n";
        self->m_is_sorted = false;
    }
    self->m_data = tmp;
    self->m_size = size;
    return self;
}

intArray* remove(intArray* self, size_ut start, size_ut end) {
    memcpy(self->m_data + start, self->m_data + end, (self->m_size - end) * sizeof(int1_t));
    resize(self, self->m_size - (end - start));
    return self;
}

intArray* insert(intArray* self, int1_t value, size_ut index) {
    // std::cout << "called resize with " << self->m_size + 1 << ".\n";
    resize(self, self->m_size + 1);
    // std::cout << "called memmove with self->m_data + " << index + 1 << ", self->m_data + " << index << ", "
    //     << self->m_size - index - 1 << ".\n";
    memmove(self->m_data + index + 1, self->m_data + index, (self->m_size - index - 1) * sizeof(int1_t));
    self->m_data[index] = value;
    return self;
}

// NOTE!!!!!: this replace is NON-INCLUSIVE, like for loops.
intArray* replace(intArray* self, int1_t value, size_ut start, size_ut end) {
    // memcpy(self->m_data + start, self->m_data + end, self->m_size - end);
    // remove(start + 1, end);

    // memcpy(self->m_data + start + 1, self->m_data + end, (self->m_size - end) * sizeof(T) - 1);
    memcpy(self->m_data + start + 1, self->m_data + end, (self->m_size - end) * sizeof(int1_t));
    resize(self, self->m_size - (end - start) + 1);
    self->m_data[start] = value;
    return self;
}

intArray* pop_front(intArray* self, size_ut indexes = 1ULL) {
    memcpy(self->m_data, self->m_data + indexes, self->m_size - indexes);
    resize(self, self->m_size - indexes);
    return self;
}

intArray* push_front(intArray* self, int1_t val) {
    resize(self, ++self->m_size);
    memmove(self->m_data + 1, self->m_data, self->m_size);
    *self->m_data = val;
    return self;
}

/*
int1_t& operator[](intArray* self, size_ut index) const {
    if (index < 0) index += self->m_size;
    if (index >= self->m_size || index < 0) {
        fprintf(stderr, "Out of range.\n");
        // return T();
        throw "Out of range.\n";
    }
    return self->m_data[index];
}
intArray operator+(intArray* self, const intArray* array) const {
    intArray arr(self->m_size + array.self->m_size);
    memcpy(arr.self->m_data, self->m_data, self->m_size * sizeof(int1_t));
    memcpy(arr.self->m_data + self->m_size, array.self->m_data, array.self->m_size * sizeof(int1_t));
    self->m_is_sorted = false;
    return arr;
}
intArray* operator+=(intArray* self, const intArray* array) {
    size_ut old_size{ self->m_size };
    resize(self->m_size + array.self->m_size);
    memcpy(self->m_data + old_size, array.self->m_data, array.self->m_size * sizeof(int1_t));
    self->m_is_sorted = false;
    return self;
}
intArray* operator=(intArray* self, const intArray* array) {
    resize(array.self->m_size);
    memcpy(self->m_data, array.self->m_data, array.self->m_size * sizeof(int1_t));
    self->m_is_sorted = array.self->m_is_sorted;
    return self;
} */

/*
intArray operator+(intArray* self, const Array_view& array) const;
// Array<T> operator+(const Array_view<T> &array) const {
//     Array<T> arr(self->m_size + array.self->m_size);
//     memcpy(arr.self->m_data, self->m_data, self->m_size * sizeof(T));
//     memcpy(arr.self->m_data + self->m_size, array.self->m_data, array.size() * sizeof(T));
//     self->m_is_sorted = false;
//     return arr;
// }
intArray* operator+=(intArray* self, const Array_view& array);
// Array<T> &operator+=(const Array<T> &array) {
//     size_ut old_size{self->m_size};
//     resize(self->m_size + array.self->m_size);
//     memcpy(self->m_data + old_size, array.self->m_data, array.self->m_size * sizeof(T));
//     self->m_is_sorted = false;
//     return self;
// }
intArray* operator=(intArray* self, const Array_view& array);
// Array<T> &operator=(const Array<T> &array) {
//     resize(array.self->m_size);
//     memcpy(self->m_data, array.self->m_data, array.self->m_size * sizeof(T));
//     self->m_is_sorted = array.self->m_is_sorted;
//     return self;
// } */

size_ut find(intArray* self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _find(self, target, 0, self->m_size - 1);
}
size_ut findGreater(intArray* self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _findg(self, target, 0, self->m_size - 1);
}
size_ut findGreaterEq(intArray* self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _findge(self, target, 0, self->m_size - 1);
}
size_ut findLesser(intArray* self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _findl(self, target, 0, self->m_size - 1);
}
size_ut findLesserEq(intArray* self, int1_t target) {
    if (!self->m_size) { return 0UL; }
    if (!self->m_is_sorted) { sort(self); }
    return _findle(self, target, 0, self->m_size - 1);
}
/*
friend std::ostream& operator<<(std::ostream& out, const intArray* arr) {
    arr._print(out);
    return out;
}
friend FILE& operator<<(FILE& out, const intArray* arr) {
    arr._print(out);
    return out;
} */

intArray* clear(intArray* self) { resize(self, 0); }
size_ut _find(intArray* self, int1_t target, size_ut left, size_ut right) {
    if (right < left) return self->m_size;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target)
        return self->_middle;
    else if (self->m_data[self->_middle] > target)
        return _find(self, target, left, self->_middle - 1);
    else
        return _find(self, target, self->_middle + 1, right);
}
size_ut _findg(intArray* self, int1_t target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target)
        return _find(self, target, self->_middle + 1, right);
    else if (self->m_data[self->_middle] > target) {
        if (self->_middle == 0) { return self->_middle; }
        if (!(self->m_data[self->_middle - 1] > target)) return self->_middle;
        return _find(self, target, left, self->_middle - 1);
    }
    else
        return _find(self, target, self->_middle + 1, right);
}
size_ut _findl(intArray* self, int1_t target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target)
        return _find(self, target, self->_middle + 1, right);
    else if (self->m_data[self->_middle] > target) {
        return _find(self, target, left, self->_middle - 1);
    }
    else {
        if (self->_middle == self->m_size - 1) { return self->_middle; }
        if (!(self->m_data[self->_middle + 1] < target)) return self->_middle;
        return _find(self, target, self->_middle + 1, right);
    }
}
size_ut _findge(intArray* self, int1_t target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target) {
        if (self->_middle == self->m_size - 1) { return self->_middle; }
        return _find(self, target, self->_middle + 1, right);
    }
    else if (self->m_data[self->_middle] > target) {
        if (self->_middle == 0) { return self->_middle; }
        if (!(self->m_data[self->_middle - 1] > target)) return self->_middle - 1;
        return _find(self, target, left, self->_middle - 1);
    }
    else
        return _find(self, target, self->_middle + 1, right);
}
size_ut _findle(intArray* self, int1_t target, size_ut left, size_ut right) {
    if (right < left) return self->_middle;
    self->_middle = (left + (right - left) / 2);
    if (self->m_data[self->_middle] == target) {
        if (self->_middle == 0) { return self->_middle; }
        return _find(self, target, self->_middle + 1, right);
    }
    else if (self->m_data[self->_middle] > target) {
        return _find(self, target, left, self->_middle - 1);
    }
    else {
        if (self->_middle == self->m_size - 1) { return self->_middle; }
        if (!(self->m_data[self->_middle + 1] < target)) return self->_middle + 1;
        return _find(self, target, self->_middle + 1, right);
    }
}
intArray* push_back(intArray* self, int1_t element) {
    //    ++self->m_size;
    //    if (self->m_size > self->m_allocated) {
    //      self->m_data = realloc(self->m_data, (size_ut)(self->m_size * 1.5 + 1));
    //      self->m_allocated = (size_ut)(self->m_size * 1.5 + 1);
    //    }
    //    *(self->m_data + self->m_size - 1) = element;
    //    return self;
    resize(self, self->m_size + 1);
    self->m_data[self->m_size - 1] = element;
    self->m_is_sorted = false;
    return self;
}
intArray* pop_back(intArray* self) {
    //    --self->m_size;
    //    if (self->m_size < (size_ut)(self->m_allocated * 0.7)) {
    //      self->m_data = realloc(self->m_data, (size_ut)(self->m_size * 0.7 + 1));
    //      self->m_allocated = (size_ut)(self->m_size * 0.7 + 1);
    //    }
    //    return self;
    resize(self, self->m_size - 1);
    return self;
}

intArray* sort(intArray* self) {
    if (self->m_is_sorted) { return self; }
    qsort(self->m_data, self->m_size, sizeof(int1_t), [](const void* a, const void* b) -> int { return *((int1_t*)(a)) > *((int1_t*)(b)); });
    self->m_is_sorted = true;
    return self;
}
/*
inline bool operator==(const intArray* arr) const {
    if (self->m_size != arr.self->m_size) return 0;
    return !(memcmp(self->m_data, arr.self->m_data, self->m_size));
}
inline bool operator!=(const intArray* arr) const {
    if (self->m_size != arr.self->m_size) return 1;
    return (memcmp(self->m_data, arr.self->m_data, self->m_size));
} */