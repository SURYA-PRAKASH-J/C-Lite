#include "AST.h"

int eval(ASTNode* node);
void exec(ASTNode* node);
//SYmbol table 
typedef struct{
	char name[64];
	int value;
	VarType type;
	int depth;
} Symbol;