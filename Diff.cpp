#include"Diff.hpp"

Tree* Create(Type type, const char* value, Tree* left, Tree* right)
{
    Tree *ret = new Tree;

    ret->left  = left;
    ret->right = right;
    ret->type  = type;
    strcpy(ret->value,value);
    return ret;
}


Tree* copy(Tree* current)
{
    if(current)
    {
        char value[MAX_LEN_VALUE];
        strcpy(value, current->value);
        Tree* ret = Create(current->type, value, copy(current->left), copy(current->right));
        return ret;
    }
    else
    {
        return NULL;
    }
}


void destroy(Tree* current)
{
    assert(current!=NULL);

    if(current->left)
        destroy(current->left);

    if(current->right)
        destroy(current->right);

    delete current;
}


Tree* Diff_NUMBER(Tree* tree)
{
    return Create(NUMBER, "0", NULL, NULL);
}


Tree* Diff_VAR(Tree* tree)
{
    return Create(NUMBER, "1", NULL, NULL);
}


Tree* Diff_MINUS(Tree* tree)  //left - right
{
    return Create(OPERATOR, "-", Diff(tree->left), Diff(tree->right));
}


Tree* Diff_PLUS(Tree* tree)
{
    return Create(OPERATOR, "+", Diff(tree->left), Diff(tree->right));
}


Tree* Diff_MUL(Tree* tree)
{
    Tree *left = Create(OPERATOR, "*", Diff(copy(tree->left)), copy(tree->right)),
         *right= Create(OPERATOR, "*", copy(tree->left), Diff(copy(tree->right)));

    return Create(OPERATOR, "+", left, right);
}


/*Tree* Diff_POW(Tree* tree) //слева - основание степениб справа - показатель
{
    Tree *left = Create(OPERATOR, "*", Diff(copy(tree->left)), copy(tree->right)),
         *right= Create(OPERATOR, "*", copy(tree->left), Diff(copy(tree->right)));

    return Create(OPERATOR, "+", left, right);
}*/


Tree* Diff_DIV(Tree* tree) //(f/g)'  <=> (left/right)'
{
    Tree *f  = copy(tree->left),
         *g  = copy(tree->right),
         *df = Diff(f),
         *dg = Diff(g);

    Tree *num = Create(OPERATOR, "-", Create(OPERATOR, "*", df, g), Create(OPERATOR, "*", f, dg)),
         *den = Create(OPERATOR, "*", copy(g), copy(g));

    return Create(OPERATOR, "/", num, den);
}


Tree* Diff_LN(Tree* tree)
{
    return Create(OPERATOR, "/", Diff(tree->right), copy(tree->right));
}


Tree* Diff_SIN(Tree* tree)
{
    return Create(OPERATOR, "*", Create(OPERATOR, "cos", NULL, copy(tree->right)), Diff(tree->right));
}


Tree* Diff_COS(Tree* tree)
{
    Tree* left = Create(OPERATOR, "*", Create(NUMBER, "-1", NULL, NULL), Create(OPERATOR, "cos", NULL, copy(tree->right)));
    return Create(OPERATOR, "*", left, Diff(tree->right));
}


Tree* Diff(Tree* tree)
{
    assert(tree!=NULL);

    switch(tree->type)
    {
        case NUMBER: return Diff_NUMBER(tree);
        case VAR:    return Diff_VAR(tree);

        case OPERATOR:
            if(!strcmp("-",tree->value))   return Diff_MINUS(tree);
            if(!strcmp("+",tree->value))   return Diff_PLUS(tree);
            if(!strcmp("*",tree->value))   return Diff_MUL(tree);
            if(!strcmp("/",tree->value))   return Diff_DIV(tree);
            if(!strcmp("ln",tree->value))  return Diff_LN(tree);
            if(!strcmp("sin",tree->value)) return Diff_SIN(tree);
            if(!strcmp("cos",tree->value)) return Diff_COS(tree);
        default: printf("Не могу дифференцироать. Функция не описана\n");
    }
}


