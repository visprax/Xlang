#include <stdio.h>
#include <string.h>

#include "common.h"
#include "logger.h"
#include "scanner.h"

static char* LOGNAME = "scanner";

Scanner scanner;

static char peek()
{
    return *scanner.current;
}

static bool is_at_end()
{
    return *scanner.current == "\0";
}

static char advance()
{
    scanner.current++;
    return scanner.current[-1];
}

static bool match(char expected)
{
    if(is_at_end()) return false;
    if(*scanner.current != expected) return false;
    scanner.current++;
    return true;
}

static void skip_whitespace()
{
    for(;;)
    {
        char c = peek();
        switch(c)
        {
            case ' ':
            case '\r':
            case '\t': 
                advance();
                break;
            case '\n':
                scanner.line++;
                advance();
                break;
            case '/':
                if(peek_next() == '/')
                {
                    while(peek() != '\n' && !is_at_end()) advance();
                }
                else
                {
                    return
                }
            default:
                return;
        }
    }
}

static Token make_token(TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

static Token error_token(const char* message)
{
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)(strlen(message));
    token.line = scanner.line;
    return token;
}

void init_scanner(const char* source)
{
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

// scans for one token at a time
Token scan_token()
{
    // advance the scanner past any leading white spaces
    skip_whitespace();
    // current points to beginning of the new lexeme
    scanner.start = scanner.current;

    // if reached to the end, tell the compiler to stop asking for tokens
    if(is_at_end()) return make_token(TOKEN_EOF);

    // single character tokens
    char c = advance();
    switch(c)
    {
        case '(': return make_token(TOKEN_LEFT_PAREN);
        case ')': return make_token(TOKEN_RIGHT_PAREN);
        case '{': return make_token(TOKEN_LEFT_BRACE);
        case '}': return make_token(TOKEN_RIGHT_BRACE);
        case ';': return make_token(TOKEN_SEMICOLON);
        case ',': return make_token(TOKEN_COMMA);
        case '.': return make_token(TOKEN_DOT);
        case '-': return make_token(TOKEN_MINUS);
        case '+': return make_token(TOKEN_PLUS);
        case '/': return make_token(TOKEN_SLASH);
        case '*': return make_token(TOKEN_STAR);
        case '!': return make_token(match('=') ? TOKEN_BANG_EQUAL   : TOKEN_BANG); // ! or !=
        case '=': return make_token(match('=') ? TOKEN_EQUAL_EQUAL  : TOKEN_EQUAL);
        case '<': return make_token(match('=') ? TOKEN_LESS_EQUAL   : TOKEN_LESS);
        case '>': return make_token(match('=') ? TOKEN_GREATER_EQUAL: TOKEN_GREATER);

    }

    return error_token("Unexpected character.")
}

