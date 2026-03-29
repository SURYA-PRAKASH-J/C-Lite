    #include "parser.h"
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "expr.h"
    #include "AST.h"


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
    static VarType type_identifier(TokenType tokType){
        switch (tokType)
        {
        case TOKEN_INT:
            return TYPE_INT;
        case TOKEN_BOOL:
            return TYPE_BOOL;
        case TOKEN_CHAR:
            return TYPE_CHAR;
        default:
            printf("Error: Unknown Type");
            exit(1);
        }
    }
    static ASTNode* parse_var_decl(Parser *parser, TokenType type){
        VarType var_type = type_identifier(type);
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


    ASTNode* parse_statement(Parser* parser){
        switch (parser->current_token.type) {
            case TOKEN_INT:
                return parse_var_decl(parser, TOKEN_INT);
            case TOKEN_BOOL:
                return parse_var_decl(parser, TOKEN_BOOL);
                //break;
            case TOKEN_CHAR:
                return parse_var_decl(parser, TOKEN_CHAR);
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
            case TOKEN_WHILE:
                return parse_while(parser);
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

