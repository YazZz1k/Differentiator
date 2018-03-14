#include"Diff.hpp"
#include"Optim.hpp"

int main()
{
    /*Tree* tree_9 = Create(VAR, 0, NULL, NULL);
    Tree* tree_8 = Create(NUMBER, 1, NULL, NULL);
    Tree* tree_7 = Create(PLUS, 0, tree_8, tree_9);
    Tree* tree_6 = Create(VAR, 0, NULL, NULL);
    Tree* tree_5 = Create(MUL, 0, tree_6, tree_7);
    Tree* tree_4 = Create(NUMBER, 4, NULL, NULL);
    Tree* tree_3 = Create(MUL, 0, tree_4, tree_5);
    Tree* tree_2 = Create(VAR, 0, NULL, NULL);
    Tree* tree_1 = Create(PLUS, 0, tree_3, tree_2);

    Tree* Dtree = Diff(tree_1);

    EASY(Dtree);
    EASY(Dtree);
    EASY(Dtree);
*/
    FILE* f = fopen("out.txt", "a");
    /*print(Dtree,f);
    fprintf(f,"\n");
    fclose(f);

    destroy(Dtree);*/


    Tree* tree_6 = Create(NUMBER, 3, NULL, NULL);
    Tree* tree_5 = Create(VAR, 4, NULL, NULL);
    Tree* tree_4 = Create(VAR, 4, NULL, NULL);
    Tree* tree_3 = Create(NUMBER, 3, NULL, NULL);
    Tree* tree_2 = Create(DIV, 0, tree_5, tree_6);
    Tree* tree_1 = Create(MUL, 0, tree_3, tree_4);
    Tree* tree_0 = Create(PLUS, 0, tree_2, tree_1);
    //print(tree_0, f);
    //fprintf(f,"\n");
    EASY_Calc_Constant_Tree(tree_0);
    print(tree_0,f);
    fprintf(f,"\n");
    //destroy(tree_0);
    return 0;
}
