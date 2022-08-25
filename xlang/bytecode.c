#include <stdlib.h>

#include "logger.h"
#include "memory.h"
#include "bytecode.h"
#include "value.h"

void init_bytecode(Bytecode* bytecode)
{
    logger("INFO", "intializing bytecode stream");
    bytecode->size = 0;
    bytecode->capacity = 0;
    bytecode->code = NULL;
    init_valuearray(&bytecode->constants);
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

int add_constant(Bytecode* bytecode, Value value)
{
    logger("INFO", "adding to bytecode stream the constant: %lf", value);
    write_valuearray(&bytecode->constants, value);
    return bytecode->constants.size - 1;
}

void free_bytecode(Bytecode* bytecode)
{
    logger("INFO", "freeing bytecode stream");
    FREE_ARRAY(uint8_t, bytecode->code, bytecode->capacity);
    free_valuearray(&bytecode->constants);
    // leave the bytecode in a well-defined state
    init_bytecode(bytecode);
}
