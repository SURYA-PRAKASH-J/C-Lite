#ifndef LEXER_H

#define LEXER_H
#define MAX_IDENT_LEN 64
#define DEBUG_PRINT(...) \
    do { if (LEXER_DEBUG) printf("DEBUG: " __VA_ARGS__); } while (0)

#include <stdio.h>

extern int LEXER_DEBUG;

typedef struct {
	FILE* fp;
	int current_char;
} Lexer;

//TOKENS

typedef enum{
	TOKEN_EOF,
	TOKEN_UNKOWN,
	TOKEN_INTEGER,
	TOKEN_IDENTIFIER,
	TOKEN_INT,
	TOKEN_IF,
	TOKEN_ELSE,
	TOKEN_RETURN,
	TOKEN_WHILE,
	TOKEN_ASSIGN,
	TOKEN_EQUALS,
	TOKEN_SEMICOLON,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULTPLY,
	TOKEN_DIVIDE,
	TOKEN_OPEN_PAREN,
	TOKEN_CLOSE_PAREN,
	TOKEN_NOT,
	TOKEN_NOTEQ,
	TOKEN_LESS_THAN,
	TOKEN_GREATER_THAN,
	TOKEN_LESS_THAN_OR_EQ,
	TOKEN_GREAT_THAN_OR_EQ,
	TOKEN_TRUE,
	TOKEN_FALSE,
	TOKEN_BOOL
} TokenType;

typedef struct{
	TokenType  type;
	union {
		int int_value;
		char ident[MAX_IDENT_LEN]; 
	}value;
}Token;

Token lexer_next_token(Lexer *lexer);


//lexer's



void lexer_init(Lexer *lexer, FILE *fp);
void lexer_advance(Lexer *lexer);
#endif