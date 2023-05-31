#ifndef XLANG_COMPILER_H
#define XLANG_COMPILER_H

#include "vm.h"

bool compile(const char* source, BCStream* bcstream);

#endif // XLANG_COMPILER_H
