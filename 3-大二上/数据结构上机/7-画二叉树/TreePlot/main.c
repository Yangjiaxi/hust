#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AvlTree/AvlTree.h"
// #include "BST/BST.h"
#include "TreePlot.h"

int main()
{
    // SearchTree tree = MakeEmpty(NULL);
    AvlTree tree = MakeEmpty(NULL);
    for (int i = 'A'; i <= 'Z'; i++)
    {
        tree = Insert(i, tree);
    }
    TreePlot(tree);
    MakeEmpty(tree);
    return 0;
}