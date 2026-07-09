#ifndef FUNCTION_TABLE
#define FUNCTION_TABLE

#include "AST.h"


void function_add(const char* name, ASTNode* body);
int function_find(const char* name);
ASTNode* function_get(const char* name);
#endif