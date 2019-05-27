#include <stdio.h>
#include <time.h>
#include "snake.h"

void snakeInit(int n, snake *mua) 
{
  length = 0;
  int scoreSave = curScore;
  memset(items, 0, sizeof(items));
  memset(itemsShow, 0, sizeof(itemsShow));
  special.x = pointer.x = shield.x = bezoar.x = -1;
  special.y = pointer.y = shield.y = bezoar.y = -1;
  mua->currentDir = RIGHT;
  counter = 0;
  isFinish = 0;
  int i;
  mua->head = mua->tail = (snakeNode *) malloc(sizeof(snakeNode));
  mua->head->y = grids / 2;
  mua->head->x = grids / 2 - (n - 1);
  mua->head->dir = RIGHT;
  srandColor();
  mua->head->c = nextCol();
  for (i = 0; i < n - 1; i++)
  {
    foodInfo.x = mua->head->x + 1;
    foodInfo.y = mua->head->y;
    foodInfo.c = nextCol();
    snakeEat(mua);
  }
  mua->tail->next = mua->head->prev = NULL;
  mua->num = n;
  interval = max;

  if (gameMode == 1 && level > 1)
  {
    curScore = scoreSave;
  }
  else curScore = 0;

  foodInfo.x = foodInfo.y = mine.x = mine.y = -1;
  randomFood(mua);
  randomMine(mua);
  poison = 0;
  for (i = 1; i <= 10; i++)
  {
    poi[i].x = poi[i].y = -1;
  }
  display(mua);
}

void printSnake(snake *mua)
{
  snakeNode *pNode = mua->head;
  while (pNode != NULL)
  {
    printf("%d %d %d\n", pNode->x, pNode->y, pNode->c);
    pNode = pNode->next;
  }
  printf("food : %d %d %d\n", foodInfo.x, foodInfo.y, foodInfo.c);
  printf("\n");
}

void snakeMove(snake *mua)  
{
  snakeNode *pNode = mua->tail;
  while (pNode->prev != NULL) 
  {
    pNode->x = pNode->prev->x;
    pNode->y = pNode->prev->y;
    pNode->dir = pNode->prev->dir;
    pNode = pNode->prev;
  }
  mua->head->dir = mua->currentDir;
  mua->head->x += dx[mua->currentDir];
  mua->head->y += dy[mua->currentDir];
  if (mua->head->x < 0) mua->head->x = grids - 1;
  if (mua->head->y < 0) mua->head->y = grids - 1;
  if (mua->head->x > grids - 1) mua->head->x = 0;
  if (mua->head->y > grids - 1) mua->head->y = 0;
}

void snakeEat(snake *mua)
{
  snakeNode *node = (snakeNode *) malloc(sizeof(snakeNode));
  node->x = foodInfo.x;
  node->y = foodInfo.y;
  node->dir = mua->currentDir;
  node->c = foodInfo.c;
  mua->head->prev = node;
  node->next = mua->head;
  node->prev = NULL;
  mua->head = node;
  mua->num++;
  interval = (max - (mua->num - 4) / decNum * dec);
  interval = interval < min ? min : interval;
  curScore += (int) (((max - interval) / dec + 1) * 1.0 * (double) (50 / grids));
}

void snakeCut(snake *mua)
{
  snakeNode *p = mua->tail->prev;
  free(mua->tail);
  mua->tail = p;
  mua->tail->next = NULL;
}

void snakeHalf(snake *mua)
{
  if (mua->num <= 2)
  {
    isFinish = 1;
  }
  else
  {
    int goal = mua->num / 2;
    mua->num -= goal;
    for (int i = 1; i <= goal; i++)
    {
      snakeCut(mua);
    }
    interval = (max - (mua->num - 4) / decNum * dec);
    interval = interval < min ? min : interval;
  }
}

void freeAll(snake *mua)
{
  snakeNode *pNode = mua->tail->prev;
  while (pNode != NULL)
  {
    free(pNode->next);
    pNode = pNode->prev;
  }
  free(mua->head);
}