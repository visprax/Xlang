#include "common.h"
#include "logger.h"
#include "bytecode.h"
#include "debugger.h"


int main(int argc, const char* argv[])
{
    Bytecode bytecode;
    init_bytecode(&bytecode);
    
    int constant = add_constant(&bytecode, 1.5);
    write_bytecode(&bytecode, OP_CONSTANT, 100);
    write_bytecode(&bytecode, constant, 100);

    write_bytecode(&bytecode, OP_RETURN, 100);
    
    disassemble_bytecode(&bytecode, "Test Bytecode");

    free_bytecode(&bytecode);
    return 0;
}
