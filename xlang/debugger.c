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

static int constant_instruction(const char* name, BCStream* bcstream, int offset)
{
    logger(LOGNAME, DEBUG, "got instruction: %s", name);
    uint8_t constant = bcstream->code[offset+1];
    logger(LOGNAME, DEBUG, "constant: %4d", constant);
    print_value(bcstream->constants.values[constant]);
    printf("'\n");
    // note that OP_CONSTANT is two bytes, one 
    // for opcode and the other for operand
    return offset + 2;
}

void disassemble_bcstream(BCStream* bcstream, const char* name)
{
    logger(LOGNAME, DEBUG, "disassembling bytecode stream: %s", name);
    int offset = 0;
    while (offset < bcstream->size)
    {
        offset = disassemble_instruction(bcstream, offset);
    }
}

int disassemble_instruction(BCStream* bcstream, int offset)
{
    logger(LOGNAME, DEBUG, "disassembling instruction at offset: %04d", offset);
    
    if ((offset > 0) && (bcstream->lines[offset] == bcstream->lines[offset-1]))
    {
       printf("    | "); 
    }
    else
    {
        printf("%4d", bcstream->lines[offset]);
    }

    uint8_t instruction = bcstream->code[offset];
    switch (instruction)
    {
        case OP_CONSTANT:
            return constant_instruction("OP_CONSTANT", bcstream, offset);
        case OP_RETURN:
            return simple_instruction("OP_RETURN", offset);
        default:
            logger(LOGNAME, ERROR, "unknown operation code: %d", instruction);
            return offset+1;
    }
}

