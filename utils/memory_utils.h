// memory_utils.h

#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <stdlib.h>
#include <stdio.h>

// Function declaration
void *safe_malloc(size_t size);
void *safe_realloc(void *ptr, size_t size);

#endif // MEMORY_UTILS_H
