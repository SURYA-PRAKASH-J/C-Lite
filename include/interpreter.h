#include "AST.h"

int eval(ASTNode* node);
void exec(ASTNode* node);
//SYbol table 
typedef struct{
	char name[64];
	int value;
	VarType type;
} Symbol;