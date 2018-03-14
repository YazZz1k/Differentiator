#ifndef _OPTIM_HPP_
#define _OPTIM_HPP_

#include"Diff.hpp"

#include<stdlib.h>
#include<assert.h>
#include<math.h>

#include<stack>
using namespace std;

typedef stack<Tree*> Stack;

bool Is_Zero(Tree* tree);
bool Is_One(Tree* tree);
bool Is_NUMBER(Tree* tree);
bool Is_OPERATOR(Tree* tree);
bool Is_VAR(Tree* tree);
bool Is_Constant_Tree(Tree* tree);
void EASY_MUL(Tree* tree);
void EASY_PLUS(Tree* tree);
void EASY(Tree* tree);
void EASY_Calc_Constant(Tree* tree);
double EASY_Calc(Tree* current);
void EASY_Calc_Constant_Tree(Tree* tree);


#endif
