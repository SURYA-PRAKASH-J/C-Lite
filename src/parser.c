    #include "parser.h"
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "expr.h"
    #include "AST.h"
#include "lexer.h"

    #define DEBUG_TAG "PARSER"

    void parser_error(Parser* parser, const char* msg){
	    fprintf(stderr, "Parser Error [line: %d, column: %d]: %s\n", parser->current_token.position.line, parser->current_token.position.column, msg);
        exit(1);
    }

    ParserState saveState(Parser* parser){
        ParserState state;
        state.lexer = *parser->lexer;
        state.current_token = parser->current_token;
        state.next_token = parser->next_token;
        return state;
    }

    void parserRestore(Parser *parser, ParserState *state)
    {
        *parser->lexer = state->lexer;
        parser->current_token = state->current_token;
        parser->next_token = state->next_token;
    }


    static ASTNode* parse_block(Parser* parser){
        parser_expect(parser, TOKEN_OPEN_BRACES);
        BlockNode* block = (BlockNode*) create_block();

        while (parser->current_token.type != TOKEN_CLOSE_BRACES){
            //parse_statement(parser);
            ASTNode* stmt = parse_statement(parser);

            block_add_statement(block, stmt);

            if(parser->current_token.type == TOKEN_EOF){
                parser_error(parser, "Expected '}' before EOF");
            }
        }
        parser_expect(parser, TOKEN_CLOSE_BRACES);
        return (ASTNode*) block;
    }
    static ASTNode* parse_if_statement(Parser *parser){
        parser_expect(parser, TOKEN_IF);
        
        ASTNode* condition = parse_expression(parser);

        ASTNode* body = parse_block(parser);
        ASTNode* else_Branch = NULL;
        if(parser->current_token.type == TOKEN_ELSE){
            parser_expect(parser, TOKEN_ELSE);
            if(parser->current_token.type == TOKEN_IF){
                else_Branch = parse_if_statement(parser);
            }else{
                else_Branch = parse_block(parser);
            }
        }
        
        return create_if(condition, body, else_Branch);
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
        int newLineCount = 1;
        /*
        int value = parse_expression(parser);
        ASTNode* node = create_echo(value);
        if(parser->current_token.type == TOKEN_ENDL){
            printf("\n");
            parser_expect(parser, TOKEN_ENDL);
        }
        */
       while(parser->current_token.type == TOKEN_ENDL){
        newLineCount++;
        parser_advance(parser);
       }
       
        parser_expect(parser, TOKEN_SEMICOLON);
        return create_echo(expr, newLineCount);
    }
    static VarType type_identifier(Parser* parser, TokenType tokType){
        switch (tokType)
        {
        case TOKEN_INT:
            return TYPE_INT;
        case TOKEN_BOOL:
            return TYPE_BOOL;
        case TOKEN_CHAR:
            return TYPE_CHAR;
        case TOKEN_STRING:
            return TYPE_STR;
        default:
            parser_error(parser, "Unknown Type");
        }
    }
    static ASTNode* parse_var_decl(Parser *parser, TokenType type){
        VarType var_type = type_identifier(parser, type);
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

    ASTNode* parse_while(Parser* parser){
        parser_expect(parser, TOKEN_WHILE);
        ASTNode* condition = parse_expression(parser);
        ASTNode* body = parse_block(parser);
        return create_while(condition, body);
    }
    
    ASTNode* parse_function(Parser* parser, char* name, ParameterList params){
        //parser_expect(parser, TOKEN_IDENTIFIER);
        ASTNode* body = parse_block(parser);
        return create_func_declaration(name, body, params);
    }

    ASTNode* create_func_call(Parser* parser, char* name, ArgumentList args){
        //parser_expect(parser, TOKEN_SEMICOLON);
        return create_function_call(name, args);
    }

    ParameterList parse_parameter(Parser* parser){
        //Parameter *params = NULL;
        //int count = 0;
        int capacity = 4;
        ParameterList list;
        list.params = malloc(sizeof(Parameter) * capacity);
        list.count = 0;
        while(parser->current_token.type!=TOKEN_CLOSE_PAREN){
            VarType var_type = type_identifier(parser, parser->current_token.type);
            parser_expect(parser, parser->current_token.type);
            char name[64];
            strcpy(name, parser->current_token.value.ident);
            parser_expect(parser, TOKEN_IDENTIFIER);
            if (list.count >= capacity) {
                capacity *= 2;
                list.params = realloc(list.params, sizeof(Parameter) * capacity);
            }
            //if(parser->next_token.type != TOKEN_CLOSE_PAREN) parser_expect(parser, TOKEN_COMMA); //STUPID LINE OF CODE
            if (parser->current_token.type == TOKEN_COMMA) parser_expect(parser, TOKEN_COMMA);
            list.params[list.count].type = var_type;
            list.params[list.count].name = strdup(name);
            list.count++;
        }
        return list;
    }

    ArgumentList parse_args(Parser *parser)
    {
        int capacity = 4;

        ArgumentList list;
        list.args = malloc(sizeof(ASTNode*) * capacity);
        list.count = 0;

        while (parser->current_token.type != TOKEN_CLOSE_PAREN) {
            if (list.count >= capacity) {
                capacity *= 2;
                list.args = realloc(list.args,sizeof(ASTNode*) * capacity);
            }
            list.args[list.count++] = parse_expression(parser);
            if (parser->current_token.type == TOKEN_COMMA)
                parser_expect(parser, TOKEN_COMMA);
        }

        return list;
    }

    int is_type(TokenType type){
        switch (type) {
            case TOKEN_BOOL:
            case TOKEN_INT:
            case TOKEN_STRING:
            case TOKEN_CHAR:
                return 1;
                
        }
        return 0;
    }

    ASTNode* parse_identifier(Parser* parser){
        char name[64];
        strcpy(name, parser->current_token.value.ident);
        // parser_expect(parser, TOKEN_IDENTIFIER);
        // parser_expect(parser, TOKEN_OPEN_PAREN);

        // ParserState state = saveState(parser);

        // //Parameter *params = parse_parameter(parser);
        // ParameterList params = parse_parameter(parser);
        // //parser_expect(parser, TOKEN_CLOSE_PAREN);

        // parser_expect(parser, TOKEN_CLOSE_PAREN);
        // if(parser->current_token.type == TOKEN_OPEN_BRACES){
        //     return parse_function(parser, name, params);
        // } 

        // parserRestore(parser, &state);
        // ArgumentList args = parse_args(parser);
        
        // parser_expect(parser, TOKEN_CLOSE_PAREN);
        // parser_expect(parser, TOKEN_SEMICOLON);
        // return create_func_call(parser, name, args);

        parser_expect(parser, TOKEN_IDENTIFIER);
        parser_expect(parser,TOKEN_OPEN_PAREN);

        if (parser->current_token.type == TOKEN_CLOSE_PAREN) {
            ParserState state = saveState(parser);
            parser_expect(parser, TOKEN_CLOSE_PAREN);
            if(parser->current_token.type == TOKEN_OPEN_BRACES){
                ParameterList emptyParams = {
                    .params = NULL,
                    .count = 0
                };
                return parse_function(parser, name, emptyParams);
            }
            parserRestore(parser, &state);
            parser_expect(parser, TOKEN_CLOSE_PAREN);
            parser_expect(parser, TOKEN_SEMICOLON);

            ArgumentList emptyArgs = {
                .args = NULL,
                .count = 0
            };
            return create_function_call(name, emptyArgs);

        }
        else if (is_type(parser->current_token.type)) {

            ParameterList params = parse_parameter(parser);
            parser_expect(parser, TOKEN_CLOSE_PAREN);
            if (parser->current_token.type != TOKEN_OPEN_BRACES)
                parser_error(parser, "Expected '{' after parameter list");

            return parse_function(parser, name, params);
        } else {
            ArgumentList args = parse_args(parser);

            parser_expect(parser, TOKEN_CLOSE_PAREN);
            parser_expect(parser, TOKEN_SEMICOLON);

            return create_function_call(name, args);
        }
    }
        
    ASTNode* parse_statement(Parser* parser){
        switch (parser->current_token.type) {
            case TOKEN_INT:
                return parse_var_decl(parser, TOKEN_INT);
            case TOKEN_BOOL:
                return parse_var_decl(parser, TOKEN_BOOL);
                //break;
            case TOKEN_CHAR:
                return parse_var_decl(parser, TOKEN_CHAR);
            case TOKEN_STRING:
                return parse_var_decl(parser, TOKEN_STRING);
            case TOKEN_IDENTIFIER:
                if(parser->next_token.type==TOKEN_ASSIGN){
                    DEBUG_PRINT("Parsed Assignment statemnt\n");
                    return parse_assignment_statement(parser);
                }
                if(parser->next_token.type == TOKEN_OPEN_PAREN){
                    return parse_identifier(parser); //parser->current_token.value.ident);
                }
                parser_error(parser, "Unexpected identifier");
                exit(1);
            case TOKEN_OPEN_BRACES:
                return parse_block(parser);
                //break;
            case TOKEN_IF:
                return parse_if_statement(parser);
                //break;
            case TOKEN_ECHO:
                return parse_echo(parser);
                //break;
            case TOKEN_WHILE:
                return parse_while(parser);
            default:
            char buffer[256];
            snprintf(buffer, sizeof(buffer), "Parse Error: Unexpected token %s", token_type_to_string(parser->current_token.type));
            parser_error(parser, buffer);
        }
    }


    void parser_init(Parser *parser, Lexer *lexer){
        parser->lexer = lexer;
        parser->current_token = lexer_next_token(lexer);
        parser->next_token = lexer_next_token(lexer);
    }

    void parser_advance(Parser *parser){
        parser->current_token = parser->next_token;
        parser->next_token = lexer_next_token(parser->lexer);
    }

    void parser_expect(Parser *parser, TokenType type) {
        if (parser->current_token.type != type){
            char buffer[256];
            snprintf(buffer, sizeof(buffer), "Expected %s , got %s", token_type_to_string(type), token_type_to_string(parser->current_token.type));
            parser_error(parser, buffer);
        }
        parser_advance(parser);
    }

ASTNode* parse_program(Parser *parser){
    BlockNode* block = (BlockNode*) create_block();
    while(parser->current_token.type != TOKEN_EOF){
        ASTNode* stmt = parse_statement(parser);
        block_add_statement(block, stmt);
    }

        ProgramNode* program = malloc(sizeof(ProgramNode));
        program->base.type = NODE_PROGRAM;
        program->body = block;

        return (ASTNode*) program;
        
        //OLD EXECTUTION STRAIGHT FROM PARSER
        /*
        while (parser->current_token.type != TOKEN_EOF) {
            parse_statement(parser);
        }
        for(int i = 0; i<symbol_count;i++){
            DEBUG_PRINT("%s = %d\n", symbols[i].name, symbols[i].value);
        }
        printf("\n");
        */
        
        //parser_expect(parser, TOKEN_EOF);
    }

