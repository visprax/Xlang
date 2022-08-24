#ifndef xlang_memory_h
#define xlang_memory_h

#include "common.h"

/*
 * Note that the parentheses around capacity is required,
 * since pre-processor macros perform text replacement before 
 * the code is compiled and capacity itself could be an expression,
 * like `1 + 2` and hence new capacity would be `1 + 2 * 2`, normally 
 * before passing `1 + 2` it would be evaluated to 3 and the new capacity 
 * will be 6 but without parentheses it will `1 + 4 = 5`!
 * Here the choice of 8 for initial capacity is arbitrary.
 */
#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

/*
 * This macro will take care of casting the resulting 
 * `void*` back to a pointer of the right type.
 */
#define GROW_ARRAY(type, pointer, old_size, new_size) \
    (type*)reallocate(pointer, sizeof(type)*old_size, sizeof(type)*new_size)

void* reallocate(void* pointer, size_t old_size, size_t new_size);

#endif
