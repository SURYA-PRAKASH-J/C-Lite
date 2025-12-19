#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct{
	Lexer *lexer;
	Token current_token;
} Parser;

void parser_init(Parser *parser, Lexer *lexer);
void parser_advance(Parser *parser);
void parser_expect(Parser *parser, TokenType type);

void parse_program(Parser *parser);

#endif