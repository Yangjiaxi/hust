#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "utils.c"

int cnt = 0;

void hanoi(char from, char by, char to, int n)
{
    if (n == 0)
    {
        return;
    }
    else
    {
        cnt++;
        hanoi(from, to, by, n - 1);
        //printf("%c -> %c\n", from, to);
        hanoi(by, from, to, n - 1);
    }
}

int main(int argc, char **argv)
{
    _TIME_INIT
    int size = atoi(argv[1]);
    char mtd = argv[2][0];
    _TIME_START
    hanoi('A', 'B', 'C', size);
    // printf("Total steps : %d\n", cnt);
    _TIME_END
    return 0;
}