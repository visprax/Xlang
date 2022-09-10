#include "common.h"
#include "bcstream.h"
#include "debugger.h"
#include "logger.h"
#include "vm.h"


int main(int argc, const char** argv)
{
    init_vm();

    BCStream bcstream;
    init_bcstream(&bcstream);
    
    int constant = add_constant(&bcstream, 1.5);
    write_bcstream(&bcstream, OP_CONSTANT, 100);
    write_bcstream(&bcstream, constant, 100);
    write_bcstream(&bcstream, OP_NEGATE, 100);
    write_bcstream(&bcstream, OP_RETURN, 100);
    
    disassemble_bcstream(&bcstream, "Test Bytecode Stream");
    
    interpret(&bcstream);

    free_vm();

    free_bcstream(&bcstream);
    return 0;
}
