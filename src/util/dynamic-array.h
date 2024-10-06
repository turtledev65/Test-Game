#pragma once

#include <stdlib.h>

#define DYN_ARR_DEFAULT_CAPACITY 10
#define DYN_ARR_GROW_FACTOR 2

#define DYN_ARR(T)                                                             \
  struct {                                                                     \
    T     *data;                                                               \
    size_t length;                                                             \
    size_t capacity;                                                           \
    size_t dataSize;                                                           \
  }

#define DYN_ARR_INIT(arr)                                                      \
  do {                                                                         \
    (arr)->length   = 0;                                                       \
    (arr)->capacity = DYN_ARR_DEFAULT_CAPACITY;                                \
    (arr)->dataSize = sizeof(*(arr)->data);                                    \
    (arr)->data     = calloc((arr)->capacity, (arr)->dataSize);                \
  } while (0);

#define DYN_ARR_PUSH(arr, val)                                                 \
  do {                                                                         \
    _dataResize((arr)->data, &(arr)->length, &(arr)->capacity,                 \
                (arr)->dataSize);                                              \
    (arr)->data[(arr)->length] = val;                                          \
    ++(arr)->length;                                                           \
  } while (0);

#define DYN_ARR_POP(arr)                                                       \
  do {                                                                         \
    if ((arr)->length > 0)                                                     \
      (arr)->length--;                                                         \
  } while (0);

void _dataResize(void *data, size_t *length, size_t *capacity, size_t dataSize);
