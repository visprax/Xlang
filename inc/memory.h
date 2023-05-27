#ifndef XLANG_MEMORY_H
#define XLANG_MEMORY_H

#include "common.h"

/*
 * Note that the parentheses around capacity is required,
 * since pre-processor macros perform text replacement before 
 * the code is compiled and capacity itself could be an expression,
 * like `1 + 2` and hence new capacity would be `1 + 2 * 2`, normally 
 * before passing `1 + 2` it would be evaluated to 3 and the new capacity 
 * will be 6 but without parentheses it will `1 + 4 = 5`!
 * Here the choice of 8 for initial capacity is arbitrary.
 * Note that in order to get the O(1) performance when appending an element,
 * we need to grow the array capacity based on it's old capacity, here we 
 * do a times 2, we could have also done 1.5x. It may seem that when we
 * grow the array and copy the old elements to the new one, the complexity 
 * is O(n), but the copying will happen sometimes and not in all cases, so 
 * based on amortized analysis, the growing of the array on average is an
 * O(1), as long as we increase the array capacity as a multiple of the old one.
 */
#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

/*
 * This macro will take care of casting the resulting 
 * `void*` back to a pointer of the right type.
 */
#define GROW_ARRAY(type, pointer, old_size, new_size) \
    (type*)reallocate(pointer, sizeof(type)*(old_size), sizeof(type)*(new_size))

#define FREE_ARRAY(type, pointer, old_size) \
    reallocate(pointer, sizeof(type)*(old_size), 0)


void* reallocate(void* pointer, size_t old_size, size_t new_size);

#endif // XLANG_MEMORY_H
