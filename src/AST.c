#include "AST.h"
#include <stdlib.h>

ASTNode* create_literal(int val){
    LiteralNode* node = malloc(sizeof(LiteralNode));
    node->base.type = NODE_LITERAL;
    node->value = val;
    return (ASTNode*) node;
}

ASTNode* create_echo(ASTNode* expr){
    EchoNode* node = malloc(sizeof(EchoNode));
    node->base.type = NODE_ECHO;
    node->expression = expr;
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
