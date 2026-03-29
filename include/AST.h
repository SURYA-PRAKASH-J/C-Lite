#ifndef AST_H
#define AST_H

#include "lexer.h"

typedef enum {
    TYPE_INT,
    TYPE_BOOL,
    TYPE_CHAR
} VarType;

typedef enum{
    NODE_PROGRAM,
    NODE_VAR_DECL,
    NODE_ASSIGN,
    NODE_ECHO,
    NODE_IF,
    NODE_ELSE,
    NODE_WHILE,
    NODE_BINARY,
    NODE_BLOCK,
    NODE_LITERAL,
    NODE_VARIABLE,
    NODE_UNARY
} NodeType;

typedef struct ASTNode
{
    NodeType type;
} ASTNode;

typedef struct
{
    ASTNode base;
    ASTNode* left;
    ASTNode* right;
    TokenType oper;
} BinaryNode;

typedef struct
{
    ASTNode base;
    ASTNode* right;
    TokenType oper;
} UnaryNode;

typedef struct 
{
    ASTNode base;
    int value;
    VarType type;
} LiteralNode;

typedef struct{
    ASTNode base;
    char* name;
} VariableNode;

typedef struct 
{
    ASTNode base;
    char* name;
    ASTNode* value;
    VarType var_type;
} VarDeclNode;

typedef struct 
{
    ASTNode base;
    char* name;
    ASTNode* value;
} AssignNode;

typedef struct 
{
    ASTNode base;
    ASTNode* expression;
    int newLineCount;
}EchoNode;

typedef struct 
{
    ASTNode base;
    ASTNode* condition;
    ASTNode* body;
    ASTNode* else_branch;
}IfNode;

typedef struct{
    ASTNode base;
    ASTNode* condition;
    ASTNode* body;
}WhileNode;

typedef struct 
{
    ASTNode base;
    ASTNode** statements;
    int count;
    int capacity;
}BlockNode;

typedef struct {
    ASTNode base;
    BlockNode* body;
} ProgramNode;

ASTNode* create_literal(int value, VarType type);
ASTNode* create_binary(ASTNode* left, TokenType op, ASTNode* right);
ASTNode* create_echo(ASTNode* expr, int newLineCount);
ASTNode* create_if(ASTNode* condition, ASTNode* body, ASTNode* elseBran);
//ASTNode* create_else(ASTNode* block);
ASTNode* create_while(ASTNode* condition, ASTNode* body);
ASTNode* create_block();
ASTNode* create_unary(TokenType oper, ASTNode* operand);
ASTNode* create_assignment(const char* name, ASTNode* value);
ASTNode* create_variable(const char* name);
ASTNode* create_var_decl(const char* name, ASTNode* value, VarType var_type);
void block_add_statement(BlockNode* block, ASTNode* stmt);


#endif