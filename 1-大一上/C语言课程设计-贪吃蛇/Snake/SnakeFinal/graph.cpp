#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include <time.h>
#include <math.h>
#include "snake.h"

#define PI 3.141926

void srandColor()
{
	shift = randNext(80, 120);
	colorBit = randNext(1, 4);
	colorC = randNext(0, 180);
}

COLORREF nextCol()
{
	BYTE r;
	BYTE g;
	BYTE b;
	if (colorBit == 1)
	{
		r = BYTE(255 * fabs(sin((colorC - shift) * PI / 180)));
		g = BYTE(255 * fabs(sin((colorC)* PI / 180)));
		b = BYTE(255);
	}
	if (colorBit == 2)
	{
		r = BYTE(255);
		g = BYTE(255 * fabs(sin((colorC)* PI / 180)));
		b = BYTE(255 * fabs(sin((colorC + shift) * PI / 180)));
	}
	if (colorBit == 3)
	{
		r = BYTE(255 * fabs(sin((colorC - shift) * PI / 180)));
		g = BYTE(255);
		b = BYTE(255 * fabs(sin((colorC + shift) * PI / 180)));
	}
	if (colorBit == 4)
	{
		r = BYTE(255 * fabs(sin((colorC - shift) * PI / 180)));
		g = BYTE(255 * fabs(sin((colorC)* PI / 180)));
		b = BYTE(255 * fabs(sin((colorC + shift) * PI / 180)));
	}
	colorC += 3;
	return RGB(r, g, b);
}

void showRank()
{
	SetWorkingImage(&rank);
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 24;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	TCHAR txt[20] = _T("排行榜");
	outtextxy((200 - textwidth(txt)) / 2, 2, txt);
	line(0, 30, 200, 30);
	_tcscpy_s(f.lfFaceName, _T("宋体"));
	f.lfHeight = 16;
	f.lfWeight = 600;
	settextstyle(&f);
	char tmp[100];
	TCHAR tmp_t[100];
	for (int i = 1; i <= (record.total > 8 ? 8 : record.total); i++)
	{
		_itoa_s(i, tmp, 10);
		strcat_s(tmp, ".");
		strcat_s(tmp, record.list[i].name);
		CharToTchar(tmp, tmp_t);
		settextcolor(nextCol());
		outtextxy(10, i * 20 + 13, tmp_t);
		memset(tmp_t, '\0', sizeof(tmp_t));
		_itow_s(record.list[i].score, tmp_t, 10);
		int width_t = textwidth(tmp_t);
		outtextxy((200 - width_t - 10), i * 20 + 13, tmp_t);
	}
	SetWorkingImage();
	putimage(610, 5, &rank);
}

void initPanel()
{
	SetWorkingImage(&score);
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 36;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(5, 23, _T("1.载入存档"));  
	outtextxy(5, 60 + 23, _T("2.闯关模式"));
	outtextxy(5, 60 * 2 + 23, _T("3.自选地图"));
	outtextxy(5, 60 * 3 + 23, _T("4.退出"));
	outtextxy(5, 60 * 4 + 43, _T("按下数字"));
	outtextxy(5, 60 * 5 + 23, _T("键以选择"));
	SetWorkingImage();
	putimage(610, 205, &score);
}

void initMapSaying()
{
	SetWorkingImage(&map);
	cleardevice();

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 36;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	TCHAR s[20];
	CharToTchar("朋友，玩蛇吗", s);
	outtextxy((600 - textwidth(s)) / 2, 300, s);

	SetWorkingImage();
	putimage(5, 5, &map);
}

void updateScore(snake *mua)
{
	SetWorkingImage(&score);
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 48;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	TCHAR outNum_t[20];
	TCHAR outScore_t[20];
	wcscpy_s(outScore_t, _T("得分:"));
	_itow_s(curScore, outNum_t, 10);
	wcscat_s(outScore_t, outNum_t);
	outtextxy((200 - textwidth(outScore_t)) / 2, 20, outScore_t);
	f.lfHeight = 48;
	settextstyle(&f);
	outtextxy(5, 100, _T("方向键控"));
	outtextxy(5, 150, _T("制蛇移动"));
	f.lfHeight = 40;
	settextstyle(&f);
	outtextxy(0, 250, _T("SPACE 暂停"));
	SetWorkingImage();
	putimage(610, 205, &score);
}

