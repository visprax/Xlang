#ifndef xlang_bytecode_h
#define xlang_bytecode_h

#include "common.h"

/*
 * A bytecode is a sequence of instructions, each instruction 
 * consists of one-byte operation code (OpCode), followed by 
 * zero or more operands.
 */
typedef enum
{
    OP_RETURN,
} OpCode;

typedef struct
{
    int size;
    int capacity;
    uint8_t* code;
} Bytecode;

void init_bytecode(Bytecode* bytecode);
void write_bytecode(Bytecode* bytecode, uint8_t byte);


#endif 
