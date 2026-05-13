#include "lexer.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG_TAG "LEXER"

int LEXER_DEBUG = 0;

static TokenType keyword_mapping(const char *ident){
	if(strcmp(ident, "int") == 0) return TOKEN_INT;
	if(strcmp(ident, "bool") == 0) return TOKEN_BOOL;
	if(strcmp(ident, "char") == 0) return TOKEN_CHAR;
	if(strcmp(ident, "str") == 0) return TOKEN_STRING;
	if(strcmp(ident, "string") == 0) return TOKEN_STRING;
	if(strcmp(ident, "if") == 0) return TOKEN_IF;
	if(strcmp(ident, "else") == 0) return TOKEN_ELSE;
	if(strcmp(ident, "while") == 0) return TOKEN_WHILE;
	if(strcmp(ident, "return") == 0) return TOKEN_RETURN;
	if(strcmp(ident, "true") == 0) return TOKEN_TRUE;
	if(strcmp(ident, "false") == 0) return TOKEN_FALSE;
	if(strcmp(ident, "echo") == 0) return TOKEN_ECHO;
	if(strcmp(ident, "endl") == 0) return TOKEN_ENDL;

	return TOKEN_IDENTIFIER;
}

const char* token_type_to_string(TokenType type){
	switch(type){
		case TOKEN_EOF: return "EOF";
		case TOKEN_INT: return "INT";
		case TOKEN_IDENTIFIER: return "IDENTIFIER";
		case TOKEN_INTEGER: return "INTEGER";
		case TOKEN_BOOL: return "BOOL";
		case TOKEN_CHAR: return "CHAR";
		case TOKEN_STRING: return "STRING";
		case TOKEN_IF: return "IF";
		case TOKEN_ELSE: return "ELSE";
		case TOKEN_WHILE: return "WHILE";
		case TOKEN_RETURN: return "RETURN";
		case TOKEN_TRUE: return "TRUE";
		case TOKEN_FALSE: return "FALSE";
		case TOKEN_ECHO: return "ECHO";
		case TOKEN_ENDL: return "ENDL";
		case TOKEN_PLUS: return "+";
		case TOKEN_MINUS: return "-";
		case TOKEN_MULTPLY: return "*";
		case TOKEN_DIVIDE: return "/";
		case TOKEN_OPEN_PAREN: return "(";
		case TOKEN_CLOSE_PAREN: return ")";
		case TOKEN_SINGLE_QUOTE: return "'SINGLE_QUOTE'";
		case TOKEN_STR_LTR: return "STR_LTR";
		case TOKEN_OPEN_BRACES: return "{";
		case TOKEN_CLOSE_BRACES: return "}";
		case TOKEN_NOTEQ: return "!=";
		case TOKEN_NOT: return "!";
		case TOKEN_AND: return "&";
		case TOKEN_OR: return "|";
		case TOKEN_LESS_THAN: return "<";
		case TOKEN_LESS_THAN_OR_EQ: return "<=";
		case TOKEN_GREATER_THAN: return ">";
		case TOKEN_GREAT_THAN_OR_EQ: return ">=";
		case TOKEN_EQUALS: return "==";
		case TOKEN_ASSIGN: return "=";
		case TOKEN_SEMICOLON: return ";";
		case TOKEN_UNKOWN: return "UNKOWN";
	}
	return "UNKNOWN";
}

void lexer_error(Lexer* lexer, const char* msg){
	fprintf(stderr, "Lexer Error [line: %d, column: %d]: %s\n", lexer->position.line, lexer->position.column, msg);
	exit(1);
}

