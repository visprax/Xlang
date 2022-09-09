#ifndef XLANG_BCSTREAM_H
#define XLANG_BCSTREAM_H

#include "common.h"
#include "value.h"

/*
 * A bcstream is a bytecode stream, sequence of instructions, 
 * each instruction consists of one-byte operation code (OpCode), 
 * followed by zero or more operands.
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
} BCStream;

void init_bcstream(BCStream* bcstream);
void write_bcstream(BCStream* bcstream, uint8_t byte, int line);
int add_constant(BCStream* bcstream, Value value);
void free_bcstream(BCStream* bcstream);


#endif // XLANG_BCSTREAM_H 
