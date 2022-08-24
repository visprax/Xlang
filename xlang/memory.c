#include <stdlib.h>

#include "memory.h"
#include "logger.h"

void* reallocate(void* pointer, size_t old_size, size_t new_size)
{
    if (new_size == 0)
    {
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer, new_size);
    if (result == NULL)
    {
        logger("CRITICAL", "couldn't reallocate an array of new size: %d", new_size);
        exit(EXIT_FAILURE);

    }
    return result;
}
