#include <ctype.h>
#include "defines.h"
#include "tokenizer.h"

Token lexer_number(Lexer *lexer) {
    while (isdigit(*lexer->current)) lexer->current++;
    if (*lexer->current == '.') {
        lexer->current++;
        while (isdigit(*lexer->current)) lexer->current++;
    }
    return lexer_make_token(lexer, TokenType_Number);
}

Token lexer_ident(Lexer *lexer) {
    if (isalpha(*lexer->current) || *lexer->current == '_') lexer->current++;
    while (isalnum(*lexer->current) || *lexer->current == '_') lexer->current++;
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
    while (isspace(*lexer->start)) lexer->start += 1;
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
            if (isalpha(*lexer->current)) return lexer_ident(lexer);
            return lexer_make_token(lexer, TokenType_Error);
        }
    }
}