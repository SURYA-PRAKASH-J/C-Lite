#include "interpreter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ---SYMBOL-HANLER---
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

//---SYMBOL-HANDLER-ENDS---
int eval(ASTNode* node){
    switch (node->type)
    {
    case NODE_LITERAL:
        return ((LiteralNode*)node)->value;
    case NODE_VARIABLE:
    {
        VariableNode* v = (VariableNode*)node;
        return symbol_get(v->name);
    }
    case NODE_BINARY:
    {
        BinaryNode* b = (BinaryNode*)node;
        int left = eval(b->left);
        int right = eval(b->right);
        //printf("LEFT: %d, RIGHT: %d\n", left, right);
        switch(b->oper){
            case TOKEN_PLUS: return left + right;
            case TOKEN_MINUS: return left - right;
            case TOKEN_MULTPLY: return left * right;
            case TOKEN_DIVIDE: {if(right != 0 ){ return left/right; }else{printf("Error: Cannot Divide by zero"); exit(1);}}

            case TOKEN_LESS_THAN: return left < right;
            case TOKEN_GREATER_THAN: return left > right;
            case TOKEN_LESS_THAN_OR_EQ: return left <= right;
            case TOKEN_GREAT_THAN_OR_EQ: return left <= right;
            case TOKEN_EQUALS: return left == right;
            case TOKEN_NOTEQ: return left!=right;
            
            case TOKEN_AND: return (left && right);
            case TOKEN_OR: return (left || right);

            default:
                printf("Invalid binary operator: %d\n", b->oper);
                exit(1);
        }
    }
    case NODE_UNARY:
    {
        UnaryNode* u = (UnaryNode*)node;
        int val = eval(u->right);
        //if(u->oper == TOKEN_MINUS){ return -val;}
        switch (u->oper)
        {
        case TOKEN_MINUS: return -val;
        case TOKEN_NOT: return !val;
        default:
            printf("Invalid Unary Token: %d", &(u->oper));
            exit(1);
        }
        return val;
    }
    
    default:
        printf("Eval Error\n");
        exit(1);
    }
}

void exec(ASTNode* node){

    switch(node->type){

        case NODE_PROGRAM:
        {
            ProgramNode* p = (ProgramNode*)node;
            exec((ASTNode*)p->body);
            break;
        }

        case NODE_BLOCK:
        {
            BlockNode* b = (BlockNode*)node;

            for(int i = 0; i < b->count; i++){
                exec(b->statements[i]);
            }
            break;
        }

        case NODE_VAR_DECL:
        {
            VarDeclNode* v = (VarDeclNode*)node;

            int value = eval(v->value);

            symbol_add(v->name, value, v->var_type);
            break;
        }

        case NODE_ASSIGN:
        {
            AssignNode* a = (AssignNode*)node;

            int value = eval(a->value);

            symbol_set(a->name, value);
            break;
        }

        case NODE_ECHO:
        {
            EchoNode* e = (EchoNode*)node;

            int value = eval(e->expression);

            printf("%d", value);
            for(int i=0; i< e->newLineCount; i++){
                printf("\n");
            }
            break;
        }

        case NODE_IF:
        {
            IfNode* i = (IfNode*)node;

            int condition = eval(i->condition);

            if(condition){
                exec(i->body);
            }else if(i->else_branch != NULL){
                exec(i->else_branch);
            }
            break;
        }

        default:
            printf("Exec error\n");
            exit(1);
    }
}