#include"parser.hpp"
#include"../Dump/print_tree.hpp"


Parser::Parser(const char* str)
{
    tree = NULL;
    ptr  = 0;
    Arr_Token a(str);
    len = a.get_len();
    for(int i; i<len; i++)
    {
        tokens.push(a[i]);
    }
}


Parser::~Parser(){}


void Parser::Tree_Parser()
{
    tree = Get_E();
}


bool Parser::Is_OPERATOR(const char* str)
{
    if(tokens[ptr].type == T_OPERATOR)
        return !strcmp(tokens[ptr].value, str);
    else return false;
}


bool Parser::Is_PP()
{
    if((tokens[ptr-1].type == T_VAR)   &&(tokens[ptr].type == T_VAR)&&(strcmp(tokens[ptr-1].value, tokens[ptr].value))) return true;  //xy
    if((tokens[ptr-1].type == T_NUMBER)&&(tokens[ptr].type == T_VAR)) return true; //3x

    if((tokens[ptr-1].type == T_NUMBER)&&(tokens[ptr].type == T_BRACKET)&&(!strcmp(tokens[ptr].value, "("))) return true; //3(x+1)
    if((tokens[ptr-1].type == T_VAR)   &&(tokens[ptr].type == T_BRACKET)&&(!strcmp(tokens[ptr].value, "("))) return true; //x(x+1)

    if((tokens[ptr-1].type == T_BRACKET)&&(!strcmp(tokens[ptr-1].value, ")")&&(tokens[ptr].type == T_VAR))) return true;   //(x+1)x

    return false;
}

Tree* Parser::Get_E()
{
    Tree *left = Get_T(),
         *right= NULL;
    char operator_value[2];

    while(ptr<len)
    {
        if(Is_OPERATOR("+")||(Is_OPERATOR("-")))
        {
            strcpy(operator_value, tokens[ptr++].value);

            right = Get_T();
            left = Create(OPERATOR, operator_value, left, right);
        }
        else return left;
    }

    return left;
}


Tree* Parser::Get_T()
{
    Tree *left = Get_Z(),
         *right= NULL;

    char operator_value[2];

    while(ptr<len)
    {
        if(Is_OPERATOR("/")||Is_OPERATOR("*"))
        {
            strcpy(operator_value, tokens[ptr++].value);

            right = Get_Z();
            left = Create(OPERATOR, operator_value, left, right);
        }
        else if(Is_PP())
        {
            right = Get_Z();
            left = Create(OPERATOR, "*", left, right);
        }
        else return left;
    }

    return left;
}


Tree* Parser::Get_Z()
{
    Tree *left = Get_P(),
         *right= NULL;
    char operator_value[2];

    while(ptr<len)
    {
        if(Is_OPERATOR("^"))
        {
            strcpy(operator_value, tokens[ptr++].value);

            right = Get_P();
            left = Create(OPERATOR, operator_value, left, right);
        }
        else return left;
    }

    return left;
}


bool Parser::Is_Unar_Operator()
{
    return (Is_OPERATOR("sin")||Is_OPERATOR("cos")
           ||Is_OPERATOR("tg")||Is_OPERATOR("ctg")
           ||Is_OPERATOR("arcsin")
           ||Is_OPERATOR("arccos")
           ||Is_OPERATOR("arctg")
           ||Is_OPERATOR("arcctg")
           ||Is_OPERATOR("ln")||Is_OPERATOR("exp"));
}


Tree* Parser::Get_P()
{
    switch(tokens[ptr].type)
    {
        case T_BRACKET:
            if(!strcmp(tokens[ptr].value, "("))
            {
                ptr++;
                Tree* ret_tree = Get_E();

                if(ptr>=len)
                    printf("ERROR IN Get_P()\n");

                if(!strcmp(tokens[ptr].value, ")"))
                    ptr++;
                else printf("ERROR Get_P\n");

                return ret_tree;
            }
            else printf("ERROR IN Get_P()\n");
            break;

        case T_OPERATOR:
            if(Is_Unar_Operator())
            {
                char tmp_str[MAX_LEN_TOKEN];
                strcpy(tmp_str, tokens[ptr].value);
                ptr++;
                return Create(OPERATOR, tmp_str, NULL, Get_E());
            }
            else printf("ERROR Get_P\n");
            break;

        default: return Get_N();
    }
}


Tree* Parser::Get_N()
{
    switch(tokens[ptr].type)
    {
        case T_NUMBER: return Create(NUMBER, tokens[ptr++].value, NULL, NULL);
        case T_VAR   : return Create(VAR, tokens[ptr++].value, NULL, NULL);
        default: printf("ERROR IN Get_N() "); printf("%s\n",tokens[ptr].value);
    }
}



