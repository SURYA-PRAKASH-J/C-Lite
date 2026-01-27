#ifndef EXPR_H
#define EXPR_H

#include "parser.h"

typedef int (*BuiltinFn)(int arg);

// Entry point for expression parsing
int parse_expression(Parser *parser);


#endif
