#include "common.h"
#include "logger.h"
#include "bytecode.h"
#include "debugger.h"


int main(int argc, const char* argv[])
{
    Bytecode bytecode;
    init_bytecode(&bytecode);
    write_bytecode(&bytecode, OP_RETURN);
    
    disassemble_bytecode(&bytecode, "Test Bytecode");

    free_bytecode(&bytecode);
    return 0;
}
