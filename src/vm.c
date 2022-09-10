#include "common.h"
#include "vm.h"

// TODO: make this a pointer that gets passed into functions
VM vm;

void init_vm()
{

}

void free_vm()
{

}

static InterpretResult run()
{
// read ip first, then advance it by one
#define READ_BYTE() (*vm.ip++)

    for(;;)
    {
        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {
            case OP_RETURN:
                {
                    return INTERPRET_OK;
                }
        }
    }
#undef READ_BYTE
}

InterpretResult interpret(BCStream* bcstream)
{
    vm.bcstream = bcstream;
    vm.ip = vm.bcstream->code;

    return run();
}
