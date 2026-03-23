#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "AST.h"

typedef struct{
	Lexer *lexer;
	Token current_token;
} Parser;

void parser_init(Parser *parser, Lexer *lexer);
void parser_advance(Parser *parser);
void parser_expect(Parser *parser, TokenType type);


ASTNode* parse_statement(Parser* parser);
ASTNode* parse_program(Parser* parser);






//void symbol_add(const char *name, int value, VarType type);
//int symbol_get(const char *name);
//void symbol_set(const char *name, int value);


#endif