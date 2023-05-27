#include <stdio.h>

#include "value.h"
#include "logger.h"
#include "debugger.h"

static char* LOGNAME = "debugger";

void disassemble_bcstream(BCStream* bcstream, const char* name)
{
    logger(LOGNAME, DEBUG, "disassembling bytecode stream: %s", name);
    for(int offset = 0; offset < bcstream->size;)
    {
        offset = disassemble_instruction(bcstream, offset);
    }
}

int disassemble_instruction(BCStream* bcstream, int offset)
{
    logger(LOGNAME, DEBUG, "disassembling instruction at offset: %04d, line: %4d", offset, bcstream->lines[offset]);
    uint8_t instruction = bcstream->code[offset];
    switch (instruction)
    {
        case OP_CONSTANT:
            return constant_instruction("OP_CONSTANT", bcstream, offset);
        case OP_ADD:
            return simple_instruction("OP_ADD",      offset);
        case OP_SUBTRACT:
            return simple_instruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simple_instruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simple_instruction("OP_DIVIDE",   offset);
        case OP_NEGATE:
            return simple_instruction("OP_NEGATE",   offset);
        case OP_RETURN:
            return simple_instruction("OP_RETURN",   offset);
        default:
            logger(LOGNAME, ERROR, "unknown operation code: %d", instruction);
            return offset+1;
    }
}

/*
 * Each time we add a new opcode, we have to specify what its operands 
 * look like, its instruction format. e.g. OP_RETURN has no operands, 
 * where an instruction for "load a local variable" needs an operand to
 * identify which variable to load. OP_CONSTANT takes a single byte operand 
 * that specifies which constant to load from the bytecode streams constant array.
 */
static int simple_instruction(const char* name, int offset)
{
    logger(LOGNAME, DEBUG, "got instruction: %s", name);
    return offset+1;
}

static int constant_instruction(const char* name, BCStream* bcstream, int offset)
{
    logger(LOGNAME, DEBUG, "got instruction: %s", name);
    uint8_t constant = bcstream->code[offset+1]; // constant index from the subsequent byte
    logger(LOGNAME, DEBUG, "constant index: %4d", constant);
    print_value(bcstream->constants.values[constant]); // constants are known at compile-time, so we print the actual value
    printf("'\n");
    return offset + 2; // OP_CONSTANT is two bytes, opcode and the operand
}
