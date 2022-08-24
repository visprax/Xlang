#include <stdlib.h>

#include "bytecode.h"
#include "memory.h"

void init_bytecode(Bytecode* bytecode)
{
    bytecode->size = 0;
    bytecode->capacity = 0;
    bytecode->code = NULL;
}

void write_bytecode(Bytecode* bytecode, uint8_t byte)
{
    if (bytecode->capacity < bytecode->size+1)
    {
        int old_capacity = bytecode->capacity;
        bytecode->capacity = GROW_CAPACITY(old_capacity);
        bytecode->code = GROW_ARRAY(uint8_t, bytecode->code, old_capacity, bytecode->capacity);
    }

    bytecode->code[bytecode->size] = byte;
    bytecode->size++;
        
}
