#include <stdlib.h>

#include "logger.h"
#include "memory.h"
#include "bcstream.h"
#include "value.h"

static char* LOGNAME = "bcstream";

void init_bcstream(BCStream* bcstream)
{
    logger(LOGNAME, INFO, "intializing bytecode stream");
    bcstream->size = 0;
    bcstream->capacity = 0;
    bcstream->code = NULL;
    bcstream->lines = NULL;
    init_valuearray(&bcstream->constants);
}

void write_bcstream(BCStream* bcstream, uint8_t byte, int line)
{
    logger(LOGNAME, INFO, "writing bytecode stream");
    if (bcstream->capacity < bcstream->size+1)
    {
        logger(LOGNAME, DEBUG, "increasing bytecode array capacity");
        int old_capacity = bcstream->capacity;
        bcstream->capacity = GROW_CAPACITY(old_capacity);
        bcstream->code = GROW_ARRAY(uint8_t, bcstream->code, old_capacity, bcstream->capacity);
        bcstream->lines = GROW_ARRAY(int, bcstream->lines, old_capacity, bcstream->capacity);
    }

    bcstream->code[bcstream->size]  = byte;
    bcstream->lines[bcstream->size] = line;
    bcstream->size++;
        
}

int add_constant(BCStream* bcstream, Value value)
{
    logger(LOGNAME, INFO, "adding to bytecode stream the constant: %lf", value);
    write_valuearray(&bcstream->constants, value);
    return bcstream->constants.size - 1;
}

void free_bcstream(BCStream* bcstream)
{
    logger(LOGNAME, INFO, "freeing bytecode stream");
    FREE_ARRAY(uint8_t, bcstream->code, bcstream->capacity);
    FREE_ARRAY(int, bcstream->lines, bcstream->capacity);
    free_valuearray(&bcstream->constants);
    // leave the bytecode in a well-defined state
    init_bcstream(bcstream);
}
