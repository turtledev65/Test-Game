#include "dynamic-array.h"
#include <stdio.h>

void _dataResize(void *data, size_t *length, size_t *capacity, size_t dataSize)
{
  if (*length < *capacity)
    return;

  size_t newCapacity = *capacity * DYN_ARR_GROW_FACTOR;
  void *ptr = realloc(data, newCapacity * dataSize);
  if (ptr == NULL) {
    return;
  }

  *capacity *= newCapacity;

  data = ptr;
}