void showStat()
{
	SetWorkingImage(&bottomBar);
	cleardevice();

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 26;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(20, 10, _T("道具:"));

	putimage(20, 55, &i_pointer);
	outtextxy(60, 52, Items[POINTER]);
	if (items[POINTER])
	{
		settextcolor(levelCol[level]);
		outtextxy(200, 52, _T("[已获得]"));
		TCHAR info[200];
		char info_s[200];
		char num_s[10];
		strcpy_s(info_s, "剩余次数:");
		_itoa_s(items[POINTER], num_s, 10);
		strcat_s(info_s, num_s);
		CharToTchar(info_s, info);
		outtextxy(300, 52, info);
		settextcolor(levelCol[0]);
	}
	else
	{
		outtextxy(200, 52, _T("[未获得]"));
	}

	putimage(20, 90, &i_shield);
	outtextxy(60, 87, Items[SHIELD]);
	if (items[SHIELD])
	{
		settextcolor(levelCol[level]);
		outtextxy(200, 87, _T("[已获得]"));
		TCHAR info[200];
		char info_s[200];
		char num_s[10];
		strcpy_s(info_s, "剩余次数:");
		_itoa_s(items[SHIELD], num_s, 10);
		strcat_s(info_s, num_s);
		CharToTchar(info_s, info);
		outtextxy(300, 87, info);
		settextcolor(levelCol[0]);
	}
	else
	{
		outtextxy(200, 87, _T("[未获得]"));
	}

	putimage(20, 125, &i_bezoar);
	outtextxy(60, 122, Items[BEZOAR]);
	if (items[BEZOAR])
	{
		settextcolor(levelCol[level]);
		outtextxy(200, 122, _T("[已获得]"));
		TCHAR info[200];
		char info_s[200];
		char num_s[10];
		strcpy_s(info_s, "剩余次数:");
		_itoa_s(items[BEZOAR], num_s, 10);
		strcat_s(info_s, num_s);
		CharToTchar(info_s, info);
		outtextxy(300, 122, info);
		settextcolor(levelCol[0]);
	}
	else
	{
		outtextxy(200, 122, _T("[未获得]"));
	}
	IMAGE &show = i_skin;
	if (level == 1) show = i_skin;
	else if (level == 2) show = i_warm;
	else show = i_coat;
	putimage(20, 160, &show);
	outtextxy(60, 157, Items[level]);
	if (items[level])
	{
		settextcolor(levelCol[level]);
		outtextxy(200, 157, _T("[已获得]"));
		settextcolor(levelCol[0]);
	}
	else
	{
		outtextxy(200, 157, _T("[未获得]"));
	}
	setlinestyle(PS_SOLID, 5);
	line(500, 0, 500, 200);
	if ((counter % 300) > 200 && (counter % 300) % 3)
	{
		settextcolor(levelCol[level]);
		f.lfHeight = 64;
		settextstyle(&f);
		switch (level)
		{
			case 1:
			{
				outtextxy(530, 100, _T("着火"));
				break;
			}
			case 2:
			{
				outtextxy(530, 100, _T("冻僵"));
				break;
			}
			case 3:
			{
				outtextxy(530, 100, _T("辐射"));
				break;
			}
		}

		TCHAR remain[10];
		int remain_n = (300 - (counter % 300));
		_itow_s(remain_n, remain, 10);
		outtextxy(680, 100, remain);
		settextcolor(levelCol[0]);
	}
	if (gameMode == 1)
	{
		f.lfHeight = 40;
		settextstyle(&f);
		TCHAR ss[20];
		TCHAR ns[10];
		wcscpy_s(ss, _T("目标:"));
		_itow_s(length, ns, 10);
		wcscat_s(ss, ns);
		wcscat_s(ss, _T("/"));
		TCHAR gs[10];
		_itow_s(levelGoal, gs, 10);
		wcscat_s(ss, gs);
		outtextxy(600, 20, ss);
	}
	else
	{
		f.lfHeight = 40;
		settextstyle(&f);
		TCHAR ss[20];
		TCHAR ns[10];
		wcscpy_s(ss, _T("长度:"));
		_itow_s(length, ns, 10);
		wcscat_s(ss, ns);
		outtextxy(600, 20, ss);
	}
	SetWorkingImage();
	putimage(5, 610, &bottomBar);
}

