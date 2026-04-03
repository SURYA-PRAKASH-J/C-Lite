#include "expr.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"

#define DEBUG_TAG "EXPR_PARSER"

static ASTNode* parse_term(Parser *parser);
static ASTNode* parse_factor(Parser *parser);

static ASTNode* parse_comparision(Parser *parser);

ASTNode* parse_factor(Parser *parser){
    //int value;
    DEBUG_PRINT("DEBUG: parse_factor sees : %d\n", parser->current_token.type);
    if(parser->current_token.type == TOKEN_OPEN_PAREN){
        parser_expect(parser, TOKEN_OPEN_PAREN);
        ASTNode* expr = parse_expression(parser);
        parser_expect(parser, TOKEN_CLOSE_PAREN);
        return expr;
    }
    if(parser->current_token.type == TOKEN_MINUS){
        parser_expect(parser, TOKEN_MINUS);
        ASTNode* operand = parse_factor(parser);
        return create_unary(TOKEN_MINUS, operand);
    }
    if(parser->current_token.type == TOKEN_INTEGER){
        int value = parser->current_token.value.int_value;
        parser_expect(parser, TOKEN_INTEGER);
        return create_literal(value, TYPE_INT);
    }
    if(parser->current_token.type == TOKEN_SINGLE_QUOTE){
        int value = parser->current_token.value.int_value;
        parser_expect(parser, TOKEN_SINGLE_QUOTE);
        return create_literal(value, TYPE_CHAR);
    }

    if(parser->current_token.type == TOKEN_IDENTIFIER){
        char name[64];
        strcpy(name, parser->current_token.value.ident);
        parser_expect(parser, TOKEN_IDENTIFIER);
        return create_variable(name);
    }
    if (parser->current_token.type == TOKEN_NOT) {
        parser_expect(parser, TOKEN_NOT);
        ASTNode* operand = parse_factor(parser);
        return create_unary(TOKEN_NOT, operand);
    }
    if(parser->current_token.type == TOKEN_TRUE){
        parser_expect(parser, TOKEN_TRUE);
        return create_literal(1, TYPE_BOOL);
    }
    if(parser->current_token.type == TOKEN_FALSE){
        parser_expect(parser, TOKEN_FALSE);
        return create_literal(0, TYPE_BOOL);
    }
    if(parser->current_token.type == TOKEN_STR_LTR){
        char buffer[256];
        strcpy(buffer, parser->current_token.value.ident);
        parser_expect(parser, TOKEN_STR_LTR);
        return create_str_literal(buffer);
    }
    DEBUG_PRINT("Error: Unexpected term::%d\n", parser->current_token.type);
    exit(1);
}

ASTNode* parse_term(Parser *parser){
    //int value = parse_factor(parser);

    ASTNode* left = parse_factor(parser);

    while(parser->current_token.type == TOKEN_MULTPLY || parser->current_token.type == TOKEN_DIVIDE){
        TokenType op = parser->current_token.type;
        parser_expect(parser, op);
        

        ASTNode* rigth = parse_factor(parser);

        left = create_binary(left, op, rigth);
        /*int rhs = parse_factor(parser);
        if(op == TOKEN_MULTPLY){
            value *= rhs;
        }else{
            if(rhs == 0){
                printf("Error: division by zero\n");
                exit(1);
            }
            value /= rhs;
        }
        */
    }
    return left;
}
static ASTNode* parse_and(Parser* parser) {
    ASTNode* left = parse_comparision(parser);

    while (parser->current_token.type == TOKEN_AND) {
        TokenType op = parser->current_token.type;
        parser_expect(parser, op);

        ASTNode* right = parse_comparision(parser);
        left = create_binary(left, op, right);
    }

    return left;
}
static ASTNode* parse_or(Parser* parser) {
    ASTNode* left = parse_and(parser);

    while (parser->current_token.type == TOKEN_OR) {
        TokenType op = parser->current_token.type;
        parser_expect(parser, op);

        ASTNode* right = parse_and(parser);
        left = create_binary(left, op, right);
    }

    return left;
}
static ASTNode* parse_addition(Parser *parser){
    //int value = parse_term(parser);
    ASTNode* left = parse_term(parser);

    while (parser->current_token.type == TOKEN_PLUS || parser->current_token.type == TOKEN_MINUS){
        TokenType op = parser->current_token.type;
        parser_expect(parser, op);
        
        ASTNode* rigth = parse_term(parser);
        left = create_binary(left, op, rigth);

        /*
        int rhs = parse_term(parser);
        if(op == TOKEN_PLUS)
        {
            value += rhs;
        }
        else{
            value -= rhs;
        }
        */
    }
    return left;

}

ASTNode* parse_expression(Parser *parser){
    return parse_or(parser);
}

static ASTNode* parse_comparision(Parser *parser){
    //int left = parse_addition(parser);
    ASTNode* left = parse_addition(parser);

    while (
        parser->current_token.type == TOKEN_EQUALS ||
        parser->current_token.type == TOKEN_NOTEQ ||
        parser->current_token.type == TOKEN_LESS_THAN ||
        parser->current_token.type == TOKEN_GREATER_THAN ||
        parser->current_token.type == TOKEN_LESS_THAN_OR_EQ ||
        parser->current_token.type == TOKEN_GREAT_THAN_OR_EQ
    ){
        TokenType op = parser->current_token.type;
        parser_expect(parser, op);
        //int right = parse_addition(parser);

        ASTNode* right = parse_addition(parser);
        left = create_binary(left, op, right);
        /*
        switch (op)
        {
        case TOKEN_EQUALS: left = (left == right); break;
        case TOKEN_NOTEQ: left = (left != right); break;
        case TOKEN_LESS_THAN: left = (left < right); break;
        case TOKEN_GREATER_THAN: left = (left > right); break;
        case TOKEN_LESS_THAN_OR_EQ: left = (left <= right); break;
        case TOKEN_GREAT_THAN_OR_EQ: left = (left >= right); break; 
        default: break;
        }
        */
    }
    return left;
}
