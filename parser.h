#pragma once

#include "defines.h"
#include "lexer.h"

typedef enum {
    Precedence_Min = 0,         // Special
    Precedence_Additive,        // + and -
    Precedence_Multiplicative,  // * and /
    Precedence_Exponential,     // ^
} Precedence;

typedef enum {
    NodeType_Error,
    NodeType_Number,
    NodeType_Positive,
    NodeType_Negative,
    NodeType_Add,
    NodeType_Sub,
    NodeType_Mul,
    NodeType_Div,
    NodeType_Pow,
} Expression_Node_Type;
typedef struct Expression_Node Expression_Node;
struct Expression_Node {
    Expression_Node_Type type;
    union {
        f64 number;
        struct { Expression_Node *operand; } unary;
        struct { Expression_Node *left; Expression_Node *right; } binary;
    };
};

typedef struct Parser {
    Lexer lexer;
    Token curr;
} Parser;

void parser_set_expression(Parser *parser, char *expression);
Expression_Node *parser_parse_expression(Parser *parser, Precedence prev_precedence);
f64 evaluate(Expression_Node *node);
void parser_free_expression(Expression_Node *node);