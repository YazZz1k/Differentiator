#include"Optim.hpp"

bool Is_Zero(Tree* tree)
{
    assert(tree!=NULL);

    if((tree->type == NUMBER)&&(atof(tree->value)==0.0))
        return true;
    else
        return false;
}

bool Is_One(Tree* tree)
{
     assert(tree!=NULL);

    if((tree->type == NUMBER)&&(atof(tree->value)==1))
        return true;
    else
        return false;
}


bool Is_NUMBER(Tree* tree)
{
    assert(tree!=NULL);

    return (tree->type == NUMBER)?(true):(false);
}


bool Is_OPERATOR(Tree* tree)
{
    assert(tree!=NULL);

    return (tree->type == OPERATOR)?(true):(false);
}


bool Is_VAR(Tree* tree)
{
    assert(tree!=NULL);

    return (tree->type == VAR)?(true):(false);
}


int EASY_DIV(Tree* tree)
{
    assert(tree->left !=NULL);
    assert(tree->right!=NULL);

    if(Is_Zero(tree->left))
    {
        destroy(tree->left);
        destroy(tree->right);

        tree->type = NUMBER;
        strcpy(tree->value, "0");
        tree->left = NULL;
        tree->right= NULL;

        return 1;
    }


    if(Is_One(tree->right))
    {
        destroy(tree->right);
        Tree* tmp  = tree->left;

        tree->type = tree->left->type;
        strcpy(tree->value, tree->left->value);
        tree->right= tree->left->right;
        tree->left = tree->left->left;

        delete tmp;

        return 1;
    }

    return 0;
}


int EASY_MUL(Tree* tree)
{
    assert(tree->left !=NULL);
    assert(tree->right!=NULL);

    if(Is_Zero(tree->left)||(Is_Zero(tree->right)))
    {
        destroy(tree->left);
        destroy(tree->right);

        tree->type = NUMBER;
        strcpy(tree->value, "0");
        tree->left = NULL;
        tree->right= NULL;

        return 1;
    }

    if(Is_One(tree->left))
    {
        destroy(tree->left);
        Tree* tmp  = tree->right;

        tree->type = tree->right->type;
        strcpy(tree->value,tree->right->value);
        tree->left = tree->right->left;
        tree->right= tree->right->right;

        delete tmp;

        return 1;
    }

    if(Is_One(tree->right))
    {
        destroy(tree->right);
        Tree* tmp  = tree->left;

        tree->type = tree->left->type;
        strcpy(tree->value, tree->left->value);
        tree->right= tree->left->right;
        tree->left = tree->left->left;

        delete tmp;

        return 1;
    }

    return 0;
}


int EASY_PLUS(Tree* tree)
{
    assert(tree-> left!=NULL);
    assert(tree->right!=NULL);

    if(Is_Zero(tree->left))
    {
        destroy(tree->left);
        Tree* tmp  = tree->right;

        tree->type = tree->right->type;
        strcpy(tree->value, tree->right->value);
        tree->left = tree->right->left;
        tree->right= tree->right->right;

        delete tmp;

        return 1;
    }

    if(Is_Zero(tree->right))
    {
        destroy(tree->right);

        Tree* tmp  = tree->left;

        tree->type = tree->left->type;
        strcpy(tree->value, tree->left->value);
        tree->right= tree->left->right;
        tree->left = tree->left->left;

        delete tmp;

        return 1;
    }

    return 0;
}


int EASY_MINUS(Tree* tree)
{
    assert(tree-> left!=NULL);
    assert(tree->right!=NULL);

    if(Is_Zero(tree->left))
    {
        destroy(tree->left);
        Tree* tmp  = tree->right;

        tree->type = OPERATOR;
        strcpy(tree->value, "*");
        tree->left = Create(NUMBER, "-1", NULL, NULL);
        tree->right= tmp;

        return 1;
    }

    if(Is_Zero(tree->right))
    {
        destroy(tree->right);
        Tree* tmp  = tree->left;

        tree->type = tree->left->type;
        strcpy(tree->value, tree->left->value);
        tree->right= tree->left->right;
        tree->left = tree->left->left;

        delete tmp;

        return 1;
    }

    return 0;
}


bool Is_Constant_Tree(Tree* tree)
{
    if(tree == NULL)
        return true;
    if(Is_NUMBER(tree))
        return true;

    if(!Is_VAR(tree))
    {
        return Is_Constant_Tree(tree->left)&&Is_Constant_Tree(tree->right);
    }
    else
    {
        return false;
    }
}


void delete_zeros(char* str)
{
    int len = strlen(str)-1;
    int i = 0;
    while(str[len-i] == '0')
    {
        str[len-i] = '\0';
        i++;
    }

    if(str[strlen(str)-1] == '.')
        str[strlen(str)-1] = '\0';
}

void EASY_Calc_Constant_Tree(Tree* tree)
{
    if(Is_Constant_Tree(tree))
    {
        if(!Is_NUMBER(tree))
        {
            double value = EASY_Calc(tree);

            destroy(tree->left);
            destroy(tree->right);

            tree->type  = NUMBER;

            char tmp_str[100];
            sprintf(tmp_str, "%f", value);
            tmp_str[9] = '\0';

            delete_zeros(tmp_str);

            strcpy(tree->value, tmp_str);
            tree->left = tree->right = NULL;
        }
    }
    else
    {
        if(tree->left&&tree->right&&!Is_VAR(tree->left) &&!Is_NUMBER(tree))  EASY_Calc_Constant_Tree(tree->left);
        if(tree->left&&tree->right&&!Is_VAR(tree->right)&&!Is_NUMBER(tree))  EASY_Calc_Constant_Tree(tree->right);
    }
}


double EASY_Calc(Tree* current)   //считает дерево с константами
{
    switch(current->type)
    {
        case NUMBER: return atof(current->value);
        case OPERATOR:
            if(!strcmp("+",current->value))   return EASY_Calc(current->left) + EASY_Calc(current->right);
            if(!strcmp("-",current->value))   return EASY_Calc(current->left) - EASY_Calc(current->right);
            if(!strcmp("*",current->value))   return EASY_Calc(current->left) * EASY_Calc(current->right);
            if(!strcmp("/",current->value))   return EASY_Calc(current->left) / EASY_Calc(current->right);
            if(!strcmp("^",current->value))   return pow(EASY_Calc(current->left), EASY_Calc(current->right));
            if(!strcmp("ln",current->value))  return log(EASY_Calc(current->right));
            if(!strcmp("sin",current->value)) return sin(EASY_Calc(current->right));
            if(!strcmp("cos",current->value)) return cos(EASY_Calc(current->right));
            if(!strcmp("tg",current->value))
            {
                double a = EASY_Calc(current->right);
                return sin(a)/cos(a);
            }
            if(!strcmp("ctg",current->value))
            {
                double a = EASY_Calc(current->right);
                return cos(a)/sin(a);
            }

            printf("NAPISHI FUN %s", current->value);
            return -1;
        }
}


int EASY(Tree* tree)
{
    assert(tree!=NULL);

    int changes = 0;

    if(tree->type == OPERATOR)
    {
        if(!strcmp("*", tree->value))
        {
            if(EASY_MUL(tree))
                return 1;
        }
        else if(!strcmp("/", tree->value))
        {
            if(EASY_DIV(tree))
                return 1;
        }
        else if(!strcmp("+", tree->value))
        {
            if(EASY_PLUS(tree))
                return 1;
        }
    }

    if(tree->left!=NULL)
        changes =  EASY(tree->left);

    if(tree->right!=NULL)
        return EASY(tree->right)||changes;

    return 0;
}
