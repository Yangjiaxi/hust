#include "snake.h"
#include <stdio.h>
#include <time.h>

void TCharToChar(const TCHAR *tchar, char *_char)
{
	int iLength;
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}

void CharToTchar(const char *_char, TCHAR *tchar)
{
	int iLength;
	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

int cmp(const void *a, const void *b)
{
	rankNode *aa = (rankNode *)a;
	rankNode *bb = (rankNode *)b;
	return ((aa->score) < (bb->score) ? 1 : -1);
}


int randNext(int left, int right)
{
	seed++;
	//srand(seed * seed + (time_t)time(NULL));
	srand(clock() + seed * seed);
	return rand() % (right - left + 1) + left;
}