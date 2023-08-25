#include "parser.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

void parser_set_expression(Parser *parser, char *expression) {
    parser->lexer.current = expression;
    parser->lexer.start = expression;
    parser->curr = (Token){ 0 };
}

static Precedence precedence_lookup[TokenType_MAX] = {
  [TokenType_Plus]  = Precedence_Additive,
  [TokenType_Minus] = Precedence_Additive,
  [TokenType_Star]  = Precedence_Multiplicative,
  [TokenType_Slash] = Precedence_Multiplicative,    //TODO maybe should be kept in separate precedence from mult
  [TokenType_Caret] = Precedence_Exponential,
};

#define parser_advance(parser) \
    parser->curr = lexer_next_token(&parser->lexer)

Expression_Node *alloc_node() {
    return COOL_ALLOC(sizeof(Expression_Node));
}

Expression_Node *error_node() {
    Expression_Node *ret = alloc_node();
    ret->type = NodeType_Error;
    return ret;
}

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
        default:
            fprintf(stderr, "Unknown Node Type encountered\n");
            exit(-1);
    }
}

f64 number_from_string(string str) {
    return strtod(str.str, str.str + str.size);
}

Expression_Node *parser_parse_number(Parser *parser) {
    Expression_Node *ret = alloc_node();
    ret->type = NodeType_Number;
    ret->number = number_from_string(parser->curr.lexeme);
    parser_advance(parser);
    return ret;
}

Expression_Node *parser_parse_terminal_expression(Parser *parser) {
    Expression_Node *ret = NULL;
    TokenType curr_type = parser->curr.type; 
    if (curr_type == TokenType_Number) {
        ret = parser_parse_number(parser);
    } else if (curr_type == TokenType_OpenParen) {
        parser_advance(parser);
        ret = parser_parse_expression(parser, Precedence_Min);
        if (parser->curr.type == TokenType_CloseParen) parser_advance(parser);
    } else if (curr_type == TokenType_Plus) {
        parser_advance(parser);
        ret = alloc_node();
        ret->type = NodeType_Positive;
        ret->unary.operand = parser_parse_terminal_expression(parser);
    } else if (curr_type == TokenType_Minus) {
        parser_advance(parser);
        ret = alloc_node();
        ret->type = NodeType_Negative;
        ret->unary.operand = parser_parse_terminal_expression(parser);
    } else {
        return error_node();
    }
    return ret;
}


Expression_Node * parser_parse_infix_expression(Parser *parser, Token operator, Expression_Node *left) {
    Expression_Node *ret = alloc_node();
    switch (operator.type) {
        case TokenType_Plus:    ret->type = NodeType_Add; break;
        case TokenType_Minus:   ret->type = NodeType_Sub; break;
        case TokenType_Star:    ret->type = NodeType_Mul; break;
        case TokenType_Slash:   ret->type = NodeType_Div; break;
        case TokenType_Caret:   ret->type = NodeType_Pow; break;
    }
    ret->binary.left = left;
    ret->binary.right = parser_parse_expression(parser, precedence_lookup[operator.type]);
    return ret;
}

Expression_Node *parser_parse_expression(Parser *parser, Precedence prev_precedence) {
    Expression_Node *left = parser_parse_terminal_expression(parser);
    Token curr_operator = parser->curr;
    Precedence curr_precedence = precedence_lookup[curr_operator.type];

    while (curr_precedence != Precedence_Min) {
        if (prev_precedence >= curr_precedence) {   // Higher in tree
            break;
        } else {                                    // Higher in tree
            parser_advance(parser);
            left = parser_parse_infix_expression(parser, curr_operator, left);
            curr_operator = parser->curr;
            curr_precedence = precedence_lookup[curr_operator.type];
        }
    }
    return left;
}