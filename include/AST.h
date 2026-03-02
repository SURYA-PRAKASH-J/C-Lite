#include "lexer.h"
#include "parser.h"

typedef enum{
    NODE_PROGRAM,
    NODE_VAR_DECL,
    NODE_ASSIGN,
    NODE_ECHO,
    NODE_IF,
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
}EchoNode;

typedef struct 
{
    ASTNode base;
    ASTNode* condition;
    ASTNode* body;
}IfNode;

typedef struct 
{
    ASTNode base;
    ASTNode** statements;
    int count;
    int capacity;
}BlockNode;

typedef struct {
    ASTNode base;
    ASTNode** statements;
    int count;
    int capacity;   
} ProgramNode;

ASTNode* create_literal(int value);
ASTNode* create_binary(ASTNode* left, TokenType op, ASTNode* right);
ASTNode* create_echo(ASTNode* expr);
ASTNode* create_if(ASTNode* condition, ASTNode* body);
ASTNode* create_block();
ASTNode* create_unary(TokenType oper, TokenType operand);
ASTNode* create_variable(const char* name);
ASTNode* create_var_decl(const char* name, int value, VarType var_type);
//void block_add_statement(ASTNode* block, ASTNode* stmt);





