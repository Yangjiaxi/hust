#include <stdio.h>
#include "List_IDX.h"

// Josephus problem : J(N, M)

#define N 41
#define M 3

void Josephus_1(List list, int size, int death)
{
    printf("---------------------\n");
    printf("Algorithm 1:\n");
    Position tmp;
    int counter = 0;
    int left = size;
    tmp = First(list);
    while (left > 1)
    {
        if (counter % death == death - 1)
        {
            Position del = tmp;
            tmp = RollAdv(tmp, list);
            Delete(Retrieve(del), list);
            --left;
            counter = 0;
        }
        else
        {
            counter++;
            tmp = RollAdv(tmp, list);
        }
    }
    printf("Left : %d\n", Retrieve(tmp));
}

int j2_rec(int n, int m)
{
    if (n == 1)
    {
        return 0;
    }
    else
    {
        return (j2_rec(n - 1, m) + m) % n;
    }
}

void Josephus_2(int size, int death)
{
    printf("---------------------\n");
    printf("Algorithm 2:\n");
    printf("Left : %d\n", j2_rec(size, death) + 1);
}

void Josephus_3(int size, int death)
{
    printf("---------------------\n");
    printf("Algorithm 3:\n");
    int f[size + 1];
    f[0] = f[1] = 0;
    for (int i = 2; i <= size; i++)
    {
        f[i] = (f[i - 1] + death) % i;
    }
    printf("Left : %d\n", f[size] + 1);
}

int main()
{
    InitListIDX();
    Position tmp;
    List list = NewList();
    tmp = list;
    for (int i = 1; i <= N; i++)
    {
        tmp = Insert(i, list, tmp);
    }
    Josephus_1(list, N, M);
    Josephus_2(N, M);
    Josephus_3(N, M);
    return 0;
}