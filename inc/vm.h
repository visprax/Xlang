#ifndef XLANG_VM_H
#define XLANG_VM_H

#include "bcstream.h"
#include "value.h"

/*
 * Maximum number of values we can store on the stack, if we push
 * past this number of elements on the stack, we'll have a stack overflow!
 */
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
    /*
     * This is a stack based virtual machine, when an instruction produces 
     * a value it pushed in onto the stack, when it needs to consume 
     * one or more values, it gets them by popping them off the stack.
     * Modern implementations of JVM, JavaScript, .. use JIT as opposed 
     * to a stack-based interpreter to produce faster native code on the fly.
     */
    Value stack[STACK_MAX];
    /*
     * Instead of an integer index, we use a direct pointer to the array element 
     * after the element containing the top value on the stack (faster to dereference 
     * a pointer), by pointing to element zero we know the stack is empty. stack top 
     * is where the next element to be pushed will go, it is also allowed and well-defined
     * to have an array pointer that points just past the end of an array.
     */
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

InterpretResult interpret(const char* source);

void push(Value value);
Value pop();

#endif // XLANG_VM_H
