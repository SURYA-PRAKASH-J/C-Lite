#ifndef EXPR_H
#define EXPR_H

#include "AST.h"
#include "parser.h"

typedef int (*BuiltinFn)(int arg);

// Entry point for expression parsing
ASTNode* parse_expression(Parser *parser);


#endif