Token lexer_next_token(Lexer *lexer){
	
	while(isspace((unsigned char)lexer->current_char)){
		DEBUG_PRINT("Skipping whitespace\n");
		lexer_advance(lexer);
	}
	Position start = lexer->position;
	Token token;
	token.position = start;

	if(lexer->current_char == EOF){
		token.type = TOKEN_EOF;
		DEBUG_PRINT("char = EOF\n");
		return token;
	}

	if(isdigit((unsigned char)lexer->current_char)){
		int value = 0;
		while (isdigit((unsigned char) lexer->current_char)){
			value = value * 10 + (lexer->current_char-'0');
			lexer_advance(lexer);
		}
		token.type = TOKEN_INTEGER;
		token.value.int_value = value;
		DEBUG_PRINT("INTEGER(%d)\n", token.value.int_value);
		return token;
	}

	if(isalpha((unsigned char)lexer->current_char) || lexer->current_char == '_'){
		int len = 0;
		while(isalnum((unsigned char)lexer->current_char) || lexer->current_char == '_'){
			if (len < MAX_IDENT_LEN - 1){
				token.value.ident[len++] = lexer->current_char;
			}
			lexer_advance(lexer);
		}
		token.value.ident[len] = '\0';
		token.type = keyword_mapping(token.value.ident);
		if(token.type == TOKEN_IDENTIFIER){
			DEBUG_PRINT("IDENT(%s)\n", token.value.ident);
		}else{
			DEBUG_PRINT("KEYWORD(%s)\n", token.value.ident);
		}
		return token;
	}
	if(lexer->current_char == '-'){
		lexer_advance(lexer);
		token.type = TOKEN_MINUS;
		return token;
	}
	if(lexer->current_char == '+'){
		lexer_advance(lexer);
		token.type = TOKEN_PLUS;
		return token;
	}
	if(lexer->current_char == '*'){
		lexer_advance(lexer);
		token.type = TOKEN_MULTPLY;
		return token;
	}
	if(lexer->current_char == '/'){
		lexer_advance(lexer);
		if(lexer->current_char == '/'){
			while (lexer->current_char != '\n'&& lexer->current_char != EOF){
				lexer_advance(lexer);
			}
			return lexer_next_token(lexer);
		}
		token.type = TOKEN_DIVIDE;
		return token;
	}
	if(lexer->current_char == '('){
		lexer_advance(lexer);
		token.type = TOKEN_OPEN_PAREN;
		return token;
	}
	if(lexer->current_char == ')'){
		lexer_advance(lexer);
		token.type = TOKEN_CLOSE_PAREN;
		return token;
	}
	if(lexer->current_char == '\''){
		lexer_advance(lexer);
		token.type = TOKEN_SINGLE_QUOTE;
		char c = lexer->current_char;
		lexer_advance(lexer);
		if(lexer->current_char != '\''){
			lexer_error(lexer, "Error: Expected to close the (') quote");
		}
		lexer_advance(lexer);
		token.value.int_value = (int)c;
		return token;
	}
	if(lexer->current_char == '"'){
		lexer_advance(lexer);
		token.type = TOKEN_STR_LTR;
		int len = 0;
		char buffer[256];

		while(lexer->current_char != '"' && lexer->current_char != EOF){
			if(len < 255){
				buffer[len++] = lexer->current_char;
			}
			lexer_advance(lexer);
		}
		if(lexer->current_char != '"'){
			lexer_error(lexer, "Error: String termination missing");
		}
		lexer_advance(lexer);
		buffer[len] = '\0';
		strcpy(token.value.ident, buffer);
		return token;
	}
	if(lexer->current_char == '{'){
		lexer_advance(lexer);
		token.type = TOKEN_OPEN_BRACES;
		return token;
	}
	if(lexer->current_char == '}'){
		lexer_advance(lexer);
		token.type = TOKEN_CLOSE_BRACES;
		return token;
	}
	if(lexer->current_char == '!'){
		lexer_advance(lexer);
		if(lexer->current_char == '='){
			lexer_advance(lexer);
			token.type = TOKEN_NOTEQ;
			return token;
		}
		token.type = TOKEN_NOT;
		return token;
	}
	if(lexer->current_char == '&'){
		lexer_advance(lexer);
		if(lexer->current_char == '&'){
			lexer_advance(lexer);
			token.type = TOKEN_AND;
			return token;
		}
		lexer_error(lexer, "Invalid Token '&'");
	}
	if(lexer->current_char == '|'){
		lexer_advance(lexer);
		if(lexer->current_char == '|'){
			lexer_advance(lexer);
			token.type = TOKEN_OR;
			return token;
		}
		lexer_error(lexer, "Invalid Token '|'");
	}
	if(lexer->current_char == '<'){
		lexer_advance(lexer);
		if(lexer->current_char == '='){
			lexer_advance(lexer);
			token.type = TOKEN_LESS_THAN_OR_EQ;
			return token;
		}
		token.type = TOKEN_LESS_THAN;
		return token;
	}
	if(lexer->current_char == '>'){
		lexer_advance(lexer);
		if(lexer->current_char == '='){
			lexer_advance(lexer);
			token.type = TOKEN_GREAT_THAN_OR_EQ;
			return token;
		}
		token.type = TOKEN_GREATER_THAN;
		return token;
	}
	if (lexer->current_char == '='){
		lexer_advance(lexer);
		if (lexer->current_char == '='){
			DEBUG_PRINT("found '=='\n");
			lexer_advance(lexer);
			token.type = TOKEN_EQUALS;
			return token;
		}
		token.type = TOKEN_ASSIGN;
		DEBUG_PRINT("found '='\n");
		return token;
	}
	if (lexer->current_char == ';'){
		lexer_advance(lexer);
		DEBUG_PRINT("Found ';'\n");
		token.type = TOKEN_SEMICOLON;
		return token;
	}
	DEBUG_PRINT("Current_char: [%c]\n", (unsigned char)lexer->current_char);
	lexer_advance(lexer);

	token.type = TOKEN_UNKOWN;

	return token;

}




void lexer_init(Lexer *lexer, FILE *fp){
	lexer->fp = fp;
	lexer->current_char = fgetc(fp);
	lexer->position.line = 1;
	lexer->position.column = 1;
}

void lexer_advance(Lexer *lexer){
	if(lexer->current_char == '\n'){
		lexer->position.line++;
		lexer->position.column = 1;
	}else{
		lexer->position.column += 1;
	}
	lexer->current_char = fgetc(lexer->fp);
	DEBUG_PRINT("Advancing\n");
}