void cleanStat()
{
	int i;
	for (i = 1; i <= 6; i++)
	{
		items[i] = itemsShow[i] = 0;
	}
	length = 0;
	SetWorkingImage(&bottomBar);
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 72;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(levelCol[level - 1]);
	TCHAR s[10] = _T("恭喜过关");
	outtextxy((805 - textwidth(s)) / 2, 50, s);
	_tcscpy_s(f.lfFaceName, _T("Consolas"));
	f.lfHeight = 32;
	settextstyle(&f);
	outtextxy((805 - textwidth(quotes[level - 1])) / 2, 120, quotes[level - 1]);
	settextcolor(levelCol[0]);
	SetWorkingImage();
	putimage(5, 610, &bottomBar);
}

void deadStat()
{
	SetWorkingImage(&bottomBar);
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 72;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	TCHAR s[10] = _T("再接再厉");
	outtextxy((805 - textwidth(s)) / 2, 50, s);
	_tcscpy_s(f.lfFaceName, _T("Consolas"));
	f.lfHeight = 32;
	settextstyle(&f);
	outtextxy((805 - textwidth(quotes[level - 1])) / 2, 120, quotes[0]);
	SetWorkingImage();
	putimage(5, 610, &bottomBar);
}

void clearBottom()
{
	SetWorkingImage(&bottomBar);
	cleardevice();
	SetWorkingImage();
	putimage(5, 610, &bottomBar);
}

void gamePause(snake *mua)
{
	SetWorkingImage(&score);
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 33;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy((200 - 33 * 4) / 2, 10, _T("暂停"));
	outtextxy(0, 50, _T("[SPACE]"));
	outtextxy(0, 90, _T(" 继续游戏"));
	outtextxy(0, 140, _T("[M]"));
	outtextxy(0, 180, _T(" 保存游戏"));
	outtextxy(0, 230, _T("[L]"));
	outtextxy(0, 260, _T(" 返回主菜单"));
	outtextxy((200 - 33 * 5) / 2, 330, _T("[ESC] 退出"));

	SetWorkingImage();
	putimage(610, 205, &score);

	while (!_kbhit());
	char c = _getch();
	if (c == 27)
	{
		exit(0);
	}
	else if (c == ' ')
	{
		updateScore(mua);
		return;
	}
	else if (c == 'M' || c == 'm')
	{
		saveMap(mua);
		gamePause(mua);
		return;
	}
	else if (c == 'L' || c == 'l')
	{
		isFinish = 1;
	}
	else gamePause(mua);
}

void initRes()
{
	loadimage(&i_bezoar, _T("img"), _T("bezoar"));
	loadimage(&i_coat, _T("img"), _T("coat"));
	loadimage(&i_grass, _T("img"), _T("grass"));
	loadimage(&i_mine, _T("img"), _T("mine"));
	loadimage(&i_pointer, _T("img"), _T("pointer"));
	loadimage(&i_shield, _T("img"), _T("shield"));
	loadimage(&i_skin, _T("img"), _T("skin"));
	loadimage(&i_warm, _T("img"), _T("warm"));
}

void showLevel()
{
	showInfo();
	SetWorkingImage(&score);
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 40;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(5, 40, _T("当前关卡:"));
	outtextxy(5, 120, levelc[level]);
	outtextxy(5, 160, levels[level]);
	f.lfHeight = 32;
	settextstyle(&f);
	outtextxy(5, 240, _T("[SPACE] 开始"));
	SetWorkingImage();
	putimage(610, 205, &score);
	char ch;
	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();
			//printf("%d\n", ch);
			if (ch == ' ')
			{
				break;
			}
			else continue;
		}
	}
}

