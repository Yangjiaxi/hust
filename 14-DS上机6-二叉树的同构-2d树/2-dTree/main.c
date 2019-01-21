#include <stdio.h>
#include <stdlib.h>
#include "2-dTree/Tree.h"
#include "Utils/Utils.h"
#include "string.h"

// int cmp(TElementType LHS, TElementType RHS)
// {
//     // printf("LHS : %s, RHS : %s -> %d\n", LHS, RHS, strcmp(LHS, RHS));
//     return strcmp(LHS, RHS);
// }

int cmp(TElementType LHS, TElementType RHS)
{
    return LHS - RHS;
}

void TreePreWalk(KDTree T)
{
    printf("<%03d, %03d>\n", T->Data[0], T->Data[1]);
    if (T->Left != NULL)
        TreePreWalk(T->Left);
    if (T->Right != NULL)
        TreePreWalk(T->Right);
}

int main()
{
    KDTree T = MakeEmpty(NULL);
    char* FirstName[] = {"Harry",  "Dwight", "John",   "Lyndon", "Richard",
                         "Gerald", "Jimmy",  "Ronald", "George", "Bill"};

    char* SecondName[] = {"Truman", "Eisenhower", "Kennedy", "Johnson",
                          "Nixon",  "Ford",       "Carter",  "Reagan",
                          "Bush",   "Clinton"};

    for (int i = 0; i < 10; i++)
    {
        // T = TreeInsert(CreateData(FirstName[i], SecondName[i]), T, cmp);
        T = TreeInsert(
            CreateData(GetRandomNumber(0, 100), GetRandomNumber(0, 100)), T,
            cmp);
    }

    // TreePreWalk(T);
    TreePlot(T, "<%03d,%03d>", 9);

    // FindAndPrint(CreateData("A", "A"), CreateData("Z", "Z"), T, cmp);
    FindAndPrint(CreateData(0, 30), CreateData(50, 70), T, cmp);

    return 0;
}