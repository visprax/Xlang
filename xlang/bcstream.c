#include <stdlib.h>

#include "logger.h"
#include "memory.h"
#include "bytecode.h"
#include "value.h"

static char* LOGNAME = "bytecode";

void init_bytecode(Bytecode* bytecode)
{
    logger(LOGNAME, INFO, "intializing bytecode stream");
    bytecode->size = 0;
    bytecode->capacity = 0;
    bytecode->code = NULL;
    bytecode->lines = NULL;
    init_valuearray(&bytecode->constants);
}

void write_bytecode(Bytecode* bytecode, uint8_t byte, int line)
{
    logger(LOGNAME, INFO, "writing bytecode stream");
    if (bytecode->capacity < bytecode->size+1)
    {
        logger(LOGNAME, DEBUG, "increasing bytecode array capacity");
        int old_capacity = bytecode->capacity;
        bytecode->capacity = GROW_CAPACITY(old_capacity);
        bytecode->code = GROW_ARRAY(uint8_t, bytecode->code, old_capacity, bytecode->capacity);
        bytecode->lines = GROW_ARRAY(int, bytecode->lines, old_capacity, bytecode->capacity);
    }

    bytecode->code[bytecode->size]  = byte;
    bytecode->lines[bytecode->size] = line;
    bytecode->size++;
        
}

int add_constant(Bytecode* bytecode, Value value)
{
    logger(LOGNAME, INFO, "adding to bytecode stream the constant: %lf", value);
    write_valuearray(&bytecode->constants, value);
    return bytecode->constants.size - 1;
}

void free_bytecode(Bytecode* bytecode)
{
    logger(LOGNAME, INFO, "freeing bytecode stream");
    FREE_ARRAY(uint8_t, bytecode->code, bytecode->capacity);
    FREE_ARRAY(int, bytecode->lines, bytecode->capacity);
    free_valuearray(&bytecode->constants);
    // leave the bytecode in a well-defined state
    init_bytecode(bytecode);
}
