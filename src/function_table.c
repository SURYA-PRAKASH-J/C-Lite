#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "AST.h"
#include "interpreter.h"

static FunctionSymbol functions[64];
static int function_count = 0;

void function_add(const char* name, ASTNode* body, ParameterList params){
    //printf("Adding Function");
    strcpy(functions[function_count].name, name);
    functions[function_count].body = body;
    functions[function_count].params = params;
    function_count++;
}

int function_find(const char* name){
    for (int i = 0; i < function_count; i++){
        if(strcmp(functions[i].name, name)==0){
            return i;
        }
    }
    return -1;
}

FunctionSymbol function_get(const char* name){
    int i = function_find(name);
    if(i!=-1){
        return functions[i];
    }
    printf("Error Cannot find function : %s", name);
    exit(1);
}