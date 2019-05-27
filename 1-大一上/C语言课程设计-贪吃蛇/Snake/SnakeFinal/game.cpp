#include <graphics.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include "snake.h"


void start()
{
	initBoard();
	getRank();
	showRank();
	initPanel();
	initRes();
	getCommand();
	closegraph();
}

void printRank()
{
	for (int i = 1; i <= record.total; i++)
	{
		printf("No.%d %s %d\n", i, record.list[i].name, record.list[i].score);
	}
}

bool canPlace(int x, int y, snake *mua)
{
	snakeNode *pNode = mua->head;
	while (pNode != NULL)
	{
		if (pNode->x == x && pNode->y == y)
		{
			return false;
		}
		else
		{
			pNode = pNode->next;
		}
	}
	if ((x == mine.x && y == mine.y) || (x == foodInfo.x && y == foodInfo.y))
	{
		return false;
	}
	int i;
	for (i = 1; i <= 10; i++)
	{
		if (x == poi[i].x && y == poi[i].y)
		{
			return false;
		}
	}
	if (x == pointer.x && y == pointer.y)
	{
		return false;
	}
	if (x == shield.x && y == shield.y)
	{
		return false;
	}
	if (x == bezoar.x && y == bezoar.y)
	{
		return false;
	}
	if (x == special.x && y == special.y)
	{
		return false;
	}
	return true;
}

void randomFood(snake *mua)
{
	int cx;
	int cy;
	COLORREF c;
	do
	{
		cx = randNext(0, grids - 1);
		cy = randNext(0, grids - 1);
		c = nextCol();
	} while (!canPlace(cx, cy, mua));
	foodInfo.x = cx;
	foodInfo.y = cy;
	foodInfo.c = c;
}

void randomMine(snake *mua)
{
	int cx;
	int cy;
	do
	{
		cx = randNext(0, grids - 1);
		cy = randNext(0, grids - 1);
	} while (!canPlace(cx, cy, mua));
	mine.x = cx;
	mine.y = cy;
	mine.c = RED;
}

void randomPoi(snake *mua)
{
	int i;
	for (i = 1; i <= 10; i++)
	{
		int cx = -1;
		int cy = -1;
		do
		{
			cx = randNext(0, grids - 1);
			cy = randNext(0, grids - 1);
		} while (!canPlace(cx, cy, mua));
		poi[i].x = cx;
		poi[i].y = cy;
		poi[i].c = GREEN;
	}
}

void randomItem(int type, snake *mua)
{
	int cx;
	int cy;
	do
	{
		cx = randNext(0, grids - 1);
		cy = randNext(0, grids - 1);
	} while (!canPlace(cx, cy, mua));

	switch (type)
	{
		case POINTER:
		{
			pointer.x = cx;
			pointer.y = cy;
			break;
		}
		case SHIELD:
		{
			shield.x = cx;
			shield.y = cy;
			break;
		}
		case BEZOAR:
		{
			bezoar.x = cx;
			bezoar.y = cy;
		}
	}
}

void randomSpecial(snake *mua)
{
	int cx;
	int cy;
	do
	{
		cx = randNext(0, grids - 1);
		cy = randNext(0, grids - 1);
	} while (!canPlace(cx, cy, mua));
	special.x = cx;
	special.y = cy;
	itemsShow[level] = 1;
}

bool hasFood(snake *mua)
{
	snakeNode *pNode = mua->head;
	int x = pNode->x + dx[mua->currentDir];
	int y = pNode->y + dy[mua->currentDir];

	if (x < 0) x = grids - 1;
	if (y < 0) y = grids - 1;
	if (x > grids - 1) x = 0;
	if (y > grids - 1) y = 0;

	if (x == foodInfo.x && y == foodInfo.y)
	{
		return 1;
	}
	return 0;
}

