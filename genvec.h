/*
 * Copyright (c) 2023 genvec contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static inline size_t vector_size(void *ptr) {
    if (!ptr) return 0;

    return *((size_t *)ptr - 3);
}

static inline size_t vector_capacity(void *ptr) {
    if (!ptr) return 0;

    return *((size_t *)ptr - 2);
}

static inline size_t vector_element_size(void *ptr) {
    if (!ptr) return 0;

    return *((size_t *)ptr - 1);
}

static inline int vector_empty(void *ptr) {
  return vector_size(ptr) == 0;
}

static inline void __vector_set_size(void *ptr, size_t size) {
    if (!ptr) return;

    *((size_t *)ptr - 3) = (size_t)size;
}

static inline void __vector_set_capacity(void *ptr, size_t capacity) {
    if (!ptr) return;

    *((size_t *)ptr - 2) = (size_t)capacity;
}

static inline void *__vector_genesis(void *ptr) {
    if (!ptr) return NULL;

    return ((size_t*)(ptr) - 3);
}

static inline void *__v_alloc(void *ptr, size_t new_capacity, size_t element_size) {
    size_t size = ((ptr) ? vector_size(ptr) : 0);
    size_t *__data = (size_t *)realloc(ptr ? __vector_genesis(ptr) : NULL, (sizeof(size_t) * 3) + (new_capacity * element_size));
    __data[0] = size;
    __data[1] = new_capacity;
    __data[2] = element_size;
    return __data + 3;
}

#define vector_create(type, capacity) ((type *)__v_alloc(NULL, capacity, sizeof(type)))

#define vector_destroy(ptr) free(__vector_genesis(ptr))

#define vector_push_back(ptr, element)                                                  \
    do {                                                                                \
        if (vector_size(ptr) == vector_capacity(ptr)) {                                 \
            __vector_set_capacity(ptr, vector_capacity(ptr) * 2);                       \
            ptr = __v_alloc(ptr, vector_capacity(ptr) * 2, vector_element_size(ptr));   \
        }                                                                               \
        ptr[vector_size(ptr)] = element;                                                \
        __vector_set_size(ptr, vector_size(ptr) + 1);                                   \
    } while (0)

#define vector_pop_back(ptr) \
    do { \
        if (vector_empty(ptr)) break; \
        __vector_set_size(ptr, vector_size(ptr) - 1); \
    } while (0)

#define vector_at(ptr, index) ((ptr) ? (ptr)[index] : NULL)

#define vector_front(ptr) ((ptr) ? (ptr)[0] : NULL)

#define vector_back(ptr) ((ptr) ? (ptr)[vector_size(ptr) - 1] : NULL)

#define vector_clear(ptr) __vector_set_size(ptr, 0)