#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

int* BucketSort(int* a, int size);
int* ArrRandInit(int size, int left, int right);
void PrintArray(int* Arr, int size);
int* MakeEmptyArray(int size);

int* BucketSort(int* A, int size)
{
    int* B = MakeEmptyArray(size);
    int max = -1;

    for (int i = 0; i < size; i++)
        max = max(max, A[i]);

    int C[max + 1];

    for (int i = 0; i <= max; i++)
        C[i] = 0;

    for (int i = 0; i < size; i++)
        C[A[i]]++;

    for (int i = 1; i <= max; i++)
        C[i] += C[i - 1];

    for (int j = 0; j < size; j++)
    {
        B[C[A[j]] - 1] = A[j];
        C[A[j]]--;
    }

    return B;
}

int* ArrRandInit(int size, int left, int right)
{
    srand(time(NULL));
    int* a = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % (right - left + 1) + left;
    }
    return a;
}

int* MakeEmptyArray(int size)
{
    int* a = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        a[i] = 0;
    }
    return a;
}

void PrintArray(int* Arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", Arr[i]);
    }
    printf("\n");
}

int main()
{
    int n = 10;
    int* a = ArrRandInit(n, 1, 100);  // 源数据
    PrintArray(a, n);
    int* b = BucketSort(a, n);
    PrintArray(b, n);
    return 0;
}
