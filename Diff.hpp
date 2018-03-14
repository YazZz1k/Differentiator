#ifndef _DIFF_HPP_
#define _DIFF_HPP_

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

typedef enum
{
    NUMBER,
    VAR,
    DIV,
    MUL,
    PLUS,
    MINUS,
    POW,
    LN,
    COS,
    SIN,
    TG,
    CTG
} Type;


typedef struct Tree
{
    struct Tree *left,
                *right;
    Type type;
    double value;
} Tree;

Tree* Create(Type type, int value, Tree* left, Tree* right);
bool do_I_put_brackets(Tree* tree);
void print(Tree* current,FILE* file);
Tree* copy(Tree* current);
void destroy(Tree* current);
Tree* Diff_NUMBER(Tree* tree);
Tree* Diff_VAR(Tree* tree);
Tree* Diff_MINUS(Tree* tree);
Tree* Diff_PLUS(Tree* tree);
Tree* Diff_MUL(Tree* tree);
Tree* Diff_POW(Tree* tree);
Tree* Diff_DIV(Tree* tree);
Tree* Diff(Tree* tree);

#endif
