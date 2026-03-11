    #include "parser.h"
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "expr.h"
    #include "AST.h"

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
        DEBUG_PRINT("isSymbolFound: %d\n", symbol_find(name));
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
    static ASTNode* parse_block(Parser* parser){
        parser_expect(parser, TOKEN_OPEN_BRACES);
        BlockNode* block = (BlockNode*) create_block();

        while (parser->current_token.type != TOKEN_CLOSE_BRACES){
            //parse_statement(parser);
            ASTNode* stmt = parse_statement(parser);

            block_add_statement(block, stmt);

            if(parser->current_token.type == TOKEN_EOF){
                printf("Error: Expected '}' before EOF");
            }
        }
        parser_expect(parser, TOKEN_CLOSE_BRACES);
    }
    static ASTNode* parse_if_statement(Parser *parser){
        parser_expect(parser, TOKEN_IF);

        ASTNode* condition = parse_expression(parser);

        ASTNode* body = parse_block(parser);

        return create_if(condition, body);
        /*
        int condition;
        if(parser->current_token.type == TOKEN_OPEN_BRACES){
            parser_expect(parser, TOKEN_OPEN_BRACES);
            condition = parse_expression(parser);
            parser_expect(parser, TOKEN_CLOSE_BRACES);
        }else{
            condition = parse_expression(parser);
        }
        if(condition != 0){
            parse_block(parser);
        }else{
            parser_expect(parser, TOKEN_OPEN_BRACES);
            
            int brace_depth = 1;
            while(brace_depth > 0){
                if(parser->current_token.type == TOKEN_OPEN_BRACES){
                    brace_depth++;
                }else if (parser->current_token.type == TOKEN_CLOSE_BRACES){
                    brace_depth--;
                }
                parser_advance(parser);
            }
        }
        */

    }

    static ASTNode* parse_echo(Parser *parser){
        //VarType var_type = (type == TOKEN_BOOL) ? TYPE_BOOL : TYPE_INT;
        parser_expect(parser, TOKEN_ECHO);
        ASTNode* expr = parse_expression(parser);
        /*
        int value = parse_expression(parser);
        ASTNode* node = create_echo(value);
        if(parser->current_token.type == TOKEN_ENDL){
            printf("\n");
            parser_expect(parser, TOKEN_ENDL);
        }
        */
        parser_expect(parser, TOKEN_SEMICOLON);
        return create_echo(expr);
    }

    static ASTNode* parse_var_decl(Parser *parser, TokenType type){
        VarType var_type = (type == TOKEN_BOOL) ? TYPE_BOOL : TYPE_INT;
        parser_expect(parser, type);
        char name[64];
        strcpy(name, parser->current_token.value.ident);
        parser_expect(parser, TOKEN_IDENTIFIER);
        parser_expect(parser, TOKEN_ASSIGN);
        //int value = parse_expression(parser);
        ASTNode* value = parse_expression(parser);
        parser_expect(parser, TOKEN_SEMICOLON);
        //symbol_add(name, value, var_type);
        return create_var_decl(name, value, var_type);
    }

    static ASTNode* parse_assignment_statement(Parser *parser){
        char name[64];
        strcpy(name, parser->current_token.value.ident);
        parser_expect(parser, TOKEN_IDENTIFIER);
        parser_expect(parser, TOKEN_ASSIGN);
        ASTNode* value = parse_expression(parser);
        //int value = parse_expression(parser);
        parser_expect(parser, TOKEN_SEMICOLON);
        //symbol_set(name, value);
        return create_assignment(name, value);
    }


    ASTNode* parse_statement(Parser* parser){
        switch (parser->current_token.type) {
            case TOKEN_INT:
                return parse_var_decl(parser, TOKEN_INT);
            case TOKEN_BOOL:
                return parse_var_decl(parser, TOKEN_BOOL);
                //break;
            case TOKEN_IDENTIFIER:
                DEBUG_PRINT("Parsed Assignment statemnt\n");
                return parse_assignment_statement(parser);
                //break;
            case TOKEN_OPEN_BRACES:
                return parse_block(parser);
                //break;
            case TOKEN_IF:
                return parse_if_statement(parser);
                //break;
            case TOKEN_ECHO:
                return parse_echo(parser);
                //break;
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
        printf("\n");
        
        //parser_expect(parser, TOKEN_EOF);
    }


