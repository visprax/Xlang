#include <stdio.h>

#include "logger.h"
#include "debugger.h"

void disassemble_bytecode(Bytecode* bytecode, const char* name)
{
    logger("DEBUG", "disassembling bytecode stream: %s", name);
    int offset = 0;
    while (offset < bytecode->size)
    {
        offset = disassemble_instruction(bytecode, offset);
    }
}

int disassemble_instruction(Bytecode* bytecode, int offset)
{
    logger("DEBUG", "disassembling instruction at offset: %d", offset);
    uint8_t instruction = bytecode->code[offset];
    switch (instruction)
    {
        case OP_RETURN:
            return simple_instruction("OP_RETURN", offset);
        default:
            logger("ERROR", "unknown operation code: %d", instruction);
            return offset+1;
    }
}

static int simple_instruction(const char* name, int offset)
{
    logger("DEBUG", "got instruction: '%s'", name);
    return offset+1;
}
