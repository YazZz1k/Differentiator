#ifndef _PRINT_SCANF_HPP_
#define _PRINT_SCANF_HPP_

#include"../Diff/Diff.hpp"
#include<stdio.h>
#include<stdlib.h>

    static bool do_I_put_brackets(Tree* tree);
    static void print_DOT(Tree* tree, FILE* out);
    void Print_Tree(FILE* TEX,Tree* tree);

    void print(Tree* current,FILE* file);
    void print_DOT(Tree* tree);
    void print_TEX(Tree* tree, const char* file_adress);

#endif
