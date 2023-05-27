#include <stdlib.h>

#include "memory.h"
#include "logger.h"

static char* LOGNAME = "memory";

void* reallocate(void* pointer, size_t old_size, size_t new_size)
{
    if (new_size == 0)
    {
        free(pointer);
        return NULL;
    }

    /*
     * Note that the malloc maintains the allocated block size 
     * right before the returned address. If the new size is bigger
     * than the old size, and there is no immediate block available right 
     * after the current one, realloc will allocate a complete new block 
     * and will copy the old block to the new one.
     */
    void* result = realloc(pointer, new_size);
    if (result == NULL)
    {
        logger(LOGNAME, CRITICAL, "couldn't reallocate an array of new size: %d", new_size);
        exit(EXIT_FAILURE);

    }
    return result;
}
