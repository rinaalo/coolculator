#include "parser.h"
#include <math.h>
#include <stdio.h>

f64 evaluate(Expression_Node *node) {
    switch(node->type) {
        case NodeType_Error:
            fprintf(stderr, "Node Type error encountered\n");
            exit(-1);
        case NodeType_Number:
            return node->number;
        case NodeType_Positive:
            return +evaluate(node->unary.operand);
        case NodeType_Negative:
            return -evaluate(node->unary.operand);
        case NodeType_Add:
            return evaluate(node->binary.left) + evaluate(node->binary.right);
        case NodeType_Sub:
            return evaluate(node->binary.left) - evaluate(node->binary.right);
        case NodeType_Mul:
            return evaluate(node->binary.left) * evaluate(node->binary.right);
        case NodeType_Div:
            return evaluate(node->binary.left) / evaluate(node->binary.right);
        case NodeType_Pow:
            return pow(evaluate(node->binary.left), evaluate(node->binary.right));
    }
}