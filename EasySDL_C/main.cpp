#include<stdio.h>
#include"easySdl.h"
//#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
int map[5][8];//地图数组
void InsertMap()//创造地图，随机生成1-4的值，存入数组
{
	srand((unsigned int)time(0));
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			map[i][j] = rand() % 4 + 1;
		}
	}
}
struct _Board//地图下方的板的结构
{
	int x;
	int y;
	COLORREF Color;
	int speed;
}Board;
struct _Board BlueBoard = { 325,570,LightBlue,10};
void InsertBlock()//创建砖块
{
	int x, y;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			x = 100 * j;
			y = 25 * i;
			switch (map[i][j])
			{
			case 1:
				setlinecolor(LightCyan);
				setfillcolor(Green);
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 2:
				setlinecolor(LightCyan);
				setfillcolor(Red);
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 3:
				setlinecolor(LightCyan);
				setfillcolor(Magenta);
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 4:
				setlinecolor(LightCyan);
				setfillcolor(Blue);
				fillrectangle(x, y, x + 100, y + 25);
				break;
			case 0:
				break;
			}

		}
	}

}
void InitBoard()//绘画地图下方的板
{
	setfillcolor(BlueBoard.Color);
	fillrectangle(BlueBoard.x, BlueBoard.y, BlueBoard.x + 150, BlueBoard.y + 25);
}
void MoveBoard()//用户交互，移动板
{
	if ((GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT))&&BlueBoard.x>=0)
	{
		BlueBoard.x -= BlueBoard.speed;
	}
	if ((GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))&&BlueBoard.x+150<=800)
	{
		BlueBoard.x += BlueBoard.speed;
	}
}
struct Ball//在地址中发生碰撞的球的结构
{
	int x;
	int y;
	int r;
	COLORREF Color;
	int Dx;
	int Dy;
};
struct Ball CyanBall = { 500,400,10,LightCyan,5,-5};
void InitBall()//绘制球
{
	
	setfillcolor(CyanBall.Color);
	solidcircle(CyanBall.x, CyanBall.y, CyanBall.r);
}
int Reboundball()
{
	if (CyanBall.y + CyanBall.r == BlueBoard.y && (CyanBall.x + CyanBall.r >= BlueBoard.x&&CyanBall.x + CyanBall.r <= BlueBoard.x + 150))
	{
		return 1;
	}
	else
		return 0;

}
int ClearBlock()
{
	int BlockJ = CyanBall.x / 100;
	int BlockI = (CyanBall.y-CyanBall.r)/25;
	if ((BlockJ >= 0 && BlockJ < 8) && (BlockI >= 0&&BlockI < 5) && map[BlockI][BlockJ] != 0)
	{
		map[BlockI][BlockJ] = 0;
		return 1;
	}
	else
		return 0;
}
void Moveball()
{
	CyanBall.x += CyanBall.Dx;
	CyanBall.y += CyanBall.Dy;
	if (CyanBall.x + CyanBall.r == 0 || CyanBall.x+CyanBall.r == 800)
	{
		CyanBall.Dx = -CyanBall.Dx;
	}
	if (Reboundball() || CyanBall.y + CyanBall.r ==0|| ClearBlock())
	{
		CyanBall.Dy = -CyanBall.Dy;
	}
}
int GameOver()
{
	for (int i=0; i < 5; i++)
	{

		for (int j = 0; j < 8; j++)
		{
			if (map[i][j] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}
int GameDie()
{
	if (CyanBall.y-CyanBall.r > 600)
	{
		return 1;
	}
	else
		return 0;
}

struct Board
{
	int x;
	int y;
	int w;
	int h;
	Uint32 color;
}board = { 325,570,200,20,LightBlue};

int main(int argc,char* argv[])
{
	initgraph(800, 600,SDL_WINDOW_SHOWN);
	setbkcolor(White);
	InsertMap();
	ExMessage msg = {0};
	while (1)
	{
		start(50);
		if (peekMessage(&msg))
		{
		    switch (msg.message)
		    {
		    case M_KEYDOWN:
		        break;
		    }
		}
		//setfillcolor(board.color);
		//solidrectangle(board.x, board.y, board.x + board.w, board.y + board.h);

		InsertBlock();
		InitBoard();
		MoveBoard();
		InitBall();
		Moveball();

		delay();
	}
closegraph();
return 0;
}