bool hasMine(snake *mua)
{
	snakeNode *pNode = mua->head;
	int x = pNode->x + dx[mua->currentDir];
	int y = pNode->y + dy[mua->currentDir];

	if (x < 0) x = grids - 1;
	if (y < 0) y = grids - 1;
	if (x > grids - 1) x = 0;
	if (y > grids - 1) y = 0;

	if (x == mine.x && y == mine.y)
	{
		return 1;
	}
	return 0;
}

bool hasPoison(snake *mua)
{
	snakeNode *pNode = mua->head;
	int x = pNode->x + dx[mua->currentDir];
	int y = pNode->y + dy[mua->currentDir];

	if (x < 0) x = grids - 1;
	if (y < 0) y = grids - 1;
	if (x > grids - 1) x = 0;
	if (y > grids - 1) y = 0;

	int i;
	for (i = 1; i <= 10; i++)
	{
		if (x == poi[i].x && y == poi[i].y)
		{
			return 1;
		}
	}
	return 0;
}

bool hasItem(snake *mua)
{
	if (counter < 50)
	{
		return false;
	}
	else
	{
		snakeNode *pNode = mua->head;
		int x = pNode->x + dx[mua->currentDir];
		int y = pNode->y + dy[mua->currentDir];

		if (x < 0) x = grids - 1;
		if (y < 0) y = grids - 1;
		if (x > grids - 1) x = 0;
		if (y > grids - 1) y = 0;

		if (itemsShow[4])
		{
			//pointer
			if (x == pointer.x && y == pointer.y)
			{
				itemsShow[4] = 0;
				items[4] = 200;
				return true;
			}
		}
		else if (itemsShow[5])
		{
			//shield
			if (x == shield.x && y == shield.y)
			{
				itemsShow[5] = 0;
				items[5] = 10;
				return true;
			}
		}
		else if (itemsShow[6])
		{
			//bezoar
			if (x == bezoar.x && y == bezoar.y)
			{
				itemsShow[6] = 0;
				items[6] = 10;
				return true;
			}
		}
	}
	return false;
}

bool hasSpecial(snake *mua)
{
	if (!itemsShow[level])
	{
		return false;
	}
	else
	{
		snakeNode *pNode = mua->head;
		int x = pNode->x + dx[mua->currentDir];
		int y = pNode->y + dy[mua->currentDir];

		if (x < 0) x = grids - 1;
		if (y < 0) y = grids - 1;
		if (x > grids - 1) x = 0;
		if (y > grids - 1) y = 0;

		if (x == special.x && y == special.y)
		{
			items[level] = 1;
			itemsShow[level] = 0;
			return true;
		}
		return false;
	}
}

void poisonEat(snake *mua)
{
	if (items[BEZOAR])
	{
		--items[BEZOAR];
		int i;

		snakeNode *pNode = mua->head;
		int x = pNode->x + dx[mua->currentDir];
		int y = pNode->y + dy[mua->currentDir];
		if (x < 0) x = grids - 1;
		if (y < 0) y = grids - 1;
		if (x > grids - 1) x = 0;
		if (y > grids - 1) y = 0;

		for (i = 1; i <= 10; i++)
		{
			if (poi[i].x == x && poi[i].y == y)
			{
				int cx = -1;
				int cy = -1;
				do
				{
					cx = randNext(0, grids - 1);
					cy = randNext(0, grids - 1);
				} while (!canPlace(cx, cy, mua));
				poi[i].x = cx;
				poi[i].y = cy;
				break;
			}
		}
	}
	else if (items[SHIELD])
	{
		--items[SHIELD];
		int i;

		snakeNode *pNode = mua->head;
		int x = pNode->x + dx[mua->currentDir];
		int y = pNode->y + dy[mua->currentDir];
		if (x < 0) x = grids - 1;
		if (y < 0) y = grids - 1;
		if (x > grids - 1) x = 0;
		if (y > grids - 1) y = 0;

		for (i = 1; i <= 10; i++)
		{
			if (poi[i].x == x && poi[i].y == y)
			{
				int cx = -1;
				int cy = -1;
				do
				{
					cx = randNext(0, grids - 1);
					cy = randNext(0, grids - 1);
				} while (!canPlace(cx, cy, mua));
				poi[i].x = cx;
				poi[i].y = cy;
				break;
			}
		}
	}
	else
	{
		if (mua->num <= 2)
		{
			isFinish = 1;
			return;
		}
		else
		{
			snakeCut(mua);
			mua->num -= 1;
			interval = (max - (mua->num - 4) / decNum * dec);
			interval = interval < min ? min : interval;

			int i;

			snakeNode *pNode = mua->head;
			int x = pNode->x + dx[mua->currentDir];
			int y = pNode->y + dy[mua->currentDir];
			if (x < 0) x = grids - 1;
			if (y < 0) y = grids - 1;
			if (x > grids - 1) x = 0;
			if (y > grids - 1) y = 0;

			for (i = 1; i <= 10; i++)
			{
				if (poi[i].x == x && poi[i].y == y)
				{
					int cx = -1;
					int cy = -1;
					do
					{
						cx = randNext(0, grids - 1);
						cy = randNext(0, grids - 1);
					} while (!canPlace(cx, cy, mua));
					poi[i].x = cx;
					poi[i].y = cy;
					break;
				}
			}
		}
	}
}

