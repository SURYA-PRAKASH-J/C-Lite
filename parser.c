#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expr.h"
static Symbol symbols[128];
static int symbol_count = 0;

int symbol_find(const char *name){
        for(int i = 0; i < symbol_count; i++){
            //printf ("strcmp(symbols[i].name, name) -> %d",strcmp(symbols[i].name, name));
            if(strcmp(symbols[i].name, name) == 0){
                return i;
            }
        }
        return -1;
}
void symbol_add(const char *name, int value, VarType type){
    printf("%d\n", symbol_find(name));
    if(symbol_find(name) != -1){
        printf("Error: Variable decalred with same name\n");
        exit(1);
    }
    strcpy(symbols[symbol_count].name, name);
    symbols[symbol_count].value = value;
    symbols[symbol_count].type = type;
    symbol_count++;
    DEBUG_PRINT("SYMBOL ADDED\n");
}

int symbol_get(const char *name){
    int i = symbol_find(name);
    if(i==-1){
        printf("Error: undefined variable %s\n", name);
        exit(1);
    }
    return symbols[i].value;
}

void symbol_set(const char *name, int value){
    int i = symbol_find(name);
    if(i==-1){
        printf("Error: undefined variable %s\n", name);
        exit(1);
    }
    symbols[i].value = value;
}


static void parse_var_decl(Parser *parser, TokenType type){
    VarType var_type = (type == TOKEN_BOOL) ? TYPE_BOOL : TYPE_INT;
    parser_expect(parser, type);
    char name[64];
    strcpy(name, parser->current_token.value.ident);
    parser_expect(parser, TOKEN_IDENTIFIER);
    parser_expect(parser, TOKEN_ASSIGN);
    int value = parse_expression(parser);
    parser_expect(parser, TOKEN_SEMICOLON);
    symbol_add(name, value, var_type);
}

static void parse_assignment_statement(Parser *parser){
    char name[64];
    strcpy(name, parser->current_token.value.ident);
    parser_expect(parser, TOKEN_IDENTIFIER);
    parser_expect(parser, TOKEN_ASSIGN);
    int value = parse_expression(parser);
    parser_expect(parser, TOKEN_SEMICOLON);
    symbol_set(name, value);
}



void parse_statement(Parser* parser){
    switch (parser->current_token.type) {
        case TOKEN_INT:
            parse_var_decl(parser, TOKEN_INT);
            break;
        case TOKEN_BOOL:
            parse_var_decl(parser, TOKEN_BOOL);
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
    
    for(int i = 0; i<symbol_count;i++){
        DEBUG_PRINT("%s = %d\n", symbols[i].name, symbols[i].value);
    }
    
    //parser_expect(parser, TOKEN_EOF);
}


