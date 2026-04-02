#include "AST.h"

void exec(ASTNode* node);
//SYmbol table 
typedef struct{
	char name[64];
	int value;
	char* str;
	VarType type;
	int depth;
} Symbol;

typedef struct {
	int value;
	char* str;
    VarType type;
} Value;

Value eval(ASTNode* node);