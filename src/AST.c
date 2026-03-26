#include "AST.h"
#include <stdlib.h>
#include <string.h>

ASTNode* create_literal(int val){
    LiteralNode* node = malloc(sizeof(LiteralNode));
    node->base.type = NODE_LITERAL;
    node->value = val;
    return (ASTNode*) node;
}

ASTNode* create_echo(ASTNode* expr, int newLineCount){
    EchoNode* node = malloc(sizeof(EchoNode));
    node->base.type = NODE_ECHO;
    node->expression = expr;
    node->newLineCount = newLineCount;
    return (ASTNode*) node;
}

ASTNode* create_binary(ASTNode* left, TokenType oper, ASTNode* right){
    BinaryNode* node = malloc(sizeof(BinaryNode));
    node->base.type = NODE_BINARY;
    node->left = left;
    node->oper = oper;
    node->right = right;
    return (ASTNode*) node;
}

ASTNode* create_unary(TokenType oper, ASTNode* operand){
    UnaryNode* node = malloc(sizeof(UnaryNode));
    node->base.type = NODE_UNARY;
    node->right = operand;
    node->oper = oper;
    return (ASTNode*) node;
}

ASTNode* create_block(){
    BlockNode* node = malloc(sizeof(BlockNode));
    node->base.type = NODE_BLOCK;
    node->capacity = 4;
    node->count = 0;
    node->statements = malloc(sizeof(ASTNode*) * node->capacity);
    return (ASTNode*) node;
}

ASTNode* create_variable(const char* name){
    VariableNode* node = malloc(sizeof(VariableNode));
    node->base.type = NODE_VARIABLE;
    node->name = malloc(strlen(name) + 1);
    strcpy(node->name, name);
    return (ASTNode*) node;
}

ASTNode* create_var_decl(const char* name, ASTNode* value, VarType var_type){
    VarDeclNode* node = malloc(sizeof(VarDeclNode));
    node->base.type = NODE_VAR_DECL;
    node->name = malloc(strlen(name) + 1);
    strcpy(node->name, name);
    node->value = value;
    node->var_type = var_type;

    return (ASTNode*) node;
}

ASTNode* create_assignment(const char* name, ASTNode* value){
    AssignNode* node =  malloc(sizeof(AssignNode));

    node->base.type = NODE_ASSIGN;

    node->name = malloc(strlen(name) + 1);
    strcpy(node->name, name);

    node->value = value;
    return (ASTNode*) node;
}

ASTNode* create_program(BlockNode* body){
    ProgramNode* node = malloc(sizeof(ProgramNode));
    node->base.type=NODE_PROGRAM;
    node->body = body;
    return (ASTNode*) node;
}
ASTNode* create_if(ASTNode* condition, ASTNode* body, ASTNode* elseBran) {
    IfNode* node = malloc(sizeof(IfNode));
    node->base.type = NODE_IF;
    node->condition = condition;
    node->body = body;
    node->else_branch = elseBran;
    return (ASTNode*)node;
}

ASTNode* create_while(ASTNode* condition, ASTNode* body){
    WhileNode* node = malloc(sizeof(WhileNode));
    node->base.type = NODE_WHILE;
    node->body = body;
    node->condition = condition;
    return (ASTNode*)node;
}

void block_add_statement(BlockNode *block, ASTNode *stmt)
{
    if (block->count >= block->capacity) {
        block->capacity *= 2;
        block->statements = realloc(block->statements,
            sizeof(ASTNode*) * block->capacity);
    }

    block->statements[block->count++] = stmt;
}
