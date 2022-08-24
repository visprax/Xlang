#include <stdlib.h>

#include "bytecode.h"
#include "memory.h"
#include "logger.h"

void init_bytecode(Bytecode* bytecode)
{
    logger("INFO", "intializing bytecode stream");
    bytecode->size = 0;
    bytecode->capacity = 0;
    bytecode->code = NULL;
}

void free_bytecode(Bytecode* bytecode)
{
    logger("INFO", "freeing bytecode stream");
    FREE_ARRAY(uint8_t, bytecode->code, bytecode->capacity);
    // leave the bytecode in a well-defined state
    init_bytecode(bytecode);
}

void write_bytecode(Bytecode* bytecode, uint8_t byte)
{
    logger("INFO", "writing bytecode stream");
    if (bytecode->capacity < bytecode->size+1)
    {
        logger("DEBUG", "increasing bytecode array capacity");
        int old_capacity = bytecode->capacity;
        bytecode->capacity = GROW_CAPACITY(old_capacity);
        bytecode->code = GROW_ARRAY(uint8_t, bytecode->code, old_capacity, bytecode->capacity);
    }

    bytecode->code[bytecode->size] = byte;
    bytecode->size++;
        
}
