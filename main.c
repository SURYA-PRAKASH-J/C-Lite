#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"


int main(int argc, char *argv[]){
	if(argc < 2){
		printf("Usage: <filename>.ec [--debug]\n");
		return 1;
	}
	if (argc >=3 && strcmp(argv[2], "--debug")==0){
		LEXER_DEBUG = 1;
	}
	//Token tok;
	FILE* fptr = fopen(argv[1], "r");

	Lexer lexer;
	lexer_init(&lexer, fptr);
	/*
	do{
		tok = lexer_next_token(&lexer);
		DEBUG_PRINT("Token: %d\n", tok.type);
	}while(tok.type != TOKEN_EOF);
	*/
	Parser parser;
	parser_init(&parser, &lexer);
	parse_program(&parser);
	if(fptr == NULL){
		printf("Error: \"%s\" file does not exist\n", argv[1]);
		return 1;
	}
	fclose(fptr);
	return 0;

}
