#include<iostream>
#include<graphics.h>//easyx绘制ui devc++ -leasyx
#include<conio.h>
#include<Windows.h>
#include<cstring>
#include<string>
#include <ctime>
#include<random>
#include <cstdlib>
#include<mmsystem.h>//包含多媒体设备接口头文件  devc++ -lwinmm
#pragma comment(lib,"winmm.lib")//加载静态库
#include<fstream>
using namespace std;

ofstream fout;
ifstream fin;


int musicflag;
bool flag[10];
bool findflag[2];
bool xianshou;
char map[8][8] = { 0 };

char cdmap[5][8][9] = { 0 };//[i][0][8]存执子状态，人机下，黑为1，白为0；双人下为3；[i][1][8]存回合状态 [i][2][8]存进行到第几回合
int huihe, huiheshu;//1为黑，0为白
int chizicnt;
//模拟预测
int yucehuihe;
int blackyuce, whiteyuce;
int findflagyuce[2];
double yuceheigailv, yucebaigailv;
bool yuceflag[10];
int yucecnt;
char yucemap[8][8] = { 0 };
int bestyucem, bestyucen; bool ai4flag[10];
double cengheiwin, cengbaiwin, cengjushu, bestcenggailv;
int sousuoceng;
int guzhijieduan;
char huiqimap[70][8][8] = { 0 };
int huiqim[70], huiqin[70], huiqihuihe[70], huiqihei[70], huiqibai[70];
int temphuiheshu, huiqiju;
bool huiqiflag = true;
int difficult;
int dire[8][2] = { {1, 0}, {-1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1} };

int quanzhi[8][8] = { {150,-80,20,20,20,20,-80,150} ,
					{-80,-100,10,5,5,10,-100,-80 },
					{20,10,3,2,2,3,10,20},
					{20,5,2,1,1,2,5,20},
					{20,5,2,1,1,2,5,20},
					{20,10,3,2,2,3,10,20 },
					{-80,-100,10,5,5,10,-100,-80},
					{150,-80,10,20,20,10,-80,150 } };
int bestquan, minmaxceng[20];
struct yucekexia//储存可以下的位置
{
	int x;
	int y;
	bool yucekexiaflag[10];
};

ExMessage m;
IMAGE pic[10], background, tempimg, totalblack;
string blacktext, whitetext, huihetext, huiheshutext;
int black, white;
struct button
{
	int x1;
	int x2;
	int y1;
	int y2;
};


