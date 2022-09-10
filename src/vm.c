#include <stdio.h>

#include "common.h"
#include "logger.h"
#include "debugger.h"
#include "vm.h"

static char* LOGNAME = "vm";

// TODO: make this a pointer that gets passed into functions
VM vm;

static void reset_stack()
{
    vm.stack_top = vm.stack;
}

void push(Value value)
{
    *vm.stack_top = value;
    vm.stack_top++;
}

Value pop()
{
    vm.stack_top--;
    return *vm.stack_top;
}

void init_vm()
{
    logger(LOGNAME, DEBUG, "initializing virtual machine");

    reset_stack();
}

void free_vm()
{
    logger(LOGNAME, DEBUG, "freeing virtual machine");
}

static InterpretResult run()
{
// read instruction pointer first, then advance it by one
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.bcstream->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
    do \
    { \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
    } while (false);


    for(;;)
    {
#ifdef DEBUG_TRACE_EXECUTION
        printf("          ");
        for (Value* slot = vm.stack; slot < vm.stack_top; slot++)
        {
            printf("[ ");
            print_value(*slot);
            printf(" ]");
        }
        printf("\n");
/*
 * if enabled, vm disassembles and prints each instruction before execution.
 * disassemble_instruction takes two arguments, the bytecode stream itself
 * and a relative offset from the beginning of the bytecode stream.
 */
        disassemble_instruction(vm.bcstream, (int)(vm.ip - vm.bcstream->code));
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {
            case OP_CONSTANT:
                {
                    Value constant READ_CONSTANT(); 
                    push(constant); 
                    break;
                } 
            case OP_ADD:      BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE:   BINARY_OP(/); break;
            case OP_NEGATE:   push(-pop()); break;
            case OP_RETURN:
                {
                    print_value(pop());
                    printf("\n");
                    return INTERPRET_OK;
                }
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(BCStream* bcstream)
{
    vm.bcstream = bcstream;
    vm.ip = vm.bcstream->code;

    return run();
}
