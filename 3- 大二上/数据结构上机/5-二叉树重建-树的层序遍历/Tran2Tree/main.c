#include <stdio.h>
#include "Tree/Tree.h"
#include "utils.h"

int main()
{
    // const char* InOrder = "GCBDAFHE";
    // const char* PreOrder = "ABCGDEFH";
    // const char* PostOrder = "GCDBHFEA";
    // const char* LevelOrder = "ABECDFGH";
    const char* InOrder = "ABCDEFGHIJKLM";
    const char* PreOrder = "JDBACFEHGIKLM";
    const char* PostOrder = "ACBEGIHFDMLKJ";
    const char* LevelOrder = "JDKBFLACEHMGI";
    Tree tree;
    // 1. In + Pre
    MakeEmpty(tree);
    printf("\n1. Rebuild from In-Order and Pre-Order:\n");
    tree = InPreBuild(InOrder, PreOrder);
    TreePlot(tree, "<%c>", 3);

    // // 2. In + Post
    // MakeEmpty(tree);
    // printf("\n2. Rebuild from In-Order and Post-Order:\n");
    // tree = InPostBuild(InOrder, PostOrder);
    // TreePlot(tree, "<%c>", 3);
    // // 3. In + Level
    // MakeEmpty(tree);
    // printf("\n3. Rebuild from In-Order and Level-Order:\n");
    // tree = InLevelBuild(InOrder, LevelOrder);
    // TreePlot(tree, "<%c>", 3);
    return 0;
}