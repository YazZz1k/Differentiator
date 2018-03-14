#include"Optim.hpp"


bool Is_Zero(Tree* tree)
{
    assert(tree!=NULL);

    if((tree->type == NUMBER)&&(tree->value==0))
        return true;
    else
        return false;
}

bool Is_One(Tree* tree)
{
     assert(tree!=NULL);

    if((tree->type == NUMBER)&&(tree->value==1))
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

    switch(tree->type)
    {
        case PLUS  : return true;
        case MINUS : return true;
        case MUL   : return true;
        case DIV   : return true;
        case POW   : return true;
        case LN    : return true;
        case SIN   : return true;
        case COS   : return true;
        case TG    : return true;
        case CTG   : return true;

        default: printf("FUNC %d NE OPISAN V Is_Operator\n", tree->type);
    }
}


bool Is_VAR(Tree* tree)
{
    assert(tree!=NULL);

    return (tree->type == VAR)?(true):(false);
}


void EASY_MUL(Tree* tree)
{
    assert(tree->left !=NULL);
    assert(tree->right!=NULL);

    if(Is_Zero(tree->left)||(Is_Zero(tree->right)))
    {
        destroy(tree->left);
        destroy(tree->right);

        tree->type = NUMBER;
        tree->value=0;
        tree->left = NULL;
        tree->right= NULL;
    }

    if(tree->left&&Is_One(tree->left))
    {
        destroy(tree->left);
        Tree* tmp  = tree->right;

        tree->type = tree->right->type;
        tree->value= tree->right->value;
        tree->left = tree->right->left;
        tree->right= tree->right->right;

        delete tmp;
    }

    if(tree->right&&Is_One(tree->right))
    {
        destroy(tree->right);
        Tree* tmp  = tree->left;

        tree->type = tree->left->type;
        tree->value= tree->left->value;
        tree->right= tree->left->right;
        tree->left = tree->left->left;

        delete tmp;
    }
}


void EASY_PLUS(Tree* tree)
{
    assert(tree-> left!=NULL);
    assert(tree->right!=NULL);

    if(tree->left&&Is_Zero(tree->left))
    {
        destroy(tree->left);
        Tree* tmp  = tree->right;

        tree->type = tree->right->type;
        tree->value= tree->right->value;
        tree->left = tree->right->left;
        tree->right= tree->right->right;

        delete tmp;
    }

    if(tree->right&&Is_Zero(tree->right))
    {
        destroy(tree->right);
        Tree* tmp  = tree->left;

        tree->type = tree->left->type;
        tree->value= tree->left->value;
        tree->right= tree->left->right;
        tree->left = tree->left->left;

        delete tmp;
    }
}


void EASY(Tree* tree)
{
    assert(tree!=NULL);

    switch(tree->type)
    {
        case MUL:  EASY_MUL(tree);  break;
        case PLUS: EASY_PLUS(tree); break;
    }

    if(tree)
    {
        if(tree->left)
            EASY(tree->left);

        if(tree->right)
            EASY(tree->right);
    }
}


bool Is_Constant_Tree(Tree* tree)
{
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
            tree->value = value;

            tree->left = tree->right = NULL;
        }
    }
    else
    {
        if(!Is_VAR(tree->left) &&!Is_NUMBER(tree))  EASY_Calc_Constant_Tree(tree->left);
        if(!Is_VAR(tree->right)&&!Is_NUMBER(tree))  EASY_Calc_Constant_Tree(tree->right);
    }
}


double EASY_Calc(Tree* current)   //считает дерево с константами
{
    switch(current->type)
    {
        case NUMBER: return current->value;
        case PLUS  : return EASY_Calc(current->left) + EASY_Calc(current->right);
        case MINUS : return EASY_Calc(current->left) - EASY_Calc(current->right);
        case MUL   : return EASY_Calc(current->left) * EASY_Calc(current->right);
        case DIV   : return EASY_Calc(current->left) / EASY_Calc(current->right);
        case POW   : return pow(EASY_Calc(current->left), EASY_Calc(current->right));
        case LN    : return log(EASY_Calc(current->right));
        case SIN   : return sin(EASY_Calc(current->right));
        case COS   : return cos(EASY_Calc(current->right));
        case TG    :
            {
                double a = EASY_Calc(current->right);
                return sin(a)/cos(a);
            }
        case CTG   :
            {
                double a = EASY_Calc(current->right);
                return cos(a)/sin(a);
            }
        default: printf("NAPISHI FUN"); return -1;
    }
}
