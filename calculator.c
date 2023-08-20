#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"

#define ARRAY_LEN 50


int main() {
    char input[ARRAY_LEN];
    
    while (1) {
        fgets(input, ARRAY_LEN, stdin);
        printf("Inputted string \"%s\"\n", input);

        Lexer lexer = {input, input};

        Token token;
        int j = 0;
        do {
            if (j++ > 50) break;
            token = lexer_next_token(&lexer);
            printf("Type: %i Lexeme ", token.type);
            for (size_t i = 0; i < token.lexeme.size; i++) fputc(token.lexeme.str[i], stdout);
            printf("\n");
            
        } while (token.type != TokenType_EOF && token.type != TokenType_Error);
    }
    return 0;
}