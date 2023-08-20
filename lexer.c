#include <ctype.h>
#include "defines.h"
#include "lexer.h"

Token lexer_make_token(Lexer *lexer, TokenType type) {
    return(Token) {
        .type = type,
        .lexeme = (string) {
            .str = lexer->start,
            .size = (u32) (lexer->current - lexer->start)
        },
    };
}

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

Token lexer_next_token(Lexer *lexer) {
    while (isspace(*lexer->current)) lexer->current ++;
    lexer->start = lexer->current;
    if (*lexer->current == '\0')
        return lexer_make_token(lexer, TokenType_EOF);
    char c = *lexer->current;
    lexer->current++;
    switch(c) {
        case '(': return lexer_make_token(lexer, TokenType_OpenParen);
        case ')': return lexer_make_token(lexer, TokenType_CloseParen);
        
        case '+': return lexer_make_token(lexer, TokenType_Plus);
        case '-': return lexer_make_token(lexer, TokenType_Minus);
        case '*': return lexer_make_token(lexer, TokenType_Star);
        case '/': return lexer_make_token(lexer, TokenType_Slash);
        case '^': return lexer_make_token(lexer, TokenType_Caret);

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': return lexer_number(lexer);

        default: {
            if (isalpha(c)) return lexer_ident(lexer);
            return lexer_make_token(lexer, TokenType_Error);
        }
    }
}