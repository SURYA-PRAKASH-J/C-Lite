#include "lexer.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int LEXER_DEBUG = 0;

static TokenType keyword_mapping(const char *ident){
	if(strcmp(ident, "int") == 0) return TOKEN_INT;
	if(strcmp(ident, "if") == 0) return TOKEN_IF;
	if(strcmp(ident, "else") == 0) return TOKEN_ELSE;
	if(strcmp(ident, "while") == 0) return TOKEN_WHILE;
	if(strcmp(ident, "RETURN") == 0) return TOKEN_RETURN;
	return TOKEN_IDENTIFIER;
}



Token lexer_next_token(Lexer *lexer){

	Token token;

	while(isspace((unsigned char)lexer->current_char)){
		DEBUG_PRINT("Skipping whitespace\n");
		lexer_advance(lexer);
	}

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
		printf("INTEGER(%d)\n", token.value.int_value);
		return token;
	}

	if(isalpha((unsigned char)lexer->current_char) || lexer->current_char == '_'){
		int len = 0;
		while(isalpha((unsigned char)lexer->current_char) || lexer->current_char == '_'){
			if (len < MAX_IDENT_LEN - 1){
				token.value.ident[len++] = lexer->current_char;
			}
			lexer_advance(lexer);
		}
		token.value.ident[len] = '\0';
		token.type = keyword_mapping(token.value.ident);
		if(token.type == TOKEN_IDENTIFIER){
			printf("IDENT(%s)\n", token.value.ident);
		}else{
			printf("KEYWORD(%s)\n", token.value.ident);
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

	if (lexer->current_char == '='){
		lexer_advance(lexer);
		if (lexer->current_char == '='){
			DEBUG_PRINT("found '=='\n");
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
}

void lexer_advance(Lexer *lexer){
	lexer->current_char = fgetc(lexer->fp);
	DEBUG_PRINT("Advancing\n");
}