void showInfo()
{
	SetWorkingImage(&map);
	cleardevice();

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 60;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(levelCol[level]);
	setlinecolor(levelCol[level]);
	outtextxy(50, 50, levelc[level]);
	outtextxy(50, 115, levels[level]);
	setlinestyle(PS_SOLID, 3);
	line(0, 185, 600, 185);
	f.lfHeight = 30;
	settextstyle(&f);
	outtextxy(50, 200, mapEvent[level]);
	outtextxy(50, 260, _T("地图道具"));
	IMAGE &show = i_skin;
	if (level == 1) show = i_skin;
	else if (level == 2) show = i_warm;
	else show = i_coat;
	putimage(50, 320, &show);
	outtextxy(100, 315, Items[level]);
	outtextxy(50, 350, globalItemsDetail[level]);
	line(0, 400, 600, 400);
	outtextxy(50, 420, _T("普通道具"));

	putimage(40, 470, &i_pointer);
	outtextxy(60, 465, Items[POINTER]);
	outtextxy(220, 465, globalItemsDetail[POINTER]);

	putimage(40, 510, &i_shield);
	outtextxy(60, 505, Items[SHIELD]);
	outtextxy(220, 505, globalItemsDetail[SHIELD]);

	putimage(40, 550, &i_bezoar);
	outtextxy(60, 545, Items[BEZOAR]);
	outtextxy(220, 545, globalItemsDetail[BEZOAR]);

	SetWorkingImage();
	putimage(5, 5, &map);
}

void initBoard()
{
	initgraph(815, 815);
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, _T("这就是蛇吗"));
	setbkcolor(WHITE);
	cleardevice();

	SetWorkingImage(&map);
	setbkcolor(BLACK);
	cleardevice();
	SetWorkingImage();
	putimage(5, 5, &map);

	SetWorkingImage(&rank);
	setbkcolor(BLACK);
	cleardevice();
	SetWorkingImage();
	putimage(610, 5, &rank);

	SetWorkingImage(&score);
	setbkcolor(BLACK);
	cleardevice();
	SetWorkingImage();
	putimage(610, 205, &score);

	SetWorkingImage(&bottomBar);
	setbkcolor(BLACK);
	cleardevice();
	SetWorkingImage();
	putimage(5, 610, &bottomBar);
}

void displaySnake(snake *Emm)
{
	SetWorkingImage(&map);
	cleardevice();
	snakeNode *pNode = Emm->head;
	setfillcolor(pNode->c);
	if (pNode->dir == 0)
	{
		POINT head[4] =
		{
						{pNode->x * l_grid + l_grid / 3,     pNode->y * l_grid},
						{pNode->x * l_grid + l_grid * 2 / 3, pNode->y * l_grid},
						{pNode->x * l_grid + l_grid,         pNode->y * l_grid + l_grid},
						{pNode->x * l_grid,                  pNode->y * l_grid + l_grid}
		};
		solidpolygon(head, 4);
	}
	else if (pNode->dir == 1)
	{
		POINT head[4] =
		{
						{pNode->x * l_grid + l_grid / 3,     pNode->y * l_grid + l_grid},
						{pNode->x * l_grid + l_grid * 2 / 3, pNode->y * l_grid + l_grid},
						{pNode->x * l_grid + l_grid,         pNode->y * l_grid},
						{pNode->x * l_grid,                  pNode->y * l_grid}
		};
		solidpolygon(head, 4);
	}
	else if (pNode->dir == 2)
	{
		POINT head[4] =
		{
						{pNode->x * l_grid,          pNode->y * l_grid + l_grid * 2 / 3},
						{pNode->x * l_grid,          pNode->y * l_grid + l_grid / 3},
						{pNode->x * l_grid + l_grid, pNode->y * l_grid},
						{pNode->x * l_grid + l_grid, pNode->y * l_grid + l_grid}
		};
		solidpolygon(head, 4);
	}
	else if (pNode->dir == 3)
	{
		POINT head[4] =
		{
						{pNode->x * l_grid + l_grid, pNode->y * l_grid + l_grid / 3},
						{pNode->x * l_grid + l_grid, pNode->y * l_grid + l_grid * 2 / 3},
						{pNode->x * l_grid,          pNode->y * l_grid + l_grid},
						{pNode->x * l_grid,          pNode->y * l_grid}
		};
		solidpolygon(head, 4);
	}
	pNode = pNode->next;
	while (pNode != NULL)
	{
		setfillcolor(pNode->c);
		POINT pos[] = {
						{pNode->x * l_grid + l_grid / 3,     pNode->y * l_grid},
						{pNode->x * l_grid + l_grid * 2 / 3, pNode->y * l_grid},
						{(pNode->x + 1) * l_grid,            pNode->y * l_grid + l_grid / 3},
						{(pNode->x + 1) * l_grid,            pNode->y * l_grid + l_grid * 2 / 3},
						{pNode->x * l_grid + l_grid * 2 / 3, (pNode->y + 1) * l_grid},
						{pNode->x * l_grid + l_grid / 3,     (pNode->y + 1) * l_grid},
						{pNode->x * l_grid,                  pNode->y * l_grid + l_grid * 2 / 3},
						{pNode->x * l_grid,                  pNode->y * l_grid + l_grid / 3}
		};
		solidpolygon(pos, 8);
		pNode = pNode->next;
	}
	if (items[POINTER])
	{
		setlinestyle(PS_SOLID, 1);
		items[POINTER]--;
		pNode = Emm->head;
		int x, y;
		x = pNode->x;
		y = pNode->y;
		setlinecolor(RGB(50, 50, 50));
		if (Emm->currentDir == UP || Emm->currentDir == DOWN)
		{
			line(x * l_grid, 0, x * l_grid, 600);
			line((x + 1) * l_grid, 0, (x + 1) * l_grid, 600);
		}
		if (Emm->currentDir == LEFT || Emm->currentDir == RIGHT)
		{
			line(0, y * l_grid, 600, y * l_grid);
			line(0, (y + 1) * l_grid, 600, (y + 1) * l_grid);
		}
	}
}

