#ifndef XLANG_COMPILER_H
#define XLANG_COMPILER_H

#include "scanner.h"
#include "vm.h"

typedef struct
{
    Token current;
    Token previous;
    bool had_error;
    bool panic_mode;
} Parser;

bool compile(const char* source, BCStream* bcstream);

#endif // XLANG_COMPILER_H
