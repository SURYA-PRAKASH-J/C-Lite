#ifndef LEXER_H

#define LEXER_H
#define MAX_IDENT_LEN 64
#define DEBUG_PRINT(fmt, ...) \
    do { \
        if (LEXER_DEBUG) \
            printf("DEBUG: [%s] " fmt, DEBUG_TAG, ##__VA_ARGS__); \
    } while(0)

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
	TOKEN_STRING,
	TOKEN_IDENTIFIER,
	TOKEN_INT,
	TOKEN_CHAR,
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
	TOKEN_NOTEQ,
	TOKEN_LESS_THAN,
	TOKEN_GREATER_THAN,
	TOKEN_LESS_THAN_OR_EQ,
	TOKEN_GREAT_THAN_OR_EQ,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_NOT,
	TOKEN_TRUE,
	TOKEN_FALSE,
	TOKEN_BOOL,
	TOKEN_OPEN_BRACES,
	TOKEN_CLOSE_BRACES,
	TOKEN_ECHO,
	TOKEN_SINGLE_QUOTE,
	TOKEN_STR_LTR,
	TOKEN_ENDL
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