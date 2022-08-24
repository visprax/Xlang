#include "common.h"
#include "bytecode.h"
#include "logger.h"

int main(int argc, const char* argv[])
{
    Bytecode bytecode;
    init_bytecode(&bytecode);
    write_bytecode(&bytecode, OP_RETURN);
    free_bytecode(&bytecode);
    return 0;
}
