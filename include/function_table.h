#ifndef FUNCTION_TABLE
#define FUNCTION_TABLE

#include "AST.h"


void function_add(const char* name, ASTNode* body, ParameterList params);
int function_find(const char* name);
FunctionSymbol function_get(const char* name);
#endif