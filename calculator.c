#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

typedef uint32_t u32;

typedef enum {
    TokenType_EOF, TokenType_Error,
    TokenType_Ident, TokenType_Number,

    TokenType_Plus, TokenType_Minus,
    TokenType_Star, TokenType_Slash,
    TokenType_Caret,
    TokenType_OpenParen,
    TokenType_CloseParen,
} TokenType;

typedef struct string {
    char *str;
    size_t size;
} string;

typedef struct Token {
    TokenType type;
    string lexeme;
} Token;

typedef struct Lexer {
    // Current Token Span
    char *start;
    char *current;
} Lexer;

Token lexer_make_token(Lexer *lexer, TokenType type) {
    return(Token) {
        .type = type,
        .lexeme = (string) {
            .str = lexer->start,
            .size = (u32) (lexer->current - lexer->start)
        },
    };
}

Token lexer_next_token(Lexer *lexer) {
    while (is_whitespace(*lexer->start)) lexer->start += 1;
    lexer->current = lexer->start;
    if (*lexer->current == '\0')
        return lexer_make_token(lexer, TokenType_EOF);
}

int main() {
    printf("hi again");
    return 0;
}