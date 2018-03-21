#include"print_tree.hpp"

static bool do_I_put_brackets(Tree* tree)
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

    fprintf(file,"%s", current->value);

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


static void _print_DOT(Tree* tree, FILE* out)
{
    assert(tree!=NULL);

    if(tree)
    {
        fprintf(out, "%d [shape = box, style = rounded, color = blue, label = \"%s\"]\n",(int)tree, tree->value);

        if(tree->left)
        {
            fprintf(out, "%d -> %d [color = blue]\n", (int)tree, (int)tree->left);
            _print_DOT(tree->left,out);
        }

        if(tree->right)
        {
            fprintf(out, "%d -> %d [color = blue]\n", (int)tree, (int)tree->right);
            _print_DOT(tree->right,out);
        }
    }
}


void print_DOT(Tree* tree)
{
    FILE* out = fopen("print_DOT", "w");

    assert(out!=NULL);
    fprintf(out, "digraph G{\n");

    _print_DOT(tree, out);

    fprintf(out, "\n}");
    fclose(out);

    system("xdot print_DOT");
}


void Print_HEAD(FILE* TEX)
{
    fprintf(TEX, "\\documentclass[a4paper,12pt]{article}\n");
}


void Begin_Document(FILE* TEX)
{
    fprintf(TEX, "\\begin{document}\n");
}


void End_Document(FILE* TEX)
{
    fprintf(TEX, "\\end{document}\n");
}


void Print_VAR(FILE* TEX, const char* value)
{
    fprintf(TEX, "%s", value);
}


void Print_NUMBER(FILE* TEX, const char* value)
{
    fprintf(TEX, "%s", value);
}


void Print_Bin_Before(FILE* TEX, Tree* tree, const char* operat)
{
    fprintf    (TEX , " ( \\%s{", operat);
    Print_Tree (TEX , tree->left);
    fprintf    (TEX , "}");

    fprintf    (TEX , "{");
    Print_Tree (TEX , tree->right);
    fprintf    (TEX , "}) \n");
}


void Print_Bin_Beetwen(FILE* TEX, Tree* tree, const char* operat)
{
    fprintf    (TEX , "(");
    Print_Tree (TEX , tree->left);
    fprintf    (TEX , "%s", operat);
    Print_Tree (TEX , tree->right);
    fprintf    (TEX , ")\n");
}


void Print_Unar(FILE* TEX, Tree* right, const char* operat)
{
    fprintf    (TEX , "\\%s(", operat);
    Print_Tree (TEX , right);
    fprintf    (TEX , ")\n");
}


void Print_OPERATOR(FILE* TEX, Tree* tree)
{
    if     (!strcmp("/", tree->value))   Print_Bin_Before (TEX, tree, "\\frac");
    else if(!strcmp("*", tree->value))   Print_Bin_Beetwen(TEX, tree, "\\cdot");
    else if(!strcmp("+", tree->value))   Print_Bin_Beetwen(TEX, tree, "+");
    else if(!strcmp("-", tree->value))   Print_Bin_Beetwen(TEX, tree, "-");
    else if(!strcmp("cos", tree->value)) Print_Unar(TEX, tree->right, "cos");
    else if(!strcmp("sin", tree->value)) Print_Unar(TEX, tree->right, "sin");
    else if(!strcmp("ln", tree->value))  Print_Unar(TEX, tree->right, "ln");
}


void Print_Tree(FILE* TEX,Tree* tree)
{
    assert(tree!=NULL);

    switch(tree->type)
    {
        case VAR:    Print_VAR(TEX, tree->value);    break;
        case NUMBER: Print_NUMBER(TEX, tree->value); break;

        case OPERATOR: Print_OPERATOR(TEX, tree);    break;
    }
}


void Compil_TEX(const char* file_adress)
{
    char buf[100];

    sprintf(buf, "latex %s", file_adress);
    system(buf);
}


void print_TEX(Tree* tree, const char* file_adress)
{
    FILE* TEX = fopen(file_adress, "w");
    assert(TEX!=NULL);

    Print_HEAD(TEX);
    Begin_Document(TEX);

    fprintf(TEX,"$");
    Print_Tree(TEX, tree);
    fprintf(TEX,"$");

    End_Document(TEX);
    fclose(TEX);

    Compil_TEX(file_adress);
    //Open_TEX();
}
