#ifndef _DIFF_HPP_
#define _DIFF_HPP_

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>

#define MAX_LEN_VALUE 10

typedef enum
{
    NUMBER,
    VAR,
    OPERATOR
} Type;


typedef struct Tree
{
    struct Tree *left,
                *right;
    Type type;
    char value[MAX_LEN_VALUE];
} Tree;

Tree* Create(Type type,const char* value, Tree* left, Tree* right);
Tree* copy(Tree* current);
void destroy(Tree* current);
Tree* Diff_NUMBER(Tree* tree);
Tree* Diff_VAR(Tree* tree);
Tree* Diff_MINUS(Tree* tree);
Tree* Diff_PLUS(Tree* tree);
Tree* Diff_MUL(Tree* tree);
Tree* Diff_POW(Tree* tree);  //TO_DO
Tree* Diff_DIV(Tree* tree);
Tree* Diff(Tree* tree);
Tree* Diff_COS(Tree* tree);
Tree* Diff_SIN(Tree* tree);
Tree* Diff_LN(Tree* tree);

#endif
