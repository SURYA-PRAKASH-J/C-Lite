#include "interpreter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//--helpers---
static inline Value make_value(int val, VarType type) {
    return (Value){.value = val, .type = type, .str = NULL};
}

VarType result_type(VarType a, VarType b){
    if (a == TYPE_CHAR && b == TYPE_INT) return TYPE_CHAR;
    if (a == TYPE_INT && b == TYPE_CHAR) return TYPE_CHAR;
    return TYPE_INT;
}

static inline Value make_string(char* s){
    Value v;
    v.str = strdup(s);
    v.type = TYPE_STR;
    return v;
}

Value string_concat(Value left, Value right){
    char buffer[512];
    if(left.type == TYPE_STR && right.type == TYPE_STR){
        sprintf(buffer, "%s%s", left.str, right.str);
    }else if(left.type == TYPE_STR){
        if(right.type ==  TYPE_CHAR){
            sprintf(buffer, "%s%c", left.str, right.value);
        }else{
            sprintf(buffer, "%s%d", left.str , right.value);
        }
    }else if(right.type == TYPE_STR){
        if(left.type == TYPE_CHAR){
            sprintf(buffer, "%c%s", left.value, right.str);
        }else{
            sprintf(buffer, "%d%s", left.value, right.str);
        }
        
    }
    return make_string(buffer);
}

Value eval_add(Value left, Value right){
    if(left.type == TYPE_STR || right.type == TYPE_STR){
        return string_concat(left, right);
    }
    if(left.type == TYPE_CHAR && right.type == TYPE_CHAR){
        char buffer[3];
        buffer[0] = left.value;
        buffer[1] = right.value;
        buffer[2] = '\0';
        return make_string(buffer);
    }
    if((left.type == TYPE_CHAR && right.type == TYPE_INT) || (left.type == TYPE_INT && right.type == TYPE_CHAR))
    {
        return make_value(left.value + right.value, TYPE_CHAR);
    }

    return make_value(left.value + right.value, TYPE_INT);
}

//--helper-end

// ---SYMBOL-HANLER---
static Symbol symbols[128];
static int symbol_count = 0;
static int current_depth = 0;

int symbol_find(const char *name){
        for(int i = symbol_count - 1; i >= 0; i--){
            //printf ("strcmp(symbols[i].name, name) -> %d",strcmp(symbols[i].name, name));
            if(strcmp(symbols[i].name, name) == 0){
                return i;
            }
        }
        return -1;
}
void symbol_add(const char *name, Value value, VarType type){
    DEBUG_PRINT("isSymbolFound: %d\n", symbol_find(name));
    for (int i = symbol_count - 1; i >=0; i--){
        if (symbols[i].depth != current_depth) break;

        if (strcmp(symbols[i].name, name) == 0){
            printf("Error: Redeclared in same scope!\n");
            exit(1);
        }
    }

    Symbol* sym = &symbols[symbol_count];

    strcpy(sym->name, name);
    sym->type = type;
    sym->depth = current_depth;

    switch(type){

        case TYPE_INT:
            if(value.type == TYPE_STR){
                sym->value = strlen(value.str);
            } else {
                sym->value = value.value;
            }
            break;

        case TYPE_CHAR:
            if(value.type == TYPE_STR){
                sym->value = value.str[0];
            } else {
                sym->value = value.value;
            }
            break;

        case TYPE_STR:
            sym->str = strdup(value.str);
            break;

        default:
            sym->value = value.value;
    }

    symbol_count++;
    DEBUG_PRINT("SYMBOL ADDED\n");

}

Symbol symbol_get(const char *name){
    int i = symbol_find(name);
    if(i==-1){
        printf("Error: undefined variable %s\n", name);
        exit(1);
    }
    return symbols[i];
}

void symbol_set(const char *name, Value value){
    int i = symbol_find(name);
    if(i==-1){
        printf("Error: undefined variable %s\n", name);
        exit(1);
    }
    if(symbols[i].type == TYPE_STR){
        symbols[i].str = strdup(value.str);
    }else{
        symbols[i].value = value.value;
    }
}

//---SYMBOL-HANDLER-ENDS---


