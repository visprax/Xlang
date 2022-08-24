#ifndef xlang_chunk_h
#define xlang_chunk_h

#include "common.h"

typedef enum
{
    OP_RETURN,
} OpCode;

typedef struct
{
    uint8_t* code;
} Chunk;

#endif 
