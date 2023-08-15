#pragma once

#include "defines.h"

typedef enum {
    TokenType_EOF, TokenType_Error,
    TokenType_Ident, TokenType_Number,

    TokenType_Plus, TokenType_Minus,
    TokenType_Star, TokenType_Slash,
    TokenType_Caret,
    TokenType_OpenParen,
    TokenType_CloseParen,
} TokenType;

typedef struct Token {
    TokenType type;
    string lexeme;
} Token;

typedef struct Lexer {
    // Current Token Span
    char *start;
    char *current;
} Lexer;

Token lexer_make_token(Lexer *lexer, TokenType type);
Token lexer_next_token(Lexer *lexer);