void mineEat(snake *mua)
{
	if (items[SHIELD])
	{
		if (items[SHIELD] >= 3)
		{
			items[SHIELD] -= 3;
		}
		else items[SHIELD] = 0;
	}
	else
	{
		snakeHalf(mua);
	}
}

bool judgeCurrent(snake *mua)
{
	snakeNode *pNode = mua->head->next;
	int x = mua->head->x + dx[mua->currentDir];
	int y = mua->head->y + dy[mua->currentDir];
	if (x < 0) x = grids - 1;
	if (y < 0) y = grids - 1;
	if (x > grids - 1) x = 0;
	if (y > grids - 1) y = 0;
	while (pNode != mua->tail)
	{
		if (pNode->x == x && pNode->y == y)
		{
			return 1;
		}
		pNode = pNode->next;
	}
	return 0;
}

void saveMap(snake *mua)
{
	//printSnake(mua);
	int i;
	FILE *out;
	fopen_s(&out, "save.txt", "w");
	if (out == NULL)
	{
		printf("FATAL ERROR OCCUR!\n");
		exit(0);
	}
	fprintf(out, "%d %d\n", grids, interval);
	fprintf(out, "%d %d %d\n", mua->num, curScore, mua->currentDir);
	snakeNode *pNode = mua->head;
	while (pNode != NULL)
	{
		fprintf(out, "%d %d %d\n", pNode->x, pNode->y, pNode->dir);
		pNode = pNode->next;
	}
	fprintf(out, "%d %d\n", foodInfo.x, foodInfo.y);
	fprintf(out, "%d %d\n", mine.x, mine.y);
	fprintf(out, "%d %d\n", isPoi, poison);
	if (isPoi)
	{
		for (i = 1; i <= 10; i++)
		{
			fprintf(out, "%d %d\n", poi[i].x, poi[i].y);
		}
	}
	fprintf(out, "%d %d %d %d %d\n", level, gameMode, shouldNext, counter, eventComes);
	for (int i = 1; i <= 6; i++)
	{
		fprintf(out, "%d %d ", items[i], itemsShow[i]);
		if (itemsShow[i])
		{
			if (i <= 3)
			{
				fprintf(out, "%d %d", special.x, special.y);
			}
			else
			{
				switch (i)
				{
					case POINTER:
					{
						fprintf(out, "%d %d", pointer.x, pointer.y);
						break;
					}
					case SHIELD:
					{
						fprintf(out, "%d %d", shield.x, shield.y);
						break;
					}
					case BEZOAR:
					{
						fprintf(out, "%d %d", bezoar.x, bezoar.y);
						break;
					}
				}
			}
		}
		fprintf(out, "\n");
	}
	MessageBox(NULL, _T("保存成功"), _T("蛇爆"), MB_OK | MB_SYSTEMMODAL);
	fclose(out);
}

