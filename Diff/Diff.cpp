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
    assert(tree!=NULL);
    assert(tree->type == NUMBER);

    return _ZERO_;
}


Tree* Diff_VAR(Tree* tree)
{
    assert(tree!=NULL);
    assert(tree->type == VAR);

    if(tree->value[0] == DIFFERENTIATION_VAR)
        return _ONE_;
    else
        return _ZERO_;
}


Tree* Diff_MINUS(Tree* tree)  //left - right
{
    assert(tree!=NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "-"));

    return Create(OPERATOR, "-", Diff(tree->left), Diff(tree->right));
}


Tree* Diff_PLUS(Tree* tree)
{
    assert(tree!=NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "+"));

    return Create(OPERATOR, "+", Diff(tree->left), Diff(tree->right));
}


Tree* Diff_MUL(Tree* tree)
{
    assert(tree!=NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "*"));

    Tree *left = Create(OPERATOR, "*", Diff(copy(tree->left)), copy(tree->right)),
         *right= Create(OPERATOR, "*", copy(tree->left), Diff(copy(tree->right)));

    return Create(OPERATOR, "+", left, right);
}


Tree* Diff_Constant_Power(Tree* tree)  //d(f^power) = (power*f^(power-1))*df
{
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left !=NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "^"));

    double power = atof(tree->right->value) - 1;

    printf("%f\n",power);
    char char_power[100];

    sprintf(char_power, "%f", power);
    char_power[9] = '\0';
    //delete_zeros(char_power);

    Tree *f_pow_power_minus_1           = Create(OPERATOR, "^", copy(tree->left), Create(NUMBER, char_power, NULL, NULL)),
         *power_mul_f_pow_power_minus_1 = Create(OPERATOR, "*", copy(tree->right), f_pow_power_minus_1),
         *df = Diff(tree->left);

    return Create(OPERATOR, "*", power_mul_f_pow_power_minus_1, df);
}


Tree* Diff_Function_Power(Tree* tree) //d(f^g) = (d(e^(ln(f)*g))) = f^g*d(ln(f)*g)
{
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left !=NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "^"));

    Tree *lnF       = Create(OPERATOR, "ln", NULL, tree->left),
         *lnF_mul_G = Create(OPERATOR, "*", lnF, copy(tree->right));

    Tree *D = Diff(lnF_mul_G);

    destroy(lnF_mul_G);

    return Create(OPERATOR, "*", copy(tree), D);
}


Tree* Diff_POW(Tree* tree)
{
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left !=NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "^"));

    //EASY_Calc_Constant_Tree(tree->right);
    //EASY_Calc_Constant_Tree(tree->left);

    if(tree->right->type == NUMBER)
        return Diff_Constant_Power(tree);
    else
        return Diff_Function_Power(tree);
}


Tree* Diff_DIV(Tree* tree) //(f/g)'  <=> (left/right)'
{
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left !=NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "/"));


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
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left ==NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "ln"));

    return Create(OPERATOR, "/", Diff(tree->right), copy(tree->right));
}


Tree* Diff_SIN(Tree* tree)
{
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left ==NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "sin"));

    return Create(OPERATOR, "*", Create(OPERATOR, "cos", NULL, copy(tree->right)), Diff(tree->right));
}


Tree* Diff_COS(Tree* tree)
{
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left ==NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "cos"));

    Tree* left = Create(OPERATOR, "*", _MINUS_ONE_, Create(OPERATOR, "sin", NULL, copy(tree->right)));
    return Create(OPERATOR, "*", left, Diff(tree->right));
}


Tree* Diff_EXP(Tree* tree)
{
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left ==NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "exp"));

    return Create(OPERATOR, "*", copy(tree), Diff(tree->right));
}


Tree* Diff_TG(Tree* tree)
{
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left ==NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "tg"));

    Tree *COS = Create(OPERATOR, "cos", NULL, copy(tree->right));

    return Create(OPERATOR, "/", _ONE_, Create(OPERATOR, "^", COS, _TWO_));
}


Tree* Diff_CTG(Tree* tree)
{
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left ==NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "ctg"));

    Tree *SIN = Create(OPERATOR, "sin", NULL, copy(tree->right));

    return Create(OPERATOR, "/", _MINUS_ONE_, Create(OPERATOR, "^", SIN, _TWO_));
}