void displayFood()
{
	setfillcolor(foodInfo.c);
	solidcircle(foodInfo.x * l_grid + l_grid / 2, foodInfo.y * l_grid + l_grid / 2, l_grid / 2);
	setfillcolor(BLACK);
	POINT food[] = {
					{foodInfo.x * l_grid + l_grid / 2,     foodInfo.y * l_grid + l_grid / 4},
					{foodInfo.x * l_grid + l_grid * 3 / 4, foodInfo.y * l_grid + l_grid * 3 / 4},
					{foodInfo.x * l_grid + l_grid / 4,     foodInfo.y * l_grid + l_grid * 3 / 4},
	};
	solidpolygon(food, 3);
}

void displayMine()
{
	putimage(mine.x * l_grid, mine.y * l_grid, &i_mine);
}

void displayPoi()
{
	if (isPoi)
	{
		poison++;
		if (poison == 50)
		{
			poison = 0;
			isPoi = 0;
		}
		if (isPoi && poison % 3)
		{
			int i;
			for (i = 1; i <= 10; i++)
			{
				putimage(poi[i].x * l_grid, poi[i].y * l_grid, &i_grass);
			}
		}
	}
}

void displayItem()
{
	int toShow = 0;
	if (itemsShow[POINTER]) toShow = POINTER;
	else if (itemsShow[SHIELD]) toShow = SHIELD;
	else if (itemsShow[BEZOAR]) toShow = BEZOAR;
	if (toShow)
	{
		//printf("%d<=\n", toShow);
		switch (toShow)
		{
			case POINTER:
			{
				putimage(pointer.x * l_grid, pointer.y * l_grid, &i_pointer);
				break;
			}
			case SHIELD:
			{
				putimage(shield.x * l_grid, shield.y * l_grid, &i_shield);
				break;
			}
			case BEZOAR:
			{
				putimage(bezoar.x * l_grid, bezoar.y * l_grid, &i_bezoar);
				break;
			}
		}
	}
}

void displaySpecial()
{
	if (itemsShow[level])
	{
		switch (level)
		{
			case NOHEAT:
			{
				putimage(special.x * l_grid, special.y * l_grid, &i_skin);
				break;
			}
			case NOCOLD:
			{
				putimage(special.x * l_grid, special.y * l_grid, &i_warm);
				break;
			}
			case NORADIO:
			{
				putimage(special.x * l_grid, special.y * l_grid, &i_coat);
				break;
			}
		}
	}
}

void display(snake *Emm)
{
	SetWorkingImage(&map);
	cleardevice();
	displaySnake(Emm);
	displayFood();
	displayMine();
	displayPoi();
	displayItem();
	displaySpecial();
	SetWorkingImage();
	putimage(5, 5, &map);
	showStat();
}