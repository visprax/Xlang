#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "logger.h"
#include "compiler.h"
#include "scanner.h"

// TODO: separate module for parser

static char* LOGNAME = "compiler";

Parser parser;
BCStream* compiling_bcstream;

static bcstream* current_bcstream()
{
    return compiling_bcstream;
}

static void error_at_current(Token* token, const char* message)
{
    if(parser.panic_mode) return;
    parser.panic_mode = true;
    fprintf(stderr, "[line %d] Error", token->line);

    if(token->type == TOKEN_EOF)
    {
        fprintf(stderr, " at end");
    }
    else if(token->type == TOKEN_ERROR){  }
    else
    {
        fprintf(stderr, " at '%.*s'", token->length, token->start);
    }

    fprintf(stderr, ": %s\n", message);
    praser.had_error = true;
}

static void error(const char* message)
{
    error_at_current(&parser.current, message);
}

static void advance()
{
    parser.previous = parser.current;

    for(;;)
    {
        parser.current = scane_token();
        if(parser.current != TOKEN_ERROR) break;
        error(parser.current.start);
    }
}

static void consume(TokenType type, const char* message)
{
    if(parser.current.type == type)
    {
        advance();
        return;
    }

    error_at_current(message);
}

static void emit_byte(uint8_t byte)
{
    write_bcstream(current_bcstream(), byte, parser.previous.line);
}

static void emit_bytes(uint8_t byte1, uint8_t byte2)
{
    emit_byte(byte1);
    emit_byte(byte2);
}

static void emit_return()
{
    emit_byte(OP_RETURN);
}

static void end_compiler()
{
    emit_return();
}

bool compile(const char* source, BCStream* bcstream)
{
    init_scanner(source);

    compiling_bcstream = bcstream;

    parser.had_error  = false;
    parser.panic_mode = false;

    advance();
    expression();
    consume(TOKEN_EOF, "Expect end of expression.");

    end_compiler();
    return !parser.had_error
}
