#ifndef XLANG_DEBUGGER_H
#define XLANG_DEBUGGER_H

#include "bcstream.h"

void disassemble_bcstream(BCStream* bcstream, const char* name);
int disassemble_instruction(BCStream* bcstream, int offset);
static int simple_instruction(const char* name, int offset);
static int constant_instruction(const char* name, BCStream* bcstream, int offset);

#endif // XLANG_DEBUGGER_H