Value eval(ASTNode* node){
    switch (node->type)
    {
    case NODE_LITERAL:
        LiteralNode* lit = (LiteralNode*) node;
        if(lit->type == TYPE_STR){
            return make_string(lit->str);
        }else{
            return make_value(lit->value, lit->type);
        }
    case NODE_VARIABLE:
    {
        VariableNode* v = (VariableNode*)node;
        Symbol sym = symbol_get(v->name);
        if(sym.type == TYPE_STR){
            return make_string(sym.str);
        }else{
            return make_value(sym.value, sym.type);
        }
    }
    case NODE_BINARY:
    {
        BinaryNode* b = (BinaryNode*)node;
        Value left = eval(b->left);
        Value right = eval(b->right);
        //printf("LEFT: %d, RIGHT: %d\n", left, right);
        switch(b->oper){
            case TOKEN_PLUS: return eval_add(left, right);
            case TOKEN_MINUS: return make_value( left.value - right.value, result_type(left.type, right.type));
            case TOKEN_MULTPLY: return make_value(left.value * right.value, TYPE_INT);
            case TOKEN_DIVIDE: {if(right.value != 0 ){ return make_value(left.value/right.value, TYPE_INT); }else{printf("Error: Cannot Divide by zero"); exit(1);}}

            case TOKEN_LESS_THAN: return make_value(left.value < right.value, TYPE_BOOL);
            case TOKEN_GREATER_THAN: return make_value(left.value > right.value,  TYPE_BOOL);
            case TOKEN_LESS_THAN_OR_EQ: return make_value(left.value <= right.value, TYPE_BOOL);
            case TOKEN_GREAT_THAN_OR_EQ: return make_value(left.value >= right.value, TYPE_BOOL);
            case TOKEN_EQUALS: return make_value(left.value == right.value, TYPE_BOOL);
            case TOKEN_NOTEQ: return make_value( left.value!=right.value, TYPE_BOOL);
            
            case TOKEN_AND: return make_value(left.value && right.value, TYPE_BOOL);
            case TOKEN_OR: return make_value(left.value || right.value, TYPE_BOOL);

            default:
                printf("Invalid binary operator: %d\n", b->oper);
                exit(1);
        }
    }
    case NODE_UNARY:
    {
        UnaryNode* u = (UnaryNode*)node;
        Value val = eval(u->right);
        //if(u->oper == TOKEN_MINUS){ return -val;}
        switch (u->oper)
        {
        case TOKEN_MINUS: return make_value(-val.value, TYPE_INT);
        case TOKEN_NOT: return make_value(!(val.value), TYPE_BOOL);
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
            current_depth++;
            BlockNode* b = (BlockNode*)node;

            for(int i = 0; i < b->count; i++){
                exec(b->statements[i]);
            }
            for (int i = symbol_count -1; i >= 0; i--){
                if (symbols[i].depth == current_depth){
                    symbols[i] = symbols[symbol_count-1];
                    symbol_count--;
                }
            }
            current_depth--;
            break;
        }

        case NODE_VAR_DECL:
        {
            VarDeclNode* v = (VarDeclNode*)node;

            Value value = eval(v->value);

            symbol_add(v->name, value, v->var_type);
            break;
        }

        case NODE_ASSIGN:
        {
            AssignNode* a = (AssignNode*)node;

            Value value = eval(a->value);

            symbol_set(a->name, value);
            break;
        }

        case NODE_ECHO:
        {
            EchoNode* e = (EchoNode*)node;

            Value value = eval(e->expression);
            if(value.type == TYPE_CHAR){
                printf("%c", value.value);
            }else if(value.type == TYPE_STR)
            {
                printf("%s", value.str);
            }
            else{
                printf("%d", value.value);
            }
            for(int i=0; i< e->newLineCount; i++){
                printf("\n");
            }
            break;
        }

        case NODE_IF:
        {
            IfNode* i = (IfNode*)node;

            Value condition = eval(i->condition);

            if(condition.value){
                exec(i->body);
            }else if(i->else_branch != NULL){
                exec(i->else_branch);
            }
            break;
        }

        case NODE_WHILE:
        {
            WhileNode* wh = (WhileNode*)node;
            while(eval(wh->condition).value){
                exec(wh->body);
            }
            break;
        }
        default:
            printf("Exec error\n");
            exit(1);
    }
}