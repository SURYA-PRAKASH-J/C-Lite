#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

static void parse_var_decl(Parser *parser){
    parser_expect(parser, TOKEN_INT);
    parser_expect(parser, TOKEN_IDENTIFIER);
    parser_expect(parser, TOKEN_ASSIGN);
    parser_expect(parser, TOKEN_INTEGER);
    parser_expect(parser, TOKEN_SEMICOLON);
}

static void parse_assignment_statement(Parser *parser){
    parser_expect(parser, TOKEN_IDENTIFIER);
    parser_expect(parser, TOKEN_ASSIGN);
    parser_expect(parser, TOKEN_INTEGER);
    parser_expect(parser, TOKEN_SEMICOLON);
}

void parse_statement(Parser* parser){
    switch (parser->current_token.type) {
        case TOKEN_INT:
            parse_var_decl(parser);
            printf("Parsed variable declaration \n");
            break;
        case TOKEN_IDENTIFIER:
            parse_assignment_statement(parser);
            printf("Parsed Assignment statemnt\n");
            break;

        default:
            printf("Parse Error: Unexpected token %d\n", parser->current_token.type);
            exit(1);
    }
}

void parser_init(Parser *parser, Lexer *lexer){
    parser->lexer = lexer;
    parser->current_token = lexer_next_token(lexer);
}

void parser_advance(Parser *parser){
    parser->current_token = lexer_next_token(parser->lexer);
}

void parser_expect(Parser *parser, TokenType type) {
    if (parser->current_token.type != type){
        printf("Parser Error: expected %d, got %d\n",type, parser->current_token.type );
        exit(1);
    }
    parser_advance(parser);
}

void parse_program(Parser *parser){
    while (parser->current_token.type != TOKEN_EOF) {
        parse_statement(parser);

    }
    //parser_expect(parser, TOKEN_EOF);
}