void upLoadScore(TCHAR name[], snake *mua)
{
	FILE *out;
	fopen_s(&out, "rank.txt", "w");
	char name_s[50];
	TCharToChar(name, name_s);
	strcpy_s(record.list[++record.total].name, name_s);
	record.list[record.total].score = curScore;
	qsort(&record.list[1], record.total + 1, sizeof(rankNode), cmp);
	fprintf(out, "Snake Rank File\n");
	for (int i = 1; i <= (record.total > 8 ? 8 : record.total); i++)
	{
		fprintf(out, "#%02d [%s] %d\n", i, record.list[i].name, record.list[i].score);
	}
	fprintf(out, "@END OF FILE");
	fclose(out);
}

void getRank()
{
	FILE *in;
	fopen_s(&in, "rank.txt", "r");
	record.total = 0;
	if (in == NULL)
	{
		printf("新建rank.txt\n");
		fopen_s(&in, "rank.txt", "w");
		fprintf(in, "Snake Game Rank File!\n");
	}
	else
	{
		char s1[10];
		char s2[50];
		int score;
		int count;
		char name[50];
		while (!feof(in))
		{
			score = 0;
			count = 0;
			memset(s1, '\0', sizeof(s1));
			memset(s2, '\0', sizeof(s2));
			memset(name, '\0', sizeof(name));
			fscanf_s(in, "%s", s1, sizeof(s1));
			if (s1[0] != '#')
			{
				fgets(s2, 50, in);
			}
			else
			{
				char t;
				int len = 0;
				fscanf_s(in, "%c", &t, sizeof(t));
				while (t != ']')
				{
					if (t != '[' && !(len == 0 && t == ' '))
					{
						name[len++] = t;
					}
					fscanf_s(in, "%c", &t, sizeof(t));
				}
				name[len] = '\0';
				fscanf_s(in, "%d", &curScore);
				count = (s1[2] - '0') + (s1[1] - '0') * 10;
				strcpy_s(record.list[++record.total].name, name);
				record.list[record.total].score = curScore;
			}
		}
	}
	fclose(in);
}

void dealAction(snake *mua)
{
	int flag = 0;
	if (hasFood(mua))
	{
		snakeEat(mua);
		flag = 1;
		//printf("=>%d\n", mua->num);
		randomFood(mua);
		updateScore(mua);
		display(mua);
		if (!isPoi)
		{
			poison++;
			if (poison == 7)
			{
				isPoi = 1;
				poison = 0;
				randomPoi(mua);
			}
		}
	}
	else if (hasMine(mua))
	{
		mineEat(mua);
		randomMine(mua);
		display(mua);
		if (!isPoi)
		{
			poison++;
			if (poison == 7)
			{
				isPoi = 1;
				poison = 0;
				randomPoi(mua);
			}
		}
	}
	else if (isPoi && hasPoison(mua))
	{
		poisonEat(mua);
		display(mua);
	}
	else if (hasItem(mua))
	{
		display(mua);
	}
	else if (hasSpecial(mua))
	{
		display(mua);
	}
	if (!flag)
	{
		if (!judgeCurrent(mua))
		{
			snakeMove(mua);
			display(mua);
		}
		else
		{
			isFinish = 1;
			deadStat();
		}
	}
	counter++;
	if (!(counter % 100))
	{
		int newItem = randNext(4, 6);
		//printf("1=>%d %d %d\n", itemsShow[4], itemsShow[5], itemsShow[6]);
		if (!itemsShow[newItem])
		{
			itemsShow[4] = itemsShow[5] = itemsShow[6] = 0;
			itemsShow[newItem] = 1;
			//printf("2=>%d %d %d\n", itemsShow[4], itemsShow[5], itemsShow[6]);
			randomItem(newItem, mua);
		}
		else
		{
			//
		}
	}
	if (counter % 300)
	{
		if ((counter % 300) == 200)
		{
			eventComes = randNext(25, 75);
		}
		if ((counter % 300) > 200)
		{
			if ((counter % 300) == (200 + eventComes))
			{
				randomSpecial(mua);
			}
		}
		else
		{
			//
		}
	}
	else
	{
		itemsShow[level] = 0;
		if (items[level])
		{
			items[level] = 0;
		}
		else if (items[SHIELD])
		{
			items[SHIELD] = 0;
		}
		else
		{
			snakeHalf(mua);
		}
	}
	length = mua->num;
	if (mua->num >= levelGoal && gameMode == 1)
	{
		shouldNext = 1;
	}
	else
	{
		Sleep(interval);
	}
}