bool checkhefa(int x, int y)
{
	if (x > 7 || x < 0)return false;
	if (y > 7 || y < 0)return false;
	return true;
}
void begin();
void ui2();
void caidanui(int zhizi);
void pictrueload()
{
	loadimage(&pic[0], _T("../source/pictures/空.jpg"));
	loadimage(&pic[1], _T("../source/pictures/黑子.jpg"));
	loadimage(&pic[2], _T("../source/pictures/白子.jpg"));
	loadimage(&background, _T("../source/pictures/3.png"));
	loadimage(&totalblack, _T("../source/pictures/黑色.png"));
}
void setbutton(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//绘制按钮(按钮，文本，文本长度，文本宽度，间距，文本颜色，边框颜色，填充颜色)
{
	if (boxcolor == "red")setlinecolor(RED);//设置边框颜色为红色
	else if (boxcolor == "green")setlinecolor(GREEN);//设置边框颜色为红色
	else if (boxcolor == "blue")setlinecolor(BLUE);//设置边框颜色为红色
	else if (boxcolor == "yellow")setlinecolor(YELLOW);//设置边框颜色为黄色
	else if (boxcolor == "black")setlinecolor(BLACK);//设置边框颜色为黑色
	else if (boxcolor == "white")setlinecolor(WHITE);//设置边框颜色为白色
	else if (boxcolor == "cyan")setlinecolor(CYAN);//青色
	else if (boxcolor == "magenta")setlinecolor(MAGENTA);//紫色
	else if (boxcolor == "brown")setlinecolor(BROWN);//棕色
	else if (boxcolor == "lightgray")setlinecolor(LIGHTGRAY);//浅灰
	else if (boxcolor == "darkgray")setlinecolor(DARKGRAY);//深灰
	else if (boxcolor == "lightblue")setlinecolor(LIGHTBLUE);//亮蓝色
	else if (boxcolor == "lightcyan")setlinecolor(LIGHTCYAN);//亮青色
	else if (boxcolor == "lightred")setlinecolor(LIGHTRED);//亮红色
	else if (boxcolor == "lightmagenta")setlinecolor(LIGHTMAGENTA);//亮紫色
	rectangle(a.x1, a.y1, a.x2, a.y2);//绘制矩形边框
	if (fillcolor == "red")setfillcolor(RED);//设置填充颜色为红色
	else if (fillcolor == "green")setfillcolor(GREEN);//设置填充颜色为红色
	else if (fillcolor == "blue")setfillcolor(BLUE);//设置填充颜色为红色
	else if (fillcolor == "yellow")setfillcolor(YELLOW);//设置填充颜色为黄色
	else if (fillcolor == "black")setfillcolor(BLACK);//设置填充颜色为黑色
	else if (fillcolor == "cyan")setfillcolor(CYAN);//青色
	else if (fillcolor == "magenta")setfillcolor(MAGENTA);//紫色
	else if (fillcolor == "brown")setfillcolor(BROWN);//棕色
	else if (fillcolor == "lightgray")setfillcolor(LIGHTGRAY);//浅灰
	else if (fillcolor == "darkgray")setfillcolor(DARKGRAY);//深灰
	else if (fillcolor == "lightblue")setfillcolor(LIGHTBLUE);//亮蓝色
	else if (fillcolor == "lightcyan")setfillcolor(LIGHTCYAN);//亮青色
	else if (fillcolor == "lightred")setfillcolor(LIGHTRED);//亮红色
	else if (fillcolor == "lightmagenta")setfillcolor(LIGHTMAGENTA);//亮紫色
	fillrectangle(a.x1, a.y1, a.x2, a.y2);
	setbkmode(TRANSPARENT);//设置透明字体
	if (textcolor == "red")settextcolor(RED);//设置字体颜色为红色
	else if (textcolor == "green")settextcolor(GREEN);//设置字体颜色为红色
	else if (textcolor == "blue")settextcolor(BLUE);//设置字体颜色为红色
	else if (textcolor == "yellow")settextcolor(YELLOW);//设置字体颜色为黄色
	else if (textcolor == "black")settextcolor(BLACK);//设置字体颜色为黑色
	else if (textcolor == "white")settextcolor(WHITE);//设置字体颜色为白色
	else if (textcolor == "cyan")settextcolor(CYAN);//青色
	else if (textcolor == "magenta")settextcolor(MAGENTA);//紫色
	else if (textcolor == "brown")settextcolor(BROWN);//棕色
	else if (textcolor == "lightgray")settextcolor(LIGHTGRAY);//浅灰
	else if (textcolor == "darkgray")settextcolor(DARKGRAY);//深灰
	else if (textcolor == "lightblue")settextcolor(LIGHTBLUE);//亮蓝色
	else if (textcolor == "lightcyan")settextcolor(LIGHTCYAN);//亮青色
	else if (textcolor == "lightred")settextcolor(LIGHTRED);//亮红色
	else if (textcolor == "lightmagenta")settextcolor(LIGHTMAGENTA);//亮紫色
	settextstyle(tlength, twidth, _T("宋体"));//字体风格设置
	outtextxy(a.x1 + textoff, a.y1 + textoff, text);//设置文本显示位置
}
void bgmbutton(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(WHITE);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			if (musicflag == 1)
			{
				mciSendString("close ..\\source\\fanyu.mp3", NULL, 0, NULL);
				musicflag = 0;
			}
			else
			{
				musicflag = 1;
				mciSendString("open ..\\source\\fanyu.mp3", NULL, 0, NULL);
				mciSendString("play ..\\source\\fanyu.mp3", NULL, 0, NULL);
			}
			FlushBatchDraw();//批量绘制
			Sleep(500);
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void ui6(int dang, int zhizi);
void ui5(int dang);
void cunchu1button(int zhizi, button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui2存档
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(GREEN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			fout.open("..\\saved\\存档一.txt");
			fout << zhizi << endl;
			fout << huihe << endl;
			fout << huiheshu << endl;
			fout << difficult << endl;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					cdmap[1][i][j] = map[i][j];
					if (map[i][j] == 'B' || map[i][j] == 'W')fout << map[i][j];
					else fout << '0';
				}
				fout << endl;
			}
			cdmap[1][0][8] = zhizi;
			cdmap[1][1][8] = huihe;
			cdmap[1][2][8] = huiheshu;
			cdmap[1][3][8] = difficult;
			fout.close();
			HWND hndcd1 = GetHWnd();
			int isok;
			isok = MessageBox(hndcd1, "对局成功存于一号存档", "提示", MB_OK);
			if (isok == IDOK)
			{
				if (zhizi != 3)ui6(4, zhizi);
				else ui5(1);
			}
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void cunchu2button(int zhizi, button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui2存档
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(GREEN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			fout.open("..\\saved\\存档二.txt");
			fout << zhizi << endl;
			fout << huihe << endl;
			fout << huiheshu << endl;
			fout << difficult << endl;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					cdmap[2][j][j] = map[i][j];
					if (map[i][j] == 'B' || map[i][j] == 'W')fout << map[i][j];
					else fout << '0';
				}
				fout << endl;
			}
			cdmap[2][0][8] = zhizi;
			cdmap[2][1][8] = huihe;
			cdmap[2][2][8] = huiheshu;
			cdmap[2][3][8] = difficult;
			fout.close();
			HWND hndcd2 = GetHWnd();
			int isok;
			isok = MessageBox(hndcd2, "对局成功存于二号存档", "提示", MB_OK);
			if (isok == IDOK)
			{
				if (zhizi != 3)ui6(4, zhizi);
				else ui5(2);
			}
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void cunchu3button(int zhizi, button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui2存档
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(GREEN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			fout.open("..\\saved\\存档三.txt");
			fout << zhizi << endl;
			fout << huihe << endl;
			fout << huiheshu << endl;
			fout << difficult << endl;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					cdmap[3][i][j] = map[i][j];
					if (map[i][j] == 'B' || map[i][j] == 'W')fout << map[i][j];
					else fout << '0';
				}
				fout << endl;
			}
			cdmap[3][0][8] = zhizi;
			cdmap[3][1][8] = huihe;
			cdmap[3][2][8] = huiheshu;
			cdmap[3][3][8] = difficult;
			fout.close();
			HWND hndcd3 = GetHWnd();
			int isok;
			isok = MessageBox(hndcd3, "对局成功存于三号存档", "提示", MB_OK);
			if (isok == IDOK)
			{
				if (zhizi != 3)ui6(4, zhizi);
				else ui5(3);
			}
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void fanhui4button(int zhizi, button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui2存档
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			caidanui(zhizi);
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void cunchuui(int zhizi)//存储档案
{
	initgraph(1208, 807, EX_SHOWCONSOLE);
	HWND hndcd = GetHWnd();//获取窗口句柄
	SetWindowText(hndcd, "存档选择");
	putimage(0, 0, &background);
	button cunchuwei[4];
	//存档一
	cunchuwei[1].x1 = 500;
	cunchuwei[1].x2 = 600;
	cunchuwei[1].y1 = 220;
	cunchuwei[1].y2 = 250;
	TCHAR ccw1text[1000] = _T("存档一");
	//存档二
	cunchuwei[2].x1 = 500;
	cunchuwei[2].x2 = 600;
	cunchuwei[2].y1 = 280;
	cunchuwei[2].y2 = 310;
	TCHAR ccw2text[1000] = _T("存档二");
	//存档三
	cunchuwei[3].x1 = 500;
	cunchuwei[3].x2 = 600;
	cunchuwei[3].y1 = 340;
	cunchuwei[3].y2 = 370;
	TCHAR ccw3text[1000] = _T("存档三");
	button fanhui4;
	//返回按钮
	fanhui4.x1 = 500;
	fanhui4.x2 = 600;
	fanhui4.y1 = 400;
	fanhui4.y2 = 430;
	TCHAR fanhui4text[1000] = _T("返回");
	while (1)
	{
		//(按钮，文本，文本长度，文本宽度，间距，文本颜色，边框颜色，填充颜色)
		fanhui4button(zhizi, fanhui4, fanhui4text, 20, 10, 5, "black", "lightmagenta", "cyan");
		cunchu1button(zhizi, cunchuwei[1], ccw1text, 20, 10, 5, "black", "green", "cyan");
		cunchu2button(zhizi, cunchuwei[2], ccw2text, 20, 10, 5, "black", "green", "cyan");
		cunchu3button(zhizi, cunchuwei[3], ccw3text, 20, 10, 5, "black", "green", "cyan");
	}
	_getch();
}
void caidan1button(int zhizi, button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//菜单 存档
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互	
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(WHITE);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			cunchuui(zhizi);
		}
		break;
	}
}
void caidan2button(int zhizi, button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//菜单 返回
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互	
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(WHITE);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			cdmap[4][0][8] = zhizi;
			cdmap[4][1][8] = huihe;
			cdmap[4][2][8] = huiheshu;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					cdmap[4][i][j] = map[i][j];
				}
			}
			if (zhizi != 3)ui6(4, zhizi);//单纯返回 故dang不取0 1 2 3 
			else ui5(4);//返回双人
		}
		break;
	}
}
void caidan3button(int zhizi, button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//菜单 返回
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互	
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(WHITE);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			begin();//单纯返回 故dang不取0 1 2 3 
		}
		break;
	}
}
void caidanui(int zhizi)
{
	initgraph(1208, 807, EX_SHOWCONSOLE);
	HWND hndcaidan = GetHWnd();//获取窗口句柄
	SetWindowText(hndcaidan, "菜单");
	putimage(0, 0, &background);
	button caidanxz[4];
	//存档一
	caidanxz[1].x1 = 500;
	caidanxz[1].x2 = 560;
	caidanxz[1].y1 = 220;
	caidanxz[1].y2 = 250;
	TCHAR cdxz1text[1000] = _T("存档");
	//存档二
	caidanxz[2].x1 = 500;
	caidanxz[2].x2 = 560;
	caidanxz[2].y1 = 280;
	caidanxz[2].y2 = 310;
	TCHAR cdxz2text[1000] = _T("返回");
	//存档三
	caidanxz[3].x1 = 500;
	caidanxz[3].x2 = 560;
	caidanxz[3].y1 = 340;
	caidanxz[3].y2 = 370;
	TCHAR cdxz3text[1000] = _T("退出");
	button music;
	//音乐播放按钮
	music.x1 = 0;
	music.x2 = 100;
	music.y1 = 0;
	music.y2 = 30;
	TCHAR musictext[1000] = _T("音乐开关");
	while (1)
	{
		//(按钮，文本，文本长度，文本宽度，间距，文本颜色，边框颜色，填充颜色)
		bgmbutton(music, musictext, 20, 10, 5, "black", "red", "green");
		caidan1button(zhizi, caidanxz[1], cdxz1text, 20, 10, 5, "black", "lightmagenta", "cyan");
		caidan2button(zhizi, caidanxz[2], cdxz2text, 20, 10, 5, "black", "lightmagenta", "cyan");
		caidan3button(zhizi, caidanxz[3], cdxz3text, 20, 10, 5, "black", "lightmagenta", "cyan");
	}
	_getch();
}
void caidanbutton(int zhizi, button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互	
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(WHITE);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			caidanui(zhizi);
		}
		break;
	}
}
bool judge(int x, int y)
{
	chizicnt = 0;
	if (map[x][y] == 'W' || map[x][y] == 'B' || x > 7 || y > 7 || x < 0 || y < 0)return false;
	char now = ((huihe == 1) ? 'B' : 'W');
	char op = ((huihe == 1) ? 'W' : 'B');
	flag[1] = 0;//右方
	flag[2] = 0;//左方
	flag[3] = 0;//上方
	flag[4] = 0;//下方
	flag[5] = 0;//左上
	flag[6] = 0;//左下
	flag[7] = 0;//右下
	flag[8] = 0;//右上
	for (int i = 1; i <= 8; i++)
	{
		int j = 1;
		if (checkhefa(x + dire[i - 1][0], y + dire[i - 1][1]) && map[x + dire[i - 1][0]][y + dire[i - 1][1]] == op)
		{
			for (j = 2; j <= 7; j++)
			{
				if (!checkhefa(x + j * dire[i - 1][0], y + j * dire[i - 1][1]))break;
				else if (map[x + j * dire[i - 1][0]][y + j * dire[i - 1][1]] != 'B' && map[x + j * dire[i - 1][0]][y + j * dire[i - 1][1]] != 'W')//空
				{
					break;
				}
				else if (map[x + j * dire[i - 1][0]][y + j * dire[i - 1][1]] == now)
				{
					flag[i] = true;
					break;
				}
			}
		}
		else continue;
	}
	return(flag[1] || flag[2] || flag[3] || flag[4] || flag[5] || flag[6] || flag[7] || flag[8]);
}
bool final()
{
	if (black + white == 64)return true;//下满
	if (black == 0 || white == 0)return true;//吃完
	if (findflag[0] == 0 && findflag[1] == 0)return true;//不能再下
	return false;
}
void begin();
void ui3();
void jieguo()
{
	HWND hndjieguo = GetHWnd();
	char str[30] = "黑子：", shuliang[5];
	sprintf_s(shuliang, "%d", black);
	strcat_s(str, shuliang);
	strcat_s(str, " 白子：");
	sprintf_s(shuliang, "%d", white);
	strcat_s(str, shuliang);
	string baizi = to_string(white);
	int isok;
	if (black == white)
		isok = MessageBox(hndjieguo, str, "游戏结束，和局", MB_OKCANCEL);
	else if (black > white)
		isok = MessageBox(hndjieguo, str, "游戏结束，黑胜", MB_OKCANCEL);
	else
		isok = MessageBox(hndjieguo, str, "游戏结束，白胜", MB_OKCANCEL);
	if (isok == IDOK)
	{
		ui3();
	}
	else if (isok == IDCANCEL)
	{
		begin();
	}
}
void inverse(int x, int y)
{
	char now = ((huihe == 1) ? 'B' : 'W');
	char op = ((huihe == 1) ? 'W' : 'B');
	for (int i = 1; i <= 8; i++)
	{
		if (flag[i])
		{
			for (int j = 1; j <= 7; j++)
			{
				if (map[x + j * dire[i - 1][0]][y + j * dire[i - 1][1]] == op)
				{
					map[x + j * dire[i - 1][0]][y + j * dire[i - 1][1]] = now;
				}
				else
				{
					break;
				}
			}
		}
	}
}
void print1()	//画棋盘
{
	putimage(480, 30, &totalblack);
	white = 0;
	black = 0;
	int x, y;
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			if (!(x == bestyucem && y == bestyucen))
			{
				switch (map[x][y])
				{
				case 'B':
					putimage(60 * x, 60 * y, &pic[1]);
					black++;
					break;
				case 'W':
					putimage(60 * x, 60 * y, &pic[2]);
					white++;
					break;
				default:
					putimage(60 * x, 60 * y, &pic[0]);
					if (judge(x, y))
					{
						setfillcolor(GREEN);
						fillrectangle(60 * x, 60 * y, 60 * (x + 1), 60 * (y + 1));
					}
					break;
				}
			}
			else
			{
				switch (map[x][y])
				{
				case 'B':
					putimage(60 * x, 60 * y, &pic[1]);
					setfillcolor(YELLOW);
					fillrectangle(60 * x + 25, 60 * y + 25, 60 * (x + 1) - 25, 60 * (y + 1) - 25);
					black++;
					break;
				case 'W':
					putimage(60 * x, 60 * y, &pic[2]);
					setfillcolor(YELLOW);
					fillrectangle(60 * x + 25, 60 * y + 25, 60 * (x + 1) - 25, 60 * (y + 1) - 25);
					white++;
					break;
				}
			}
		}

	}
	putimage(540, 120, &pic[1]);
	putimage(540, 240, &pic[2]);
	if (huihe == 1)
	{
		setlinecolor(RED);
		rectangle(520, 100, 620, 200);
		setlinecolor(BLACK);
		rectangle(520, 220, 620, 320);
	}
	else
	{
		setlinecolor(RED);
		rectangle(520, 220, 620, 320);
		setlinecolor(BLACK);
		rectangle(520, 100, 620, 200);
	}
	getimage(&tempimg, 0, 0, 640, 480);
}
void print2()//计数
{
	putimage(0, 0, &tempimg);
	settextcolor(RGB(52, 255, 51));
	settextstyle(30, 0, "楷体");
	blacktext = to_string(black);
	whitetext = to_string(white);
	huihetext = (huihe == 1) ? "黑" : "白";
	huihetext = huihetext + "子的回合";
	huiheshutext = to_string(huiheshu);
	huiheshutext = "第" + huiheshutext + "回合";
	outtextxy(560, 60, "   ");//覆盖掉前一次的数，解决从两位数到一位数出现bug
	outtextxy(560, 340, "   ");//覆盖掉前一次的数，解决从两位数到一位数出现bug
	outtextxy(560, 440, "   ");
	outtextxy(560, 410, "   ");
	outtextxy(560, 60, blacktext.c_str()); //显示目前棋盘上的黑子数
	outtextxy(560, 340, whitetext.c_str());//显示目前棋盘上的白子数
	outtextxy(480, 440, huihetext.c_str());//显示回合状态 轮到谁下
	outtextxy(480, 410, huiheshutext.c_str());//显示回合数
}
int find()	//找可以下的位置
{
	int cnt = 0;
	int x, y;
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			if (judge(x, y))
			{
				cnt++;
			}
		}
	}
	return cnt;
}
void shubiao()
{
	m = getmessage(EM_MOUSE);
	int x0 = m.x / 60;
	int y0 = m.y / 60;
	switch (m.message)
	{
	case WM_LBUTTONDOWN:
		if (judge(x0, y0))
		{
			inverse(x0, y0);
			map[x0][y0] = ((huihe == 1) ? 'B' : 'W');
			huihe = 1 - huihe;
			huiheshu++;
		}
		else if (m.x <= 480)//不能下的地方误触会标红;
		{
			setfillcolor(RED);
			fillrectangle(60 * x0, 60 * y0, 60 * (x0 + 1), 60 * (y0 + 1));
			Sleep(500);
		}
		break;
	}
}
void chucunhuiqi()
{
	memcpy(huiqimap[huiqiju], map, sizeof(map));
	huiqim[huiqiju] = bestyucem;
	huiqin[huiqiju] = bestyucen;
	huiqihuihe[huiqiju] = huiheshu;
	huiqihei[huiqiju] = black;
	huiqibai[huiqiju] = white;

}
void huiqibutton(int zhizi, button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互	
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(WHITE);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			if (huiqiju != 1)
			{
				memcpy(map, huiqimap[huiqiju - 1], sizeof(map));
				bestyucem = huiqim[huiqiju - 1];
				bestyucen = huiqin[huiqiju - 1];
				huiheshu = huiqihuihe[huiqiju - 1];
				black = huiqihei[huiqiju - 1];
				white = huiqibai[huiqiju - 1];
				huiqiju = huiqiju - 1;
				if (zhizi == 4)huihe = 1 - huihe;
			}
			else
			{
				HWND hndcd1 = GetHWnd();
				int isok;
				isok = MessageBox(hndcd1, "您不能继续悔棋", "提示", MB_OK);
			}
		}
		break;
	}
}
void ui5(int dang)//双人
{
	bestyucem = -1;
	bestyucen = -1;
	black = 2;
	white = 2;
	if (dang == 0)
	{
		memset(map, 0, sizeof(map));
		huihe = 1;
		huiheshu = 1;
		map[3][3] = 'W';
		map[4][4] = 'W';
		map[4][3] = 'B';
		map[3][4] = 'B';
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				map[i][j] = cdmap[dang][i][j];
			}
		}
		huihe = cdmap[dang][1][8];
		huiheshu = cdmap[dang][2][8];
	}
	findflag[0] = 1;
	findflag[1] = 1;
	initgraph(640, 480);
	HWND hnd5 = GetHWnd();//获取窗口句柄
	SetWindowText(hnd5, "双人对战");
	button caidananniu, huiqianniu;
	//菜单按钮
	caidananniu.x1 = 480;
	caidananniu.x2 = 580;
	caidananniu.y1 = 0;
	caidananniu.y2 = 30;
	TCHAR caidantext[1000] = _T("游戏菜单");
	huiqianniu.x1 = 580;
	huiqianniu.x2 = 640;
	huiqianniu.y1 = 0;
	huiqianniu.y2 = 30;
	TCHAR huiqitext[1000] = _T("悔棋");

	while (1)
	{
		huiqiju = huiheshu;
		chucunhuiqi();
		if (find() == 0)
		{
			flag[huihe] = 0;
			huihe = 1 - huihe;
			huiheshu++;
		}
		else
		{
			flag[huihe] = 1;
		}
		if (final())
		{
			print1();
			print2();
			jieguo();
		}
		temphuiheshu = huiheshu;
		shubiao();
		print1();
		print2();
		huiqibutton(4, huiqianniu, huiqitext, 20, 10, 5, "black", "red", "lightmagenta");
		caidanbutton(3, caidananniu, caidantext, 20, 10, 5, "black", "red", "green");
	}
	_getch();

}
void yuceinverse(int x, int y)
{
	char now = ((yucehuihe == 1) ? 'B' : 'W');
	char op = ((yucehuihe == 1) ? 'W' : 'B');
	for (int i = 1; i <= 8; i++)
	{
		if (yuceflag[i])
		{
			for (int j = 1; j <= 7; j++)
			{
				if (yucemap[x + j * dire[i - 1][0]][y + j * dire[i - 1][1]] == op)
				{
					yucemap[x + j * dire[i - 1][0]][y + j * dire[i - 1][1]] = now;
				}
				else
				{
					break;
				}
			}
		}
	}
}
bool yucejudge(int x, int y)
{
	if (yucemap[x][y] == 'W' || yucemap[x][y] == 'B')return false;
	char now = ((yucehuihe == 1) ? 'B' : 'W');
	char op = ((yucehuihe == 1) ? 'W' : 'B');
	yuceflag[1] = 0;//右方
	yuceflag[2] = 0;//左方
	yuceflag[3] = 0;//上方
	yuceflag[4] = 0;//下方
	yuceflag[5] = 0;//左上
	yuceflag[6] = 0;//左下
	yuceflag[7] = 0;//右下
	yuceflag[8] = 0;//右上
	for (int i = 1; i <= 8; i++)
	{
		int j = 1;
		if (checkhefa(x + dire[i - 1][0], y + dire[i - 1][1]) && yucemap[x + dire[i - 1][0]][y + dire[i - 1][1]] == op)
		{
			for (j = 2; j <= 7; j++)
			{
				if (!checkhefa(x + j * dire[i - 1][0], y + j * dire[i - 1][1]))break;
				else if (yucemap[x + j * dire[i - 1][0]][y + j * dire[i - 1][1]] != 'W' && yucemap[x + j * dire[i - 1][0]][y + j * dire[i - 1][1]] != 'B')//空
				{
					break;
				}
				else if (yucemap[x + j * dire[i - 1][0]][y + j * dire[i - 1][1]] == now)
				{
					yuceflag[i] = true;
					break;
				}
			}
		}
		else continue;
	}
	return(yuceflag[1] || yuceflag[2] || yuceflag[3] || yuceflag[4] || yuceflag[5] || yuceflag[6] || yuceflag[7] || yuceflag[8]);
	return(yuceflag[1] || yuceflag[2] || yuceflag[3] || yuceflag[4] || yuceflag[5] || yuceflag[6] || yuceflag[7] || yuceflag[8]);
}
bool yucefinal()
{
	if (blackyuce + whiteyuce == 64)return true;//下满
	if (blackyuce == 0 || whiteyuce == 0)return true;//吃完
	if (findflagyuce[0] == 0 && findflagyuce[1] == 0)return true;//不能再下
	return false;
}
void yucetj()//统计场上黑白子数
{
	blackyuce = 0;
	whiteyuce = 0;
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (yucemap[i][j] == 'B')blackyuce++;
			else if (yucemap[i][j] == 'W')whiteyuce++;
		}
	}
}
int evaluation1()//人机对应huihe 权值表
{
	int valuesum = 0;
	char mine = (huihe == 1) ? 'B' : 'W';
	char op = (huihe == 1) ? 'W' : 'B';
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (yucemap[i][j] == mine)
			{
				valuesum += quanzhi[i][j];
			}
			else if (yucemap[i][j] == op)
			{
				valuesum -= quanzhi[i][j];
			}
		}
	}
	return valuesum;
}
bool isstable(int x, int y)
{
	for (int i = 0; i <= 7; i++)
	{
		int tempx = x + dire[i][0];
		int tempy = x + dire[i][0];
		while (tempx <= 7 && tempx >= 0 && tempy <= 7 && tempy >= 0)
		{
			if (yucemap[tempx][tempy] != 'B' && yucemap[tempx][tempy] != 'W')return false;
			tempx += dire[i][0];
			tempy += dire[i][1];
		}
	}
	return true;
}
int evaluation2()//人机对应huihe 稳定子
{
	int valuesum = 0;
	char mine = (huihe == 1) ? 'B' : 'W';
	int wendingcnt1 = 0;
	int wendingcnt2 = 0;
	if (yucemap[0][0] == mine)wendingcnt1++;
	if (yucemap[0][7] == mine)wendingcnt1++;
	if (yucemap[7][0] == mine)wendingcnt1++;
	if (yucemap[7][7] == mine)wendingcnt1++;
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (isstable(i, j))
			{
				if (i == 0 || i == 7 || j == 0 || j == 7)
				{
					wendingcnt1 = (yucemap[i][j] == mine) ? wendingcnt1 + 1 : wendingcnt1 - 1;
				}
				else
				{
					wendingcnt2 = (yucemap[i][j] == mine) ? wendingcnt2 + 1 : wendingcnt2 - 1;
				}
			}
		}
	}
	valuesum = 20 * wendingcnt1 + 10 * wendingcnt2;
	return valuesum;
}
int minmax(int ceng, int ycalpha, int ycbeta)
{
	//	int tempalpha = INT_MIN;//继承父节点
	//	int tempbeta = INT_MAX;//继承父节点
	yucetj();
	yucekexia yucekexingwei[64];
	int yucelist = 0;
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (yucejudge(i, j))
			{
				yucelist++;
				yucekexingwei[yucelist].x = i;
				yucekexingwei[yucelist].y = j;
				for (int p = 1; p <= 8; p++)
				{
					yucekexingwei[yucelist].yucekexiaflag[p] = yuceflag[p];
				}
			}
		}
	}
	if (yucefinal() || ceng == 0)//如果搜到结束 huihe对应max 1-huihe对应min  max 改变 aphla min 改变 beta
	{
		int yucevalue = 0;
		if (guzhijieduan <= 2)
		{
			yucevalue = (yucehuihe == huihe) ? evaluation1() + 5 * yucelist : evaluation1() - 5 * yucelist;
		}
		else if (guzhijieduan == 3)//增加稳定子判定
		{
			yucevalue = (yucehuihe == huihe) ? evaluation1() + evaluation2() + 5 * yucelist : evaluation2() + evaluation1() - 5 * yucelist;
		}
		else //看最后是否胜利
		{
			yucevalue = (huihe == 1) ? blackyuce : whiteyuce;
		}
		return yucevalue;
	}

	if (yucehuihe == huihe)//预测ai下 需要max
	{
		if (yucelist == 0)
		{
			findflagyuce[huihe] = 0;
			yucehuihe = 1 - huihe;
			minmax(ceng - 1, ycalpha, ycbeta);
		}
		else
		{
			findflagyuce[huihe] = 1;
			int maxfinal = INT_MIN;
			for (int i2 = 1; i2 <= yucelist; i2++)
			{
				yucehuihe = huihe;
				char yucelinshimap[8][8];
				memcpy(yucelinshimap, yucemap, sizeof(yucemap));
				int linshifindflagyuce[2];
				memcpy(linshifindflagyuce, findflagyuce, sizeof(findflagyuce));
				yucemap[yucekexingwei[i2].x][yucekexingwei[i2].y] = (yucehuihe == 1) ? 'B' : 'W';
				memcpy(yuceflag, yucekexingwei[i2].yucekexiaflag, sizeof(yuceflag));
				yuceinverse(yucekexingwei[i2].x, yucekexingwei[i2].y);
				yucehuihe = 1 - yucehuihe;

				maxfinal = max(maxfinal, minmax(ceng - 1, ycalpha, ycbeta));
				ycalpha = max(ycalpha, maxfinal);
				if (maxfinal > ycbeta)break;

				memcpy(findflagyuce, linshifindflagyuce, sizeof(findflagyuce));
				memcpy(yucemap, yucelinshimap, sizeof(yucemap));

				yucehuihe = huihe;
			}
			return maxfinal;

		}
	}
	else//预测人下 需要min
	{
		if (yucelist == 0)
		{
			findflagyuce[1 - huihe] = 0;
			yucehuihe = huihe;
			minmax(ceng - 1, ycalpha, ycbeta);
		}
		else
		{
			findflagyuce[1 - huihe] = 1;
			int minfinal = INT_MAX;
			for (int i2 = 1; i2 <= yucelist; i2++)
			{
				yucehuihe = 1 - huihe;
				char yucelinshimap[8][8];
				memcpy(yucelinshimap, yucemap, sizeof(yucemap));
				int linshifindflagyuce[2];
				memcpy(linshifindflagyuce, findflagyuce, sizeof(findflagyuce));
				yucemap[yucekexingwei[i2].x][yucekexingwei[i2].y] = (yucehuihe == 1) ? 'B' : 'W';
				memcpy(yuceflag, yucekexingwei[i2].yucekexiaflag, sizeof(yuceflag));
				yuceinverse(yucekexingwei[i2].x, yucekexingwei[i2].y);
				yucehuihe = 1 - yucehuihe;

				minfinal = min(minfinal, minmax(ceng - 1, ycalpha, ycbeta));
				ycbeta = min(ycbeta, minfinal);
				if (minfinal < ycalpha)break;

				//if (minmaxtemp < tempalpha)break;//beta为上界
				//else tempbeta = min(minmaxtemp, tempbeta);
				memcpy(yucemap, yucelinshimap, sizeof(yucemap));
				memcpy(findflagyuce, linshifindflagyuce, sizeof(findflagyuce));
				yucehuihe = 1 - huihe;
			}
			return minfinal;

		}
	}
}
void ai5() //minmax+ alpha beta预搜索
{
	// 阶段1 初局阶段 增加搜索层数
	// 阶段2 前中期
	// 阶段3 中后阶段 增加稳定点判定
	// 阶段4 结局阶段 搜索模拟到结束
	if (huiheshu <= 10)
	{
		sousuoceng = 6;
		guzhijieduan = 1;
	}
	else if (huiheshu <= 40)
	{
		sousuoceng = 5;
		guzhijieduan = 2;
	}
	else if (huiheshu <= 50)
	{
		sousuoceng = 6;
		guzhijieduan = 3;
	}
	else
	{
		sousuoceng = 20;
		guzhijieduan = 4;
	}
	bestyucem = -1;
	bestyucen = -1;
	bestquan = INT_MIN;
	for (int q = 0; q <= 7; q++)
	{
		for (int n = 0; n <= 7; n++)
		{
			if (judge(q, n))
			{
				memset(minmaxceng, 0, sizeof(minmaxceng));
				map[q][n] = ((huihe == 1) ? 'B' : 'W');//ai尝试下在q，n
				yucehuihe = 1 - huihe;
				memcpy(yucemap, map, sizeof(map));;//所有的模拟在yucemap上做
				findflagyuce[0] = 1;
				findflagyuce[1] = 1;
				int tempquan = minmax(sousuoceng - (5 - difficult), INT_MIN, INT_MAX);
				map[q][n] = 0;//退回一步
				if (tempquan >= bestquan)
				{
					bestyucem = q;
					bestyucen = n;
					bestquan = tempquan;
					for (int k = 1; k <= 8; k++)
					{
						ai4flag[k] = flag[k];
					}
				}
			}
		}
	}
	for (int k = 1; k <= 8; k++)
	{
		flag[k] = ai4flag[k];
	}
	inverse(bestyucem, bestyucen);
	map[bestyucem][bestyucen] = ((huihe == 1) ? 'B' : 'W');
	huihe = 1 - huihe;
	huiheshu++;
}
void ui6(int dang, int zhizi)//人机对战,执子表示玩家选择1黑方，0白方
{
	if (dang == 0)
	{
		bestyucem = -1;
		bestyucen - 1;
		black = 2;
		white = 2;
		huiqiflag = true;
		huiqiju = 0;
		memset(map, 0, sizeof(map));
		huihe = 1;
		huiheshu = 1;
		map[3][3] = 'W';
		map[4][4] = 'W';
		map[4][3] = 'B';
		map[3][4] = 'B';
	}
	else if (dang == 1 || dang == 2 || dang == 3)
	{
		black = 2;
		white = 2;
		bestyucem = -1;
		bestyucen = -1;
		huiqiflag = true;
		huiqiju = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				map[i][j] = cdmap[dang][i][j];
			}
		}
		huihe = cdmap[dang][1][8];
		huiheshu = cdmap[dang][2][8];
		difficult = cdmap[dang][3][8];
	}
	findflag[0] = 1;
	findflag[1] = 1;
	initgraph(640, 480);
	HWND hnd6 = GetHWnd();//获取窗口句柄
	SetWindowText(hnd6, "人机对战");
	button caidananniu, huiqianniu;
	//菜单按钮
	caidananniu.x1 = 480;
	caidananniu.x2 = 580;
	caidananniu.y1 = 0;
	caidananniu.y2 = 30;
	TCHAR caidantext[1000] = _T("游戏菜单");
	huiqianniu.x1 = 580;
	huiqianniu.x2 = 640;
	huiqianniu.y1 = 0;
	huiqianniu.y2 = 30;
	TCHAR huiqitext[1000] = _T("悔棋");
	while (1)
	{
		if (find() == 0)
		{
			findflag[huihe] = 0;
			huihe = 1 - huihe;
			huiheshu++;
		}
		else
		{
			findflag[huihe] = 1;
		}
		if (final())
		{
			print1();
			print2();
			jieguo();
		}
		else if (huiheshu >= 65)
		{
			print1();
			print2();
			jieguo();
		}
		if (huihe == zhizi)
		{
			if (huiqiflag)
			{
				huiqiju++;
				chucunhuiqi();
				huiqiflag = false;
			}
			shubiao();
		}
		else
		{
			ai5();
			huiqiflag = true;
		}
		print1();
		print2();
		caidanbutton(zhizi, caidananniu, caidantext, 20, 10, 5, "black", "red", "green");
		huiqibutton(zhizi, huiqianniu, huiqitext, 20, 10, 5, "black", "red", "lightmagenta");
	}
	_getch();

}
void xhbutton(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui3人机对战
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			ui6(0, 1);
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void xbbutton(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui3双人对战
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			ui6(0, 0);
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void fanhui2button(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui2存档
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			ui3();
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void ui4()//人机选择先手还是后手
{
	initgraph(1208, 807, EX_SHOWCONSOLE);
	HWND hnd4 = GetHWnd();//获取窗口句柄
	SetWindowText(hnd4, "人机对战");
	putimage(0, 0, &background);
	button xuanhei, xuanbai;
	//选择黑方，先手
	xuanhei.x1 = 450;
	xuanhei.x2 = 600;
	xuanhei.y1 = 220;
	xuanhei.y2 = 250;
	TCHAR xhtext[1000] = _T("选择黑子先行");
	//选择白方，后手
	xuanbai.x1 = 450;
	xuanbai.x2 = 600;
	xuanbai.y1 = 280;
	xuanbai.y2 = 310;
	TCHAR xbtext[1000] = _T("选择白子后手");
	button music;
	//音乐播放按钮
	music.x1 = 0;
	music.x2 = 100;
	music.y1 = 0;
	music.y2 = 30;
	TCHAR musictext[1000] = _T("音乐开关");
	button fanhui2;
	//返回按钮
	fanhui2.x1 = 500;
	fanhui2.x2 = 560;
	fanhui2.y1 = 400;
	fanhui2.y2 = 430;
	TCHAR fanhui2text[1000] = _T("返回");
	while (1)
	{
		fanhui2button(fanhui2, fanhui2text, 20, 10, 5, "black", "lightmagenta", "cyan");
		bgmbutton(music, musictext, 20, 10, 5, "black", "red", "green");
		//(按钮，文本，文本长度，文本宽度，间距，文本颜色，边框颜色，填充颜色)
		xhbutton(xuanhei, xhtext, 20, 10, 5, "black", "lightmagenta", "cyan");
		xbbutton(xuanbai, xbtext, 20, 10, 5, "black", "lightmagenta", "cyan");
	}
	_getch();
}
void nandu1button(int zhizi, button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(GREEN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			difficult = 1;//简单
			ui4();
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void nandu2button(int zhizi, button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(GREEN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			difficult = 3;//普通
			ui4();
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void nandu3button(int zhizi, button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(GREEN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			difficult = 4;//困难
			ui4();
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void fanhui5button(int zhizi, button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			ui3();
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void nanduui()
{

	initgraph(1208, 807, EX_SHOWCONSOLE);
	HWND hndcd = GetHWnd();//获取窗口句柄
	SetWindowText(hndcd, "难度选择");
	putimage(0, 0, &background);
	button nanduwei[4];
	//难度一
	nanduwei[1].x1 = 500;
	nanduwei[1].x2 = 560;
	nanduwei[1].y1 = 220;
	nanduwei[1].y2 = 250;
	TCHAR ndw1text[1000] = _T("简单");
	//难度二
	nanduwei[2].x1 = 500;
	nanduwei[2].x2 = 560;
	nanduwei[2].y1 = 280;
	nanduwei[2].y2 = 310;
	TCHAR ndw2text[1000] = _T("普通");
	//难度三
	nanduwei[3].x1 = 500;
	nanduwei[3].x2 = 560;
	nanduwei[3].y1 = 340;
	nanduwei[3].y2 = 370;
	TCHAR ndw3text[1000] = _T("困难");
	button fanhui5;
	//返回按钮
	fanhui5.x1 = 500;
	fanhui5.x2 = 560;
	fanhui5.y1 = 400;
	fanhui5.y2 = 430;
	TCHAR fanhui5text[1000] = _T("返回");
	button music;
	//音乐播放按钮
	music.x1 = 0;
	music.x2 = 100;
	music.y1 = 0;
	music.y2 = 30;
	TCHAR musictext[1000] = _T("音乐开关");
	while (1)
	{
		//(按钮，文本，文本长度，文本宽度，间距，文本颜色，边框颜色，填充颜色)
		fanhui5button(0, fanhui5, fanhui5text, 20, 10, 5, "black", "lightmagenta", "cyan");
		nandu1button(0, nanduwei[1], ndw1text, 20, 10, 5, "black", "green", "cyan");
		nandu2button(0, nanduwei[2], ndw2text, 20, 10, 5, "black", "green", "cyan");
		nandu3button(0, nanduwei[3], ndw3text, 20, 10, 5, "black", "green", "cyan");
		bgmbutton(music, musictext, 20, 10, 5, "black", "red", "green");
	}
	_getch();
}
void rjbutton(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui3人机对战
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			nanduui();
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void srbutton(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui3双人对战
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			ui5(0);
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void fanhui1button(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui2存档
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			ui2();
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void ui3()//游戏模式选择
{
	initgraph(1208, 807, EX_SHOWCONSOLE);
	HWND hnd3 = GetHWnd();//获取窗口句柄
	SetWindowText(hnd3, "新的开始");
	putimage(0, 0, &background);
	button rj, sr;
	//人机对战
	rj.x1 = 500;
	rj.x2 = 600;
	rj.y1 = 220;
	rj.y2 = 250;
	TCHAR rjtext[1000] = _T("人机对战");
	//双人对战
	sr.x1 = 500;
	sr.x2 = 600;
	sr.y1 = 280;
	sr.y2 = 310;
	TCHAR srtext[1000] = _T("双人对战");
	button music;
	//音乐播放按钮
	music.x1 = 0;
	music.x2 = 100;
	music.y1 = 0;
	music.y2 = 30;
	TCHAR musictext[1000] = _T("音乐开关");
	button fanhui1;
	//返回按钮
	fanhui1.x1 = 525;
	fanhui1.x2 = 575;
	fanhui1.y1 = 400;
	fanhui1.y2 = 430;
	TCHAR fanhui1text[1000] = _T("返回");
	while (1)
	{
		fanhui1button(fanhui1, fanhui1text, 20, 10, 5, "black", "lightmagenta", "cyan");
		bgmbutton(music, musictext, 20, 10, 5, "black", "red", "green");
		//(按钮，文本，文本长度，文本宽度，间距，文本颜色，边框颜色，填充颜色)
		rjbutton(rj, rjtext, 20, 10, 5, "black", "lightmagenta", "cyan");
		srbutton(sr, srtext, 20, 10, 5, "black", "lightmagenta", "cyan");
	}
	_getch();
}
void cdui();
void xksbutton(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui2新开始
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			ui3();
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void xcd1button(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui2存档
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			fin.open("..\\saved\\存档一.txt");
			if (fin.is_open() == false)
			{
				HWND hndcd3 = GetHWnd();
				int isok;
				isok = MessageBox(hndcd3, "存档一不存在", "提示", MB_OK);
				if (isok == IDOK)
				{
					cdui();
				}
			}
			else
			{
				string tempdu;
				getline(fin, tempdu);
				cdmap[1][0][8] = stoi(tempdu);
				getline(fin, tempdu);
				cdmap[1][1][8] = stoi(tempdu);
				getline(fin, tempdu);
				cdmap[1][2][8] = stoi(tempdu);
				getline(fin, tempdu);
				cdmap[1][3][8] = stoi(tempdu);
				for (int i = 0; i < 8; i++)
				{
					getline(fin, tempdu);
					for (int j = 0; j < 8; j++)
					{
						cdmap[1][i][j] = tempdu[j];
					}
				}
				fin.close();
				if (cdmap[1][0][8] != 3)ui6(1, cdmap[1][0][8]);
				else ui5(1);
			}
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void xcd2button(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui2存档
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			fin.open("..\\saved\\存档二.txt");
			if (fin.is_open() == false)
			{
				HWND hndcd3 = GetHWnd();
				int isok;
				isok = MessageBox(hndcd3, "存档二不存在", "提示", MB_OK);
				if (isok == IDOK)
				{
					cdui();
				}
			}
			else
			{
				string tempdu;
				getline(fin, tempdu);
				cdmap[2][0][8] = stoi(tempdu);//zhizu
				getline(fin, tempdu);
				cdmap[2][1][8] = stoi(tempdu);//huihe
				getline(fin, tempdu);
				cdmap[2][2][8] = stoi(tempdu);//huiheshu
				getline(fin, tempdu);
				cdmap[2][3][8] = stoi(tempdu);//difficult
				for (int i = 0; i < 8; i++)
				{
					getline(fin, tempdu);
					for (int j = 0; j < 8; j++)
					{
						cdmap[2][i][j] = tempdu[j];
					}
				}
				fin.close();
				if (cdmap[2][0][8] != 3)ui6(2, cdmap[2][0][8]);
				else ui5(2);
			}
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void xcd3button(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui2存档
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			fin.open("..\\saved\\存档三.txt");
			if (fin.is_open() == false)
			{
				HWND hndcd3 = GetHWnd();
				int isok;
				isok = MessageBox(hndcd3, "存档三不存在", "提示", MB_OK);
				if (isok == IDOK)
				{
					cdui();
				}
			}
			else
			{
				string tempdu;
				getline(fin, tempdu);
				cdmap[3][0][8] = stoi(tempdu);
				getline(fin, tempdu);
				cdmap[3][1][8] = stoi(tempdu);
				getline(fin, tempdu);
				cdmap[3][2][8] = stoi(tempdu);
				getline(fin, tempdu);
				cdmap[3][3][8] = stoi(tempdu);
				for (int i = 0; i < 8; i++)
				{
					getline(fin, tempdu);
					for (int j = 0; j < 8; j++)
					{
						cdmap[3][i][j] = tempdu[j];
					}
				}
				fin.close();
				if (cdmap[3][0][8] != 3)ui6(3, cdmap[3][0][8]);
				else ui5(3);
			}
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void fanhuibutton(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui2存档
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			ui2();
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void cdui()//读取存档
{
	initgraph(1208, 807, EX_SHOWCONSOLE);
	HWND hndcd = GetHWnd();//获取窗口句柄
	SetWindowText(hndcd, "存档选择");
	putimage(0, 0, &background);
	button xcd[4];
	//存档一
	xcd[1].x1 = 500;
	xcd[1].x2 = 600;
	xcd[1].y1 = 220;
	xcd[1].y2 = 250;
	TCHAR xcd1text[1000] = _T("存档一");
	//存档二
	xcd[2].x1 = 500;
	xcd[2].x2 = 600;
	xcd[2].y1 = 280;
	xcd[2].y2 = 310;
	TCHAR xcd2text[1000] = _T("存档二");
	//存档三
	xcd[3].x1 = 500;
	xcd[3].x2 = 600;
	xcd[3].y1 = 340;
	xcd[3].y2 = 370;
	TCHAR xcd3text[1000] = _T("存档三");
	button music;
	//音乐播放按钮
	music.x1 = 0;
	music.x2 = 100;
	music.y1 = 0;
	music.y2 = 30;
	TCHAR musictext[1000] = _T("音乐开关");
	button fanhui;
	//返回按钮
	fanhui.x1 = 500;
	fanhui.x2 = 600;
	fanhui.y1 = 400;
	fanhui.y2 = 430;
	TCHAR fanhuitext[1000] = _T("返回");
	while (1)
	{
		//(按钮，文本，文本长度，文本宽度，间距，文本颜色，边框颜色，填充颜色)
		bgmbutton(music, musictext, 20, 10, 5, "black", "red", "green");
		fanhuibutton(fanhui, fanhuitext, 20, 10, 5, "black", "lightmagenta", "cyan");
		xcd1button(xcd[1], xcd1text, 20, 10, 5, "black", "lightmagenta", "cyan");
		xcd2button(xcd[2], xcd2text, 20, 10, 5, "black", "lightmagenta", "cyan");
		xcd3button(xcd[3], xcd3text, 20, 10, 5, "black", "lightmagenta", "cyan");
	}
	_getch();
}
void cdbutton(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui2存档
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			cdui();
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void tcbutton(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)//ui2退出
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变红色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(RED);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void ui2()
{
	initgraph(1208, 807, EX_SHOWCONSOLE);
	HWND hnd2 = GetHWnd();//获取窗口句柄
	SetWindowText(hnd2, "黑白棋游戏");
	putimage(0, 0, &background);
	button xinkaishi, cundang, tuichu;
	//新开始
	xinkaishi.x1 = 500;
	xinkaishi.x2 = 600;
	xinkaishi.y1 = 220;
	xinkaishi.y2 = 250;
	TCHAR xkstext[1000] = _T("新的开始");
	//读存档
	cundang.x1 = 500;
	cundang.x2 = 600;
	cundang.y1 = 280;
	cundang.y2 = 310;
	TCHAR cdtext[1000] = _T("读取存档");
	//退出游戏
	tuichu.x1 = 500;
	tuichu.x2 = 600;
	tuichu.y1 = 340;
	tuichu.y2 = 370;
	TCHAR tctext[1000] = _T("退出游戏");
	button music;
	//音乐播放按钮
	music.x1 = 0;
	music.x2 = 100;
	music.y1 = 0;
	music.y2 = 30;
	TCHAR musictext[1000] = _T("音乐开关");
	while (1)
	{
		//(按钮，文本，文本长度，文本宽度，间距，文本颜色，边框颜色，填充颜色)
		bgmbutton(music, musictext, 20, 10, 5, "black", "red", "green");
		xksbutton(xinkaishi, xkstext, 20, 10, 5, "black", "lightmagenta", "cyan");
		cdbutton(cundang, cdtext, 20, 10, 5, "black", "lightmagenta", "cyan");
		tcbutton(tuichu, tctext, 20, 10, 5, "black", "lightmagenta", "cyan");
	}
	_getch();
}
void startbutton(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变绿色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(LIGHTCYAN);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			closegraph();
			ui2();
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void finishbutton(button a, TCHAR text[1000], int tlength, int twidth, int textoff, string textcolor, string boxcolor, string fillcolor)
{
	setbutton(a, text, tlength, twidth, textoff, textcolor, boxcolor, fillcolor);
	//鼠标函数响应交互
	int change = 10;
	m = getmessage(EM_MOUSE);
	switch (m.message)
	{
	case WM_LBUTTONDOWN://鼠标左键点击变红色
		if (m.x >= a.x1 && m.x <= a.x2 && m.y >= a.y1 && m.y <= a.y2)
		{
			setfillcolor(RED);
			fillrectangle(a.x1, a.y1, a.x2, a.y2);
			FlushBatchDraw();//批量绘制
			Sleep(500);
			mciSendString("close ..\\source\\fanyu.mp3", NULL, 0, NULL);
			closegraph();
		}
		break;
	}
	setlinecolor(WHITE);
	setfillcolor(WHITE);
}
void begin() {
	initgraph(1208, 807, EX_SHOWCONSOLE);
	HWND hnd1 = GetHWnd();//获取窗口句柄
	SetWindowText(hnd1, "初始界面");//设置窗口标题
	putimage(0, 0, &background);
	//按钮
	button start, finish;
	//开始按钮
	start.x1 = 450;
	start.x2 = 600;
	start.y1 = 220;
	start.y2 = 280;
	TCHAR starttext[1000] = _T("开始游戏");
	//结束按钮
	finish.x1 = 450;
	finish.x2 = 600;
	finish.y1 = 330;
	finish.y2 = 390;
	TCHAR finishtext[1000] = _T("结束游戏");
	button music;
	//音乐播放按钮
	music.x1 = 0;
	music.x2 = 100;
	music.y1 = 0;
	music.y2 = 30;
	TCHAR musictext[1000] = _T("音乐开关");
	musicflag = 1;
	mciSendString("open ..\\source\\fanyu.mp3", NULL, 0, NULL);
	mciSendString("play ..\\source\\fanyu.mp3", NULL, 0, NULL);
	settextcolor(LIGHTGRAY);
	settextstyle(70, 40, "楷体");
	string begintext = "黑白棋游戏";
	outtextxy(340, 100, begintext.c_str());
	while (1)
	{
		bgmbutton(music, musictext, 20, 10, 5, "black", "red", "green");
		//(按钮，文本，文本长度，文本宽度，间距，文本颜色，边框颜色，填充颜色)
		finishbutton(finish, finishtext, 20, 15, 20, "black", "lightmagenta", "cyan");
		startbutton(start, starttext, 20, 15, 20, "black", "lightmagenta", "cyan");
	}
	_getch();
}
int main()
{
	pictrueload();
	begin();
	return 0;
}