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


typedef enum {
    TYPE_INT,
    TYPE_BOOL
} VarType;

//SYbol table 
typedef struct{
	char name[64];
	int value;
	VarType type;
} Symbol;

void symbol_add(const char *name, int value, VarType type);
int symbol_get(const char *name);
void symbol_set(const char *name, int value);


#endif