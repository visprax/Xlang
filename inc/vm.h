#ifndef XLANG_VM_H
#define XLANG_VM_H

#include "bcstream.h"

// the stream of bytecode that virtual machine will execute
typedef struct
{
    BCStream* bcstream;
    // the instruction pointer that points to the next instruction
    uint8_t* ip;
} VM;

typedef enum
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void init_vm();
void free_vm();

InterpretResult interpret(BCStream* bcstream);

#endif // XLANG_VM_H