void startGame()
{
	snake Emm;
	interval = max;
	snakeInit(4, &Emm);
	updateScore(&Emm);
	loop(&Emm);
	if (gameMode == 1 && shouldNext)
	{
		if (level == 3)
		{
			printf("通关");
			initPanel();
			getCommand();
		}
		else
		{
			level += 1;
			shouldNext = 0;
			printf("进入下一关\n");
			cleanStat();
			showLevel();
			startGame();
		}
	}
	else
	{
		initPanel();
		getCommand();
	}
}

void getCommand()
{
	initMapSaying();
	clearBottom();
	while (!_kbhit());
	char c = _getch();
	switch (c)
	{
		case '1':
		{
			printf("载入存档\n");
			FILE *in;
			fopen_s(&in, "save.txt", "r");
			if (in == NULL)
			{
				MessageBox(NULL, _T("未找到存档!"), _T("蛇爆"), MB_OK | MB_SYSTEMMODAL);
				getCommand();
			}
			else
			{
				fclose(in);
				snake mua = loadGame();
				display(&mua);
				gamePause(&mua);
				loop(&mua);
				if (shouldNext)
				{
					startGame();
				}
				else
				{
					initPanel();
					getCommand();
				}
			}
			break;
		}
		case '2':
		{
			level = 1;
			gameMode = 1;
			shouldNext = 0;
			fullMode();
			break;
		}
		case '3':
		{
			gameMode = 2;
			shouldNext = 0;
			selectMap();
			break;
		}
		case '4':
		{
			exit(0);
		}
		case 27:
		{
			exit(0);
		}
		default:
		{
			getCommand();
			break;
		}
	}
}

snake loadGame()
{
	FILE *in;
	fopen_s(&in, "save.txt", "r");
	isFinish = 0;
	fscanf_s(in, "%d%d", &grids, &interval);
	l_grid = 600 / grids;
	snake Emm;
	fscanf_s(in, "%d%d%d", &Emm.num, &curScore, &Emm.currentDir);
	length = Emm.num;
	Emm.head = Emm.tail = (snakeNode *)malloc(sizeof(snakeNode));
	srandColor();
	fscanf_s(in, "%d%d%d", &Emm.head->x, &Emm.head->y, &Emm.head->dir);
	foodInfo.c = nextCol();
	int sc = colorC;
	Emm.head->c = nextCol();
	snakeNode *node;
	int i;
	for (i = 2; i <= Emm.num; i++)
	{
		node = (snakeNode *)malloc(sizeof(snakeNode));
		fscanf_s(in, "%d%d%d", &node->x, &node->y, &node->dir);
		node->c = nextCol();
		node->prev = Emm.tail;
		Emm.tail->next = node;
		Emm.tail = node;
	}
	Emm.tail->next = Emm.head->prev = NULL;
	colorC = sc;
	fscanf_s(in, "%d%d", &foodInfo.x, &foodInfo.y);
	fscanf_s(in, "%d%d", &mine.x, &mine.y);
	mine.c = RED;
	fscanf_s(in, "%d%d", &isPoi, &poison);
	if (isPoi)
	{
		for (i = 1; i <= 10; i++)
		{
			fscanf_s(in, "%d%d", &poi[i].x, &poi[i].y);
			poi[i].c = GREEN;
		}
	}
	fscanf_s(in, "%d%d%d%d%d", &level, &gameMode, &shouldNext, &counter, &eventComes);
	for (int i = 1; i <= 6; i++)
	{
		fscanf_s(in, "%d%d", &items[i], &itemsShow[i]);
		if (itemsShow[i])
		{
			if (i <= 3)
			{
				fscanf_s(in, "%d%d", &special.x, &special.y);
			}
			else
			{
				switch (i)
				{
					case POINTER:
					{
						fscanf_s(in, "%d%d", &pointer.x, &pointer.y);
						break;
					}
					case SHIELD:
					{
						fscanf_s(in, "%d%d", &shield.x, &shield.y);
						break;
					}
					case BEZOAR:
					{
						fscanf_s(in, "%d%d", &bezoar.x, &bezoar.y);
						break;
					}
				}
			}
		}
	}
	fclose(in);
	return Emm;
}

