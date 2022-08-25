#include <stdio.h>

#include "logger.h"
#include "debugger.h"

static char* LOGNAME = "debugger";

static int simple_instruction(const char* name, int offset)
{
    logger(LOGNAME, DEBUG, "got instruction: '%s'", name);
    return offset+1;
}

void disassemble_bytecode(Bytecode* bytecode, const char* name)
{
    logger(LOGNAME, DEBUG, "disassembling bytecode stream: %s", name);
    int offset = 0;
    while (offset < bytecode->size)
    {
        offset = disassemble_instruction(bytecode, offset);
    }
}

int disassemble_instruction(Bytecode* bytecode, int offset)
{
    logger(LOGNAME, DEBUG, "disassembling instruction at offset: %04d", offset);
    uint8_t instruction = bytecode->code[offset];
    switch (instruction)
    {
        case OP_RETURN:
            return simple_instruction("OP_RETURN", offset);
        default:
            logger(LOGNAME, ERROR, "unknown operation code: %d", instruction);
            return offset+1;
    }
}

