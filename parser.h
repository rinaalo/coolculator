#pragma once

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

typedef struct Expression_Node {
    Expression_Node_Type type;
    union {
        double number;
        struct { Expression_Node *operand; } unary;
        struct { Expression_Node *left; Expression_Node *right; } binary;
    } Expression_Node;
} Expression_Node;
