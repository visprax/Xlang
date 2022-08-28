#include <stdio.h>

#include "value.h"
#include "logger.h"
#include "debugger.h"

static char* LOGNAME = "debugger";

static int simple_instruction(const char* name, int offset)
{
    logger(LOGNAME, DEBUG, "got instruction: %s", name);
    return offset+1;
}

static int constant_instruction(const char* name, Bytecode* bytecode, int offset)
{
    logger(LOGNAME, DEBUG, "got instruction: %s", name);
    uint8_t constant = bytecode->code[offset+1];
    logger(LOGNAME, DEBUG, "constant: %4d", constant);
    print_value(bytecode->constants.values[constant]);
    printf("'\n");
    // note that OP_CONSTANT is two bytes, one 
    // for opcode and the other for operand
    return offset + 2;
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
    
    if ((offset > 0) && (bytecode->lines[offset] == bytecode->lines[offset-1]))
    {
       printf("    | "); 
    }
    else
    {
        printf("%4d", bytecode->lines[offset]);
    }

    uint8_t instruction = bytecode->code[offset];
    switch (instruction)
    {
        case OP_CONSTANT:
            return constant_instruction("OP_CONSTANT", bytecode, offset);
        case OP_RETURN:
            return simple_instruction("OP_RETURN", offset);
        default:
            logger(LOGNAME, ERROR, "unknown operation code: %d", instruction);
            return offset+1;
    }
}

