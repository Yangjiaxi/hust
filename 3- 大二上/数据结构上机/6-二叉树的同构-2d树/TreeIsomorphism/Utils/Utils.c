#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>

void Fatal(const char* info)
{
    fprintf(stderr, "%s\n", info);
    fflush(stderr);
    exit(1);
}

void endl()
{
    printf("\n");
}

char* StrConcat(const char* s1, char* s2)
{
    const size_t len1 = strlen(s1);
    if (!s2)
        s2 = "No Name";
    const size_t len2 = strlen(s2);
    char* result = malloc(len1 + len2 + 1);
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}

void AlignPrint(int width, char pad, const char* text)
{
    // printf("\n");
    int t_len = strlen(text) + 4;
    int l = (width - t_len + 1) / 2;
    for (int i = 1; i <= l; i++)
        printf("%c", pad);
    width -= l;
    printf("[ %s ]", text);
    width -= t_len;
    for (int i = 1; i <= width; i++)
        printf("%c", pad);
    printf("\n");
}

int FindChar(const char* str, char ch)
{
    char* res = strchr(str, ch);
    if (res != NULL)
    {
        return res - str;
    }
    else
    {
        return -1;
    }
}

char* StrCopy(const char* str, int size)
{
    char* res = malloc(sizeof(char) * (size + 1));
    strncpy(res, str, size);
    res[size] = '\0';
    return res;
}

int GetConsoleWidth()
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

int GetRandomNumber(int L, int R)
{
    static unsigned seed = 0;
    seed += 1;
    unsigned r = time(NULL) + seed * seed + 3 * seed;
    srand(r * r);
    return (R - L) * (rand() / (double)(RAND_MAX)) + L;
}