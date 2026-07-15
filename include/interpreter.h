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

typedef struct{
	char name[64];
	ParameterList params;
	ASTNode* body;

} FunctionSymbol;


Value eval(ASTNode* node);