#include <stdio.h>
#include "AvlTree/AvlTree.h"
#include "Queue/Queue.h"

void LevelOrderTreeWalk(Tree tree, const char* format)
{
    AlignPrint(GetConsoleWidth(), '-', "Level Order Traversal");
    Queue queue = InitQueue(NULL);
    InsertLast(tree, queue);
    TPosition Tmp = NULL;
    while (!IsQueueEmpty(queue))
    {
        Tmp = (TPosition)(RemoveFirst(queue));
        printf(format, Tmp->Element);
        if (Tmp->Left != NULL)
            InsertLast(Tmp->Left, queue);
        if (Tmp->Right != NULL)
            InsertLast(Tmp->Right, queue);
    }
    printf("\n");
    DeleteQueue(queue);
    AlignPrint(GetConsoleWidth(), '-', "End");
}

int main()
{
    const char* InOrder = "ABCDEFGHIJKLM";
    const char* PreOrder = "JDBACFEHGIKLM";
    // Tree tree = InPreBuild(InOrder, PreOrder);
    AvlTree tree = MakeEmpty(NULL);
    int a;
    for (int i = 'A'; i <= 'Z'; i++)
    {
        tree = AvlInsert(i, tree);
    }
    endl();
    TreePlot(tree, "<%c>", 3);
    endl();
    LevelOrderTreeWalk(tree, " %c ");
    endl();
    return 0;
}