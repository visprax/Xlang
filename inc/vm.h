#ifndef XLANG_VM_H
#define XLANG_VM_H

#include "bcstream.h"
#include "value.h"

#define STACK_MAX 256

// the stream of bytecode that virtual machine will execute
typedef struct
{
    BCStream* bcstream;
    // the instruction pointer that points to the next instruction
    uint8_t* ip;
    Value stack[STACK_MAX];
    Value* stack_top;
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
void push(Value value);
Value pop();

#endif // XLANG_VM_H
