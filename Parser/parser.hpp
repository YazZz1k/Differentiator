#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include"token.hpp"
#include<string.h>
#include"../Diff/Diff.hpp"
#include"stdio.h"


class Parser
{
    public:
        Arr_Token tokens;
        int ptr;
        int len;
        Tree* tree;
    public:
        Parser(const char* str);
        ~Parser();
        void Tree_Parser();
    private:
        Tree* Get_N();
        Tree* Get_T();
        Tree* Get_Z();
        Tree* Get_E();
        Tree* Get_P();

        bool Is_Unar_Operator();
        bool Is_OPERATOR(const char* str);
        bool Is_PP();

        void Input_Error();
};


#endif // _PARSER_HPP_