void loop(snake *mua)
{
	int c;
	while (!isFinish && !shouldNext)
	{
		if (_kbhit())
		{
			c = _getch();
			switch (c)
			{
				case 224:
				{
					c = _getch();
					switch (c)
					{
						case 72:
						{
							if (mua->currentDir != DOWN)
							{
								mua->currentDir = UP;
							}
							break;
						}
						case 75:
						{
							if (mua->currentDir != RIGHT)
							{
								mua->currentDir = LEFT;
							}
							break;
						}
						case 80:
						{
							if (mua->currentDir != UP)
							{
								mua->currentDir = DOWN;
							}
							break;
						}
						case 77:
						{
							if (mua->currentDir != LEFT)
							{
								mua->currentDir = RIGHT;
							}
							break;
						}
						default:
						{
							break;
						}
					}
					break;
				}
				case ' ':
				{
					gamePause(mua);
					break;
				}
				default:
				{
					break;
				}
			}
		}
		dealAction(mua);
	}
	if (!shouldNext || (shouldNext && level == 3) || gameMode == 2)
	{
		if (gameMode == 1 && shouldNext)
		{
			if (level == 3)
			{
				level = 4;
				cleanStat();
				level = 3;
			}
		}
		if (record.total < 8 || curScore >= record.list[8].score)
		{
			TCHAR name[50];
			TCHAR info[200];
			char info_s[200];
			char score_s[10];
			strcpy_s(info_s, "你得到了");
			_itoa_s(curScore, score_s, 10);
			strcat_s(info_s, score_s);
			strcat_s(info_s, "分，壮士请留名");
			CharToTchar(info_s, info);
			InputBox(name, 10, info);
			if (wcslen(name) != 0)
			{
				upLoadScore(name, mua);
			}
			else
			{
				char ss[50] = "不愿意透露姓名的";
				TCHAR st[50];
				CharToTchar(ss, st);
				upLoadScore(st, mua);
			}
			showRank();
		}
		else
		{
			TCHAR info[200];
			char info_s[200];
			char score_s[10];
			strcpy_s(info_s, "你得到了");
			_itoa_s(curScore, score_s, 10);
			strcat_s(info_s, score_s);
			strcat_s(info_s, "分");
			CharToTchar(info_s, info);
			MessageBox(NULL, info, _T("蛇爆"), MB_OK | MB_SYSTEMMODAL);
		}
	}
	freeAll(mua);
}

void fullMode()
{
	//printf("闯关模式\n");
	showLevel();
	startGame();
}

void selectMap()
{
	//printf("自选地图\n");
	SetWorkingImage(&score);
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 32;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);

	outtextxy(5, 13, levelc[1]);
	outtextxy(5, 43, levels[1]);
	outtextxy(5, 83, levelc[2]);
	outtextxy(5, 113, levels[2]);
	outtextxy(5, 153, levelc[3]);
	outtextxy(5, 183, levels[3]);
	f.lfHeight = 40;
	settextstyle(&f);
	outtextxy(20, 250, _T("按下数字"));
	outtextxy(20, 290, _T("键以选择"));
	SetWorkingImage();
	putimage(610, 205, &score);
	char ch;
	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();
			if ('1' <= ch && ch <= '3')
			{
				level = ch - '0';
				//printf("选择了%d关\n", level);
				break;
			}
			else continue;
		}
	}
	showLevel();
	startGame();
}