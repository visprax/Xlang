#ifndef XLANG_BCSTREAM_H
#define XLANG_BCSTREAM_H

#include "common.h"
#include "value.h"

/*
 * A bcstream is a bytecode stream, each bytecode is a sequence of instructions, 
 * and each instruction consists of one-byte operation code (OpCode), 
 * followed by zero or more operands.
 */
typedef enum
{
    OP_CONSTANT,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_RETURN,
} OpCode;

/*
 * The BCStream struct consists of a dynamic array that stores 
 * the opcodes in a chunk of bytecode.
 */
typedef struct
{
    
    uint8_t* code; // an array of bytes, the opcodes
    int capacity;  // the capacity of the array
    int size;      // how much of the array is in use
    int* lines;
    ValueArray constants; // constants array associated with each bytecode stream
} BCStream;

void init_bcstream(BCStream* bcstream);
void write_bcstream(BCStream* bcstream, uint8_t byte, int line);
void free_bcstream(BCStream* bcstream);
int add_constant(BCStream* bcstream, Value value);


#endif // XLANG_BCSTREAM_H 
