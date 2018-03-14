#include"Diff.hpp"

Tree* Create(Type type, int value, Tree* left, Tree* right)
{
    Tree *ret = new Tree;

    ret->left  = left;
    ret->right = right;
    ret->type  = type;
    ret->value = value;
    return ret;
}


bool do_I_put_brackets(Tree* tree)
{
    if(tree->type==NUMBER) return false;
    if(tree->type==VAR)    return false;
    return true;
}

void print(Tree* current,FILE* file)
{
    bool put_brackets_left  = true,
         put_brackets_right = true;

    if(current->left!=NULL)
    {
        put_brackets_left  = do_I_put_brackets(current->left);

        if(put_brackets_left)
            fprintf(file, "(");

        print(current->left, file);

        if(put_brackets_left)
            fprintf(file, ")");
    }

    switch(current->type)
    {
        case NUMBER: fprintf(file,"%lg", current->value); break;
        case VAR   : fprintf(file,"x");         break;
        case DIV   : fprintf(file,"/");         break;
        case MUL   : fprintf(file,"*");         break;
        case PLUS  : fprintf(file,"+");         break;
        case MINUS : fprintf(file,"-");         break;
    }

    if(current->right!=NULL)
    {
        put_brackets_right  = do_I_put_brackets(current->right);

        if(put_brackets_right)
            fprintf(file,"(");

        print(current->right, file);

        if(put_brackets_right)
            fprintf(file,")");
    }
}


Tree* copy(Tree* current)
{
    if(current)
    {
        Tree* ret = Create(current->type, current->value, copy(current->left), copy(current->right));
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
    return Create(NUMBER, 0, NULL, NULL);
}


Tree* Diff_VAR(Tree* tree)
{
    return Create(NUMBER, 1, NULL, NULL);
}


Tree* Diff_MINUS(Tree* tree)  //left - right
{
    return Create(MINUS, 0, Diff(tree->left), Diff(tree->right));
}


Tree* Diff_PLUS(Tree* tree)
{
    return Create(PLUS, 0, Diff(tree->left), Diff(tree->right));
}


Tree* Diff_MUL(Tree* tree)
{
    Tree *left = Create(MUL, 0, Diff(copy(tree->left)), copy(tree->right)),
         *right= Create(MUL, 0, copy(tree->left), Diff(copy(tree->right)));

    return Create(PLUS, 0, left, right);
}


Tree* Diff_POW(Tree* tree) //слева - основание степениб справа - показатель
{
    Tree *left = Create(MUL, 0, Diff(copy(tree->left)), copy(tree->right)),
         *right= Create(MUL, 0, copy(tree->left), Diff(copy(tree->right)));

    return Create(PLUS, 0, left, right);
}

Tree* Diff_DIV(Tree* tree) //(f/g)'  <=> (left/right)'
{
    Tree *f  = copy(tree->left),
         *g  = copy(tree->right),
         *df = Diff(f),
         *dg = Diff(g);

    Tree *num = Create(MINUS, 0, Create(MUL, 0, df, g), Create(MUL, 0, f, dg)),
         *den = Create(MUL, 0, copy(g), copy(g));

    return Create(DIV, 0, num, den);
}


Tree* Diff(Tree* tree)
{
    assert(tree!=NULL);

    switch(tree->type)
    {
        case NUMBER: return Diff_NUMBER(tree);
        case VAR:    return Diff_VAR(tree);
        case MINUS:  return Diff_MINUS(tree);
        case PLUS:   return Diff_PLUS(tree);
        case MUL:    return Diff_MUL(tree);
        case DIV:    return Diff_DIV(tree);
        default: printf("Не могу дифференцироать. Функция не описана\n");
    }
}

