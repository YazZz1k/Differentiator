#ifndef _DIFF_HPP_
#define _DIFF_HPP_

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>

#define MAX_LEN_VALUE 10

#define _TWO_       Create(NUMBER, "2",   NULL, NULL)
#define _ONE_       Create(NUMBER, "1",   NULL, NULL)
#define _MINUS_ONE_ Create(NUMBER, "-1",  NULL, NULL)
#define _HALF_      Create(NUMBER, "0.5", NULL, NULL)
#define _ZERO_      Create(NUMBER, "0",   NULL, NULL)

//#include"../Optim/Optim.hpp"

static char DIFFERENTIATION_VAR = 'x';

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

Tree* Diff_NUMBER (Tree* tree);
Tree* Diff_VAR    (Tree* tree);


Tree* Diff_MINUS (Tree* tree);
Tree* Diff_PLUS  (Tree* tree);
Tree* Diff_MUL   (Tree* tree);
Tree* Diff_DIV   (Tree* tree);


Tree* Diff_COS (Tree* tree);
Tree* Diff_SIN (Tree* tree);
Tree* Diff_TG  (Tree* tree);
Tree* Diff_CTG (Tree* tree);


Tree* Diff_ARCCOS (Tree* tree);
Tree* Diff_ARCSIN (Tree* tree);
Tree* Diff_ARCTG  (Tree* tree);
Tree* Diff_ARCCTG (Tree* tree);


Tree* Diff_LN     (Tree* tree);
Tree* Diff_EXP    (Tree* tree);


Tree* Diff_Constant_Power(Tree* tree);
Tree* Diff_Function_Power(Tree* tree);
Tree* Diff_POW           (Tree* tree);

void Set_DIFFERENTIATION_VAR(char var);
Tree* Diff(Tree* tree);

Tree* Differentiate(Tree* tree, char var);



#endif
