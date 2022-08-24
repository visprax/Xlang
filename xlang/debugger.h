#ifndef XLANG_DEBUGGER_H
#define XLANG_DEBUGGER_H

#include "bytecode.h"

void disassemble_bytecode(Bytecode* bytecode, const char* name);
int disassemble_instruction(Bytecode* bytecode, int offset);

#endif // XLANG_DEBUGGER_H
