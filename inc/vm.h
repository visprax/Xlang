#ifndef XLANG_VM_H
#define XLANG_VM_H

#include "bcstream.h"
#include "value.h"

#define STACK_MAX 256

// the stream of bytecode that virtual machine will execute
typedef struct
{
    BCStream* bcstream;
    /*
     * The instruction pointer that points to the next instruction about to be executed,
     * we use an actual real C pointer right into the middle of the bytecode array 
     * instead of an integer index, because it's faster to dereference a pointer 
     * than look up an element in an array by index.
     */
    uint8_t* ip; 
    Value stack[STACK_MAX];
    Value* stack_top;
} VM;

// after running the bytecodes the vm responds with one of these results
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
