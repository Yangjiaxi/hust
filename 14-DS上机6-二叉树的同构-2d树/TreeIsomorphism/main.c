#include <stdio.h>
#include "Tree/Tree.h"
#include "Utils/Utils.h"

Bool Isomorphic(Tree t1, Tree t2)
{
    if (t1 == NULL && t2 == NULL)
        return True;
    if (t1 != NULL && t2 != NULL && t1->Element == t2->Element)
    {
        if (Isomorphic(t1->Left, t2->Left) && Isomorphic(t1->Right, t2->Right))
        {
            return True;
        }
        if (Isomorphic(t1->Left, t2->Right) && Isomorphic(t1->Right, t2->Left))
        {
            printf("Change at %c\n", t1->Element);
            return True;
        }
        return False;
    }
    // printf("Mismatch at %c & %c\n", t1->Element, t2->Element);
    return False;
}

char* IsTreeIsomorphic(Tree t1, Tree t2)
{
    return Isomorphic(t1, t2) ? "[True] Isomorphic" : "[False] Not Isomorphic";
}

int main()
{
    Tree t1 = InPreBuild("DBFEAHGC", "ABDEFCGH");
    TreePlot(t1, "<%c>", 3);
    // Tree t2 = InPreBuild("GHCAFEBD", "ACGHBEFD");
    Tree t2 = InPreBuild("GHBAFECD", "ABGHCEFD");
    TreePlot(t2, "<%c>", 3);
    printf("%s\n", IsTreeIsomorphic(t1, t2));
    return 0;
}