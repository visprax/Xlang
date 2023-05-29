#include "common.h"
#include "bcstream.h"
#include "debugger.h"
#include "logger.h"
#include "vm.h"

static char* LOGNAME = "main";

int main(int argc, const char** argv)
{
    logger(LOGNAME, INFO, "hand compiling an example AST to bytecode");

    init_vm();
    BCStream bcstream;
    init_bcstream(&bcstream);
    
    /*
     * Here we add a constant to the bytecode stream constant pool,
     * this returns the index of the constant in the array, then we
     * write the constant instruction starting with its opcode,
     * after that we write the one-byte constant index operand.
     */
    int constant = add_constant(&bcstream, 1.0);
    write_bcstream(&bcstream, OP_CONSTANT, 100); // the line numbers are arbitrary
    write_bcstream(&bcstream, constant, 100);

    constant = add_constant(&bcstream, 1.5);
    write_bcstream(&bcstream, OP_CONSTANT, 100);
    write_bcstream(&bcstream, constant, 100);

    write_bcstream(&bcstream, OP_ADD, 100);

    constant = add_constant(&bcstream, 2.0);
    write_bcstream(&bcstream, OP_CONSTANT, 100);
    write_bcstream(&bcstream, constant, 100);

    write_bcstream(&bcstream, OP_DIVIDE, 100);
    write_bcstream(&bcstream, OP_NEGATE, 100);

    write_bcstream(&bcstream, OP_RETURN, 100);
    
    disassemble_bcstream(&bcstream, "Test Bytecode Stream");
    interpret(&bcstream);

    free_vm();
    free_bcstream(&bcstream);

    return 0;
}
