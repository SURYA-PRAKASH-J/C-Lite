#include "expr.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parse_term(Parser *parser);
static int parse_factor(Parser *parser);

static int parse_comparision(Parser *parser);

int parse_factor(Parser *parser){
    int value;
    printf("DEBUG: parse_factor sees : %d\n", parser->current_token.type);
    if(parser->current_token.type == TOKEN_OPEN_PAREN){
        parser_expect(parser, TOKEN_OPEN_PAREN);
        value = parse_expression(parser);
        parser_expect(parser, TOKEN_CLOSE_PAREN);
        return value;
    }
    if(parser->current_token.type == TOKEN_MINUS){
        parser_expect(parser, TOKEN_MINUS);
        return -parse_factor(parser);

    }
    if(parser->current_token.type == TOKEN_INTEGER){
        value = parser->current_token.value.int_value;
        parser_expect(parser, TOKEN_INTEGER);
        return value;
    }

    if(parser->current_token.type == TOKEN_IDENTIFIER){
        char name[64];
        strcpy(name, parser->current_token.value.ident);
        parser_expect(parser, TOKEN_IDENTIFIER);
        return symbol_get(name);
    }
    printf("Error: Unexpected term::%d\n", parser->current_token.type);
    exit(1);
}

int parse_term(Parser *parser){
    int value = parse_factor(parser);

    while(parser->current_token.type == TOKEN_MULTPLY || parser->current_token.type == TOKEN_DIVIDE){
        TokenType op = parser->current_token.type;
        parser_expect(parser, op);
        int rhs = parse_factor(parser);
        if(op == TOKEN_MULTPLY){
            value *= rhs;
        }else{
            if(rhs == 0){
                printf("Error: division by zero\n");
                exit(1);
            }
            value /= rhs;
        }
    }
    return value;
}

static int parse_addition(Parser *parser){
    int value = parse_term(parser);
    while (parser->current_token.type == TOKEN_PLUS || parser->current_token.type == TOKEN_MINUS){
        TokenType op = parser->current_token.type;
        parser_expect(parser, op);
        int rhs = parse_term(parser);
        if(op == TOKEN_PLUS)
        {
            value += rhs;
        }
        else{
            value -= rhs;
        }
    }
    return value;

}

int parse_expression(Parser *parser){
    parse_comparision(parser);
}

static int parse_comparision(Parser *parser){
    int left = parse_addition(parser);
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
        int right = parse_addition(parser);

        switch (op)
        {
        case TOKEN_EQUALS: left = (left == right); break;
        case TOKEN_NOTEQ: left = (left != right); break;
        case TOKEN_LESS_THAN: left = (left < right); break;
        case TOKEN_GREATER_THAN: left = (left > right); break;
        case TOKEN_LESS_THAN_OR_EQ: left = (left <= right); break;
        case TOKEN_GREAT_THAN_OR_EQ: left = (left >= right); break; 
        }
    }
    return left;
}