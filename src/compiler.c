#include <stdio.h>

#include "common.h"
#include "logger.h"
#include "compiler.h"
#include "scanner.h"

static char* LOGNAME = "compiler";

bool compile(const char* source, BCStream* bcstream)
{
    init_scanner(source);
    advance();
    expression();
    consume(TOKEN_EOF, "Expect end of expression.");
}
