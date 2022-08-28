#ifndef XLANG_BYTECODE_H
#define XLANG_BYTECODE_H

#include "common.h"
#include "value.h"

// TODO: change Bytecode to BCStream (bytecode stream)

/*
 * A bytecode is a sequence of instructions, each instruction 
 * consists of one-byte operation code (OpCode), followed by 
 * zero or more operands.
 */
typedef enum
{
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct
{
    int size;
    int capacity;
    uint8_t* code;
    int* lines;
    ValueArray constants;
} Bytecode;

void init_bytecode(Bytecode* bytecode);
void write_bytecode(Bytecode* bytecode, uint8_t byte, int line);
int add_constant(Bytecode* bytecode, Value value);
void free_bytecode(Bytecode* bytecode);


#endif // XLANG_BYTECODE_H 
