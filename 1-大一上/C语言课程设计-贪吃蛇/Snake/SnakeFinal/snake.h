#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <graphics.h>

//定义蛇的方向
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

//地图事件道具
#define NOHEAT 1
#define NOCOLD 2
#define NORADIO 3

//普通道具
#define POINTER 4
#define SHIELD 5
#define BEZOAR 6

extern IMAGE map;
extern IMAGE rank;
extern IMAGE score;
extern IMAGE bottomBar;

extern int dx[];
extern int dy[];
extern int isFinish;
extern int length;
extern int grids;
extern int l_grid;
extern int max;
extern int interval;
extern int decNum;
extern int dec;
extern int min;
extern int colorC;
extern int shift;
extern int colorBit;
extern int seed;
extern int poison;
extern int isPoi;
extern int level;
extern int levelGoal;
extern int gameMode;
extern int shouldNext;
extern int curScore;
extern int counter;
extern int items[10];
extern int itemsShow[10];
extern int eventComes;
extern struct _food special;
extern struct _food pointer;
extern struct _food shield;
extern struct _food bezoar;
extern struct _record record;
extern struct _food foodInfo;
extern struct _food mine;
extern struct _food poi[11];

extern const TCHAR levelc[5][10];
extern const TCHAR levels[5][10];
extern const TCHAR Items[10][10];
extern const TCHAR globalItemsDetail[10][20];
extern const TCHAR mapEvent[5][20];
extern const TCHAR quotes[5][40];
extern const COLORREF levelCol[4];

extern IMAGE i_bezoar;
extern IMAGE i_coat;
extern IMAGE i_grass;
extern IMAGE i_mine;
extern IMAGE i_pointer;
extern IMAGE i_shield;
extern IMAGE i_skin;
extern IMAGE i_warm;

typedef struct _snakeNode
{
	int x;
	int y;
	int dir; //这段身体的方向
	COLORREF c;
	struct _snakeNode *next;
	struct _snakeNode *prev;
} snakeNode;

typedef struct _snake
{
	snakeNode *head;
	snakeNode *tail;
	int num;
	int currentDir;  //当前的移动方向
} snake;

typedef struct _rankNode
{
	char name[50];
	int score;
} rankNode;

struct _record
{
	rankNode list[20];
	int total;
};

struct _food
{
	int x;
	int y;
	COLORREF c;
};

//功能函数
void TCharToChar(const TCHAR *tchar, char *_char); //宽字符->字符
void CharToTchar(const char *_char, TCHAR *tchar); //字符->宽字符
int cmp(const void *a, const void *b); //比较函数
int randNext(int left, int right); //产生[left, right] 的随机数

//游戏类
void start(); //初始化
void printRank(); //控制台打印排行
bool canPlace(int x, int y, snake *mua); //能否放置item
void randomFood(snake *mua); //随机生成食物
void randomMine(snake *mua); //生成炸弹
void randomPoi(snake *mua); //生成毒草
void randomItem(int type, snake *mua); //生成普通道具
void randomSpecial(snake *mua); //生成事件道具
bool hasFood(snake *mua); //前方有食物
bool hasMine(snake *mua); //前方有地雷
bool hasPoison(snake *mua); //前方有毒草
bool hasItem(snake *mua); //前方有普通道具
bool hasSpecial(snake *mua); //前方有特殊道具
void poisonEat(snake *mua); //吃毒草
void mineEat(snake *mua); //吃地雷
bool judgeCurrent(snake *mua); //判断当前蛇的形态
void saveMap(snake *mua); //保存游戏
void upLoadScore(TCHAR name[], snake *mua); //上传新的排行
void getRank(); //从文件读取排行
void dealAction(snake *mua); //处理一步
void getCommand(); //获取指令
void startGame(); //开始游戏
snake loadGame(); //从文件读取存档
void loop(snake *mua); //事件循环核心
void fullMode(); //闯关模式
void selectMap(); //自选模式

//图像类
void srandColor(); //初始化颜色种子
COLORREF nextCol(); //生成下一种颜色
void showRank();  //展示排行
void initPanel(); //初始化右下角面板
void updateScore(snake *mua); //显示排行
void gamePause(snake *mua); //游戏暂停
void initRes(); //加载资源文件
void showLevel(); //显示要进入的关卡
void showInfo(); //显示本关卡信息
void initBoard(); //全局初始化
void initMapSaying(); //显示欢迎界面
void showStat(); //初始化图鉴
void clearBottom(); //初始化底部
void cleanStat(); //清空底部统计版
void deadStat(); //显示死亡信息
void display(snake *Emm); //显示所有
void displaySnake(snake *Emm); //显示蛇
void displayFood(); //显示食物
void displayMine(); //显示地雷
void displayPoi(); //显示毒草
void displayItem(); //显示普通道具
void displaySpecial(); //显示特殊道具

//蛇类
void snakeInit(int n, snake *mua); //初始化蛇
void printSnake(snake *mua); //控制台输出蛇
void snakeMove(snake *mua); //蛇移动
void snakeEat(snake *mua); //蛇吃食物
void snakeHalf(snake *mua); //身体减半
void snakeCut(snake *mua); //去掉尾部
void freeAll(snake *mua); //释放整条蛇


#endif // !SNAKE_H_INCLUDED

