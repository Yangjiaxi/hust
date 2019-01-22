#include <graphics.h>
#include "snake.h"

int dx[] = { 0, 0, -1, 1 };
int dy[] = { -1, 1, 0, 0 };
int isFinish = 0; //全局结束标志
int length = 0;

//颜色常量定义
int colorC = 0;
int colorBit = 4; //默认三项开关全部开启
int shift = 40;

int grids = 30; //棋盘为grids * grids，坐标在左上角，以每个左上角的小格标记坐标
int l_grid = 600 / 30;  //像素大小
int max = 100;
int interval = max;
int decNum = 5;
int dec = 10;
int min = 50;
int seed = 0; //随机数种子
int curScore = 0;
int poison = 0; //毒草句柄
int isPoi = 0; //当前是否显示毒草
int level = 1; //当前关卡(一共三关)
int levelGoal = 35; //达成通关条件需要的节数
int gameMode = 0; //游戏模式 0:默认 1:闯关模式 2:自选关卡
int shouldNext = 0; //是否应该进入下一关
int counter = 0; //全局计数器
//闯关模式会在一关结束后自动进入下一关
//自选关卡会下一关结束后返回主界面
//=>使用snake->num来判断是否通关
int eventComes; //事件点
int items[10];  //记录物品是否拥有/剩余使用次数，0表示用完/没拥有
int itemsShow[10]; //是否应该显示这个物品
struct _food special; //地图事件道具
struct _food pointer; //指星笔
struct _food shield;  //盾
struct _food bezoar;  //牛黄

IMAGE map(600, 600);  //走蛇的部分
IMAGE rank(200, 195); //排行榜部分
IMAGE score(200, 400); //得分、操作提示部分
IMAGE bottomBar(805, 200); //图鉴

const TCHAR levelc[5][10] =
{
				_T("EMPTY"),
				_T("第一关[1]"),
				_T("第二关[2]"),
				_T("第三关[3]")
};

const TCHAR levels[5][10] =
{
				_T("EMPTY"),
				_T(" 炼狱熔炉"),
				_T(" 冰雪绝境"),
				_T(" 末日废土")
};

const TCHAR mapEvent[5][20] =
{
				_T("EMPTY"),
				_T("[地图事件] 着火!"),
				_T("[地图事件] 冻僵!"),
				_T("[地图事件] 辐射!")
};

const TCHAR Items[10][10] =
{
				_T("EMPTY"),
				_T("黑曜石皮肤"),
				_T("暖手宝"),
				_T("防化服"),
				_T("指星笔"),
				_T("圣十字盾"),
				_T("牛黄")
};

const TCHAR globalItemsDetail[10][20] =
{
				_T("EMPTY"),
				_T("一次性道具，抵抗着火事件"),
				_T("一次性道具，抵抗冻僵事件"),
				_T("一次性道具，抵抗辐射事件"),
				_T("被动，200/200，指明方向"),
				_T("被动，10/10，抵御所有伤害"),
				_T("被动，10/10，抵御毒草伤害")
};

const TCHAR quotes[5][40] =
{
				_T("\"People die if they are killed.\""),
				_T("\"Hell is empty, all devils are here.\""),
				_T("\"Winter is coming.\""),
				_T("\"War, war never changes.\"")
};

const COLORREF levelCol[4]
{
				RGB(255, 255, 255),
				RGB(226, 88, 34),
				RGB(113, 166, 210),
				RGB(176, 191, 26)
};

struct _record record;

struct _food foodInfo;
struct _food mine;
struct _food poi[11]; //[1...10] => 10个

IMAGE i_bezoar;
IMAGE i_coat;
IMAGE i_grass;
IMAGE i_mine;
IMAGE i_pointer;
IMAGE i_shield;
IMAGE i_skin;
IMAGE i_warm;