Tree* Diff_ARCCOS (Tree* tree)
{
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left ==NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "arccos"));

    Tree *df   = Diff(tree->right),
         *f_pow_two = Create(OPERATOR, "^", copy(tree->right), _TWO_),
         *one_minus_f_pow_two = Create(OPERATOR, "-", _ONE_, f_pow_two),
         *darccos   = Create(OPERATOR, "/", _MINUS_ONE_, Create(OPERATOR, "^", one_minus_f_pow_two, _HALF_));

    return Create(OPERATOR, "*", df, darccos);
}


Tree* Diff_ARCSIN (Tree* tree)
{
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left ==NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "arcsin"));

    Tree *df   = Diff(tree->right),
         *f_pow_two = Create(OPERATOR, "^", copy(tree->right), _TWO_),
         *one_minus_f_pow_two = Create(OPERATOR, "-", _ONE_, f_pow_two),
         *darcsin   = Create(OPERATOR, "/", _ONE_, Create(OPERATOR, "^", one_minus_f_pow_two, _HALF_));

    return Create(OPERATOR, "*", df, darcsin);

}


Tree* Diff_ARCTG (Tree* tree)
{
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left ==NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "arctg"));

    Tree *f_pow_two = Create(OPERATOR, "^", copy(tree->right), _TWO_),
         *one_plus_f_pow_two = Create(OPERATOR, "+", _ONE_, f_pow_two),
         *df   = Diff(tree->right);

    return Create(OPERATOR, "/", df, one_plus_f_pow_two);
}


Tree* Diff_ARCCTG (Tree* tree)
{
    assert(tree!=NULL);
    assert(tree->right!=NULL);
    assert(tree->left ==NULL);
    assert(tree->type == OPERATOR);
    assert(!strcmp(tree->value, "arcctg"));

    Tree *f_pow_two = Create(OPERATOR, "^", copy(tree->right), _TWO_),
         *one_plus_f_pow_two = Create(OPERATOR, "+", _ONE_, f_pow_two),
         *df   = Diff(tree->right);

    return Create(OPERATOR, "*", df, Create(OPERATOR, "/", _MINUS_ONE_, one_plus_f_pow_two));
}


void Set_DIFFERENTIATION_VAR(const char var)
{
    DIFFERENTIATION_VAR = var;
}


Tree* Differentiate(Tree* tree, const char var)
{
    Set_DIFFERENTIATION_VAR(var);

    return Diff(tree);
}


Tree* Diff(Tree* tree)
{
    assert(tree!=NULL);

    switch(tree->type)
    {
        case NUMBER: return Diff_NUMBER(tree);
        case VAR:    return Diff_VAR(tree);

        case OPERATOR:
            if(!strcmp("-"  ,tree->value)) return Diff_MINUS(tree);
            if(!strcmp("+"  ,tree->value)) return Diff_PLUS (tree);
            if(!strcmp("*"  ,tree->value)) return Diff_MUL  (tree);
            if(!strcmp("/"  ,tree->value)) return Diff_DIV  (tree);

            if(!strcmp("exp",tree->value)) return Diff_EXP  (tree);
            if(!strcmp("^"  ,tree->value)) return Diff_POW  (tree);
            if(!strcmp("ln" ,tree->value)) return Diff_LN   (tree);

            if(!strcmp("sin",tree->value)) return Diff_SIN  (tree);
            if(!strcmp("cos",tree->value)) return Diff_COS  (tree);
            if(!strcmp("tg" ,tree->value)) return Diff_TG   (tree);
            if(!strcmp("ctg",tree->value)) return Diff_CTG  (tree);

            if(!strcmp("arccos",tree->value)) return Diff_ARCCOS(tree);
            if(!strcmp("arcsin",tree->value)) return Diff_ARCSIN(tree);
            if(!strcmp("arcctg",tree->value)) return Diff_ARCCTG(tree);
            if(!strcmp("arctg" ,tree->value)) return Diff_ARCTG (tree);
        default: printf("Не могу дифференцироать. Функция %s не описана\n", tree->value); return NULL;
    }
}


