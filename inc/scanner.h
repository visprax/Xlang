#ifndef XLANG_SCANNER_H
#define XLANG_SCANNER_H

typedef enum
{
    // single-character token
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
    TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
    TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR,
    // one or two character tokens
    TOKEN_BANG, TOKEN_BANG_EQUAL,
    TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
    TOKEN_GREATER, TOKEN_GREATER_EQUAL,
    TOKEN_LESS, TOKEN_LESS_EQUAL,
    // literals
    TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_ELSE, TOKEN_FALSE,
    TOKEN_FOR, TOKEN_FUNC, TOKEN_IF, TOKEN_NIL, TOKEN_OR, 
    TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, TOKEN_THIS, 
    TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE,
    // special tokens
    TOKEN_ERROR, TOKEN_EOF
} TokenType;

typedef struct 
{
    const char* start;   // points to the beginning of the current lexeme being scanned
    const char* current; // points to the current character being looked at in the lexeme
    int line;            // which line the current lexeme is in
} Scanner;

typedef struct 
{
    TokenType type;
    const char* start;
    int length;
    int line;
} Token;

void init_scanner(const char* source);
Token scan_token();

#endif // XLANG_SCANNER_H
