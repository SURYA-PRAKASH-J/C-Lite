#include "AST.h"
#include "interpreter.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Hmm, cool.
VERSION = 1.3
I didn't keep track initaially, my bad


lol what

Updating this everytime i get a segfaults from now on 
[added pretty late but i rememebered the count]
SEGFAULTs = 7
*/


// Oh wait does this limits me from adding sub versions? 
// I don't know what it's called, that we use like 1.3.2
// nah i ain't gonna use (prolly not)
const float VERSION = 1.3;


int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: <filename>.cl [--debug] [-v]\n");
    return 1;
  }
  if(argc == 2){
    if(strcmp(argv[1], "-v")==0){
      printf("Version: %.1f\n", VERSION);
      return 0;
    }
  }
  if (argc >= 3 && strcmp(argv[2], "--debug") == 0) {
    LEXER_DEBUG = 1;
  }
  // Token tok;
  FILE *fptr = fopen(argv[1], "r");

  if (fptr == NULL) {
    printf("Error: \"%s\" file does not exist\n", argv[1]);
    return 1;
  }

  fseek(fptr, 0, SEEK_END);
  long size = ftell(fptr);
  rewind(fptr);

  char* buffer = malloc(size + 1);
  fread(buffer, 1, size, fptr);
  buffer[size] = '\0';


  Lexer lexer;
  lexer_init(&lexer, buffer);
  /*
  do{
          tok = lexer_next_token(&lexer);
          DEBUG_PRINT("Token: %d\n", tok.type);
  }while(tok.type != TOKEN_EOF);
  */
  Parser parser;
  parser_init(&parser, &lexer);
  // parse_program(&parser);
  ASTNode *program = parse_program(&parser);
  exec(program);
  fclose(fptr);
  return 0;
}