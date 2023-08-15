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

Token lexer_number(Lexer *lexer) {
    while (is_number(lexer->current)) lexer->current++;
    if (*lexer->current == '.') {
        lexer->current++;
        while (is_number(lexer->current)) lexer->current++;
    }
    return lexer_make_token(lexer, TokenType_Number);
}

Token lexer_ident(Lexer *lexer) {
    if (isalpha(lexer->current) || *lexer->current == '_') lexer->current++;
    while (isalnum(lexer->current) || *lexer->current == '_') lexer->current++;
    return lexer_make_token(lexer, TokenType_Ident);
}

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
    lexer->current++;
    switch(*lexer->current) {
        case '+': lexer->current++; return lexer_make_token(lexer, TokenType_Plus);
        case '-': lexer->current++; return lexer_make_token(lexer, TokenType_Minus);
        case '*': lexer->current++; return lexer_make_token(lexer, TokenType_Star);
        case '/': lexer->current++; return lexer_make_token(lexer, TokenType_Slash);
        case '^': lexer->current++; return lexer_make_token(lexer, TokenType_Caret);

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': return lexer_number(lexer);

        default: {
            if (is_alpha(*lexer->current)) return lexer_ident(lexer);
            return lexer_make_token(lexer, TokenType_Error);
        }
    }
}

int main() {
    printf("hi again");
    return 0;
}