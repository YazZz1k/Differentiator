#include"Diff.hpp"
#include"Optim.hpp"
#include"print_tree.hpp"

int main()
{

    /*Tree* tree_6 = Create(NUMBER, "3", NULL, NULL);
    Tree* tree_5 = Create(VAR, "x", NULL, NULL);
    Tree* tree_4 = Create(VAR, "x", NULL, NULL);
    Tree* tree_3 = Create(NUMBER, "3", NULL, NULL);
    Tree* tree_2 = Create(OPERATOR, "/", tree_5, tree_6);
    Tree* tree_1 = Create(OPERATOR, "*", tree_3, tree_4);
    Tree* tree_0 = Create(OPERATOR, "+", tree_2, tree_1);

    Tree* D=Diff(tree_0);
    EASY(D);
    EASY_Calc_Constant_Tree(D);
    */
    //Tree *D= Diff(tree_0);


    Tree* tree_3 = Create(NUMBER, "2", NULL, NULL);
    Tree* tree_2 = Create(VAR, "x", NULL, NULL);
    Tree* tree_1 = Create(OPERATOR, "*", tree_2, tree_3);
    Tree* tree_0 = Create(OPERATOR, "sin", NULL, tree_1);
    Tree* D = Diff(tree_0);
    EASY(D);
    EASY(D);
    //EASY_Calc_Constant_Tree(D);
    return 0;
}
