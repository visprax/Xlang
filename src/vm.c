#include <stdio.h>

#include "common.h"
#include "logger.h"
#include "debugger.h"
#include "compiler.h"
#include "vm.h"

static char* LOGNAME = "vm";

VM vm;

static void reset_stack()
{
    // for resetting we just set the stack top to the beginning of the stack array
    vm.stack_top = vm.stack; 
}

void init_vm()
{
    logger(LOGNAME, DEBUG, "initializing virtual machine");
    reset_stack();
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

void free_vm()
{
    logger(LOGNAME, DEBUG, "freeing virtual machine");
}

static InterpretResult run()
{
// read instruction pointer first, then advance it by one
#define READ_BYTE() (*vm.ip++)
// read the next byte in the bytecode, which in the case of a constant opcode 
// is the index where the constant is in the constant table 
#define READ_CONSTANT() (vm.bcstream->constants.values[READ_BYTE()])
// note that this do while(false) trick is necessary to make sure that 
// all this falls in the same scope, e.g. imgagine a case like:
// if (condition) BINARY_OP(op); else ..., without this trick 
// this will get messy!
#define BINARY_OP(op) \
    do \
    { \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
    } while (false);

    // each loop step reads and executes single bytecode instruction
    for(;;)
    {
#ifdef DEBUG_TRACE_EXECUTION
        // print the current content of the stack
        fprintf(stdout, "          ");
        for (Value* slot = vm.stack; slot < vm.stack_top; slot++)
        {
            fprintf(stdout, "[ ");
            print_value(*slot);
            fprintf(stdout, " ]");
        }
        fprintf(stdout, "\n");
        /*
         * If debug is enabled, vm disassembles and prints each instruction before execution.
         * disassemble_instruction takes two arguments, the bytecode stream itself and 
         * a relative offset from the beginning of the bytecode stream.
         */
        disassemble_instruction(vm.bcstream, (int)(vm.ip - vm.bcstream->code));
#endif

        // decoding step or instruction dispatching
        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {
            case OP_CONSTANT:
                Value constant = READ_CONSTANT(); 
                push(constant); 
                break;
            case OP_ADD:
                BINARY_OP(+);
                break;
            case OP_SUBTRACT:
                BINARY_OP(-);
                break;
            case OP_MULTIPLY:
                BINARY_OP(*);
                break;
            case OP_DIVIDE:
                BINARY_OP(/)
            case OP_NEGATE:
                push(-pop());
                break;
            case OP_RETURN:
                print_value(pop());
                fprintf(stdout, "\n");
                return INTERPRET_OK;
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(const char* source)
{
    BCStream bcstream;
    init_bcstream(&bcstream);

    if(!compile(source, &bcstream))
    {
        free_bcstream(&bcstream);
        return INTERPRET_COMPILE_ERROR;
    }

    vm.bcstream = &bcstream;
    vm.ip = vm.bcstream->code;

    InterpretResult result = run();

    free_bcstream(&bcstream);
    return result;
}
