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
        fgets(input, ARRAY_LEN, stdin);
        printf("Inputted string \"%s\"\n", input);
        parser_set_expression(&parser, input);
        result = evaluate(parser_parse_expression(&parser, Precedence_Min));
        printf("Result: %lf\n", result);
    }
    return 0;
}