#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"
#include "parser.h"

#define ARRAY_LEN 50


int main() {
    char input[ARRAY_LEN];
    f64 result;
    
    Parser parser = { 0 };
    while (true) {
        strcpy(input, " 1+    (9)*2 *(1-2 )   ");
        // fgets(input, ARRAY_LEN, stdin);
        printf("Inputted string \"%s\"\n", input);
        parser_set_expression(&parser, input);
        Expression_Node *expression_tree = parser_parse_expression(&parser, Precedence_Min);
        result = evaluate(expression_tree);
        parser_free_expression(expression_tree);
        printf("Result: %lf\n", result);
    }
    return 0;
}