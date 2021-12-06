#ifdef WIN32
#pragma comment(lib,"/x86/SDL2_image.lib")
#pragma comment(lib,"/x86/SDL2.lib")
#pragma comment(lib,"/x86/SDL2main.lib")
#include<sdl.h>
#include<sdl_image.h>
#else
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#define SDL_KeyCode SDL_Keycode
#endif // WIN32
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<set>
using namespace std;


SDL_Window* win;
SDL_Surface* winsfc;
SDL_Renderer* winRenderer;
int win_w= 480;
int win_h= 760;

/*@ IMAGE*/
typedef struct IMAGE
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	int w ;
	int h ;
}Image;
void loadimage(Image* img, const char* fileName, int w, int h)
{
	img->surface = IMG_Load(fileName);
	img->texture = SDL_CreateTextureFromSurface(winRenderer, img->surface);
	if (w != 0 && h != 0)
	{
		img->w = w;
		img->h = h;
	}
	else
	{
		//获取宽度和高度
		if (SDL_QueryTexture(img->texture, NULL, NULL, &img->w, &img->h))
		{
			SDL_Log("%s SDL_QueryTexture failed %s", fileName, SDL_GetError());
		}
	}
	//释放img->surface 以后使用img->texture即可
	SDL_FreeSurface(img->surface);
	img->surface = NULL;
}
void putimage(int x, int y, Image* img)
{
	SDL_Rect dest ={ x, y, img->w, img->h };
	SDL_RenderCopy(winRenderer, img->texture, NULL, &dest);
}
void unloadimage(Image* img)
{
	SDL_DestroyTexture(img->texture);
}

//图片
Image img_bk;		//背景
Image img_player;	//玩家
Image img_bullet;	//子弹
Image img_enemy[2];	//敌机
Image img_gamerover;

//加载资源
void loadResource()
{
	loadimage(&img_bk, "./Resources/img/background.png",0,0);
	loadimage(&img_player, "./Resources/img/hero1.png", 0, 0);
	loadimage(&img_bullet, "./Resources/img/bullet1.png", 0, 0);
	loadimage(img_enemy + 0, "./Resources/img/enemy3_hit.png", 104, 148);
	loadimage(img_enemy + 1,"./Resources/img/enemy1.png", 0, 0);
	loadimage(&img_gamerover, "./Resources/img/gameover1.png", 0, 0);
}
//销毁资源
void destroyResource()
{
	unloadimage(&img_bk);
	unloadimage(&img_player);
	unloadimage(&img_bullet);
	unloadimage(img_enemy);
	unloadimage(img_enemy + 1);
	unloadimage(&img_gamerover);
}
//初始化
bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
	{
		SDL_Log("can not init video,%s", SDL_GetError());
		return false;
	}
	win = SDL_CreateWindow(u8"飞机大战", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_w,win_h, SDL_WINDOW_SHOWN);
	if (!win)
	{
		SDL_Log("can not create window,%s", SDL_GetError());
		return false;
	}
	winsfc = SDL_GetWindowSurface(win);
	winRenderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	loadResource();
	return true;
}

//游戏部分
enum My
{
	BULLLET_NUM = 15,
	ENEMY_NUM = 10,
	BIG,
	SMALL
};
struct Plance//飞机结构
{
	int x;
	int y;
	bool isLive;
	int width;
	int height;
	int hp;
	int type;//敌机的类型
}player, bull[BULLLET_NUM], enemy[ENEMY_NUM];
void enemyHp(int i)
{
	int flag = rand() % 10;
	if (flag >= 0 && flag <= 2)
	{
		enemy[i].type = BIG;
		enemy[i].hp = 3;
		enemy[i].width = 104;
		enemy[i].height = 148;
	}
	else
	{
		enemy[i].type = SMALL;
		enemy[i].hp = 1;
		enemy[i].width = 52;
		enemy[i].height = 39;
	}
}
void gameInit()
{
	srand(time(NULL));
	player.x = win_w / 2;
	player.y = win_h - 120;
	printf("winsfc %d %d \n", win_w, win_h);
	player.isLive = true;
	//初始化子弹
	for (int i = 0; i < BULLLET_NUM; i++)
	{
		bull[i].x = 0;
		bull[i].y = 0;
		bull[i].isLive = false;
	}
	//初始化敌机
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].isLive = false;
		enemyHp(i);
	}
}

//绘制
void draw()
{
	//绘制背景图
	putimage(0, 0, &img_bk);
	//绘制玩家
	putimage(player.x, player.y, &img_player);
	//退出，写在前面是为了让，死亡画面和文字显示（让程序在运行一次）
	if (player.isLive == false)
	{
		//MessageBox(GetHWnd(), "你死了`", "Over", MB_OKCANCEL);
		putimage((win_w - img_gamerover.w)/2, (win_h - img_gamerover.h) / 2, &img_gamerover);
		//exit(0);
	}
	//printf("player:%d %d \n", player.x, player.y);
	//绘制子弹
	for (int i = 0; i < BULLLET_NUM; i++)
	{
		if (bull[i].isLive)
		{
			putimage(bull[i].x, bull[i].y, &img_bullet);
		}
	}
	//绘制敌机
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].isLive)
		{
			if (enemy[i].type == BIG)
			{
				putimage(enemy[i].x, enemy[i].y, img_enemy);
			}
			else
			{
				putimage(enemy[i].x, enemy[i].y, img_enemy+1);
			}
		}
	}
	//更新图片
	//SDL_UpdateWindowSurface(win);
	SDL_RenderPresent(winRenderer);
}
void createBullet()
{
	for (int i = 0; i < BULLLET_NUM; i++)
	{
		if (!bull[i].isLive)
		{
			bull[i].x = player.x + 60;
			bull[i].y = player.y;
			bull[i].isLive = true;
			break;
		}
	}
}
void BulletMove(int speed)
{
	for (int i = 0; i < BULLLET_NUM; i++)
	{
		if (bull[i].isLive)
		{

			bull[i].y -= speed;
			if (bull[i].y < 0)
			{
				bull[i].isLive = false;
			}

		}
	}
}
bool Timer(Uint32 ms, int id)
{
	static Uint32 beg[10];
	Uint32 end = SDL_GetTicks();
	if (end - beg[id] >= ms)
	{

		beg[id] = end;
		return true;
	}

	return false;
}

set<SDL_Keycode> keycode;
//角色移动

void playerMove(int speed)
{
	if (keycode.find(SDLK_UP) !=keycode.end() && player.y>=0)
	{
		if (player.y > 0)
		{
			player.y -= speed;
		}
	}
	if (keycode.find(SDLK_DOWN) != keycode.end() && player.y+img_player.h <= win_h)
	{
		if (player.y + 120 < win_h)
		{
			player.y += speed;
		}

	}
	if (keycode.find(SDLK_LEFT) != keycode.end() && player.x+img_player.w/2 >= 0)
	{
		if (player.x + 60 > 0)
		{
			player.x -= speed;
		}

	}
	if (keycode.find(SDLK_RIGHT) != keycode.end() && player.x + img_player.w/2 <= win_w)
	{
		if (player.x + 60 < win_h)
		{
			player.x += speed;
		}
	}

	if (keycode.find(SDLK_SPACE) != keycode.end() && Timer(200, 1))
	{
		//创建一个子弹
		createBullet();
	}

}
//敌机的移动
void enemyMove(int speed)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].isLive)
		{
			enemy[i].y += speed;
			if (enemy[i].y > win_h)
			{
				enemy[i].isLive = false;
			}
		}
	}
}
//产生敌机
void createEnemy()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (!enemy[i].isLive)
		{
			enemy[i].isLive = true;
			enemy[i].x = rand() % (win_w-60);
			enemy[i].y = -150;
			enemyHp(i);
			break;
		}
	}
}
void PlayEnemyP()
{
	//1，遍历敌机数组  判断是否存活
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].isLive == 0)
		{
			continue;
		}
		//计算敌机的宽度和高度
		int width = 0, height = 0;
		if (enemy[i].type == BIG)
		{
			width = 100;
			height = 130;
		}
		else if (enemy[i].type == SMALL)
		{
			width = 50;
			height = 30;
		}

		//玩家和敌机是否相撞
		if (player.x + 50 >= enemy[i].x && player.x + 50 <= enemy[i].x + width
			&& player.y > enemy[i].y && player.y < enemy[i].y + height)
		{
			player.isLive = false;
		}
		//2，遍历子弹数组
		for (int k = 0; k < BULLLET_NUM; k++)
		{
			if (bull[k].isLive == 0)
			{
				continue;
			}

			//3，判断子弹是否击中敌机
			if (bull[k].x > enemy[i].x && bull[k].x<enemy[i].x + width
				&& bull[k].y>enemy[i].y && bull[k].y < enemy[i].y + height)
			{
				//4,达到了，属性改变，血量--，存活状态，玩家分数++，
				enemy[i].hp--;
				bull[k].isLive = 0;
			}
			//5，如果血量为0，敌机死亡
			if (enemy[i].hp <= 0)
			{
				enemy[i].isLive = 0;
			}
		}
	}
}
int main(int argc,char*argv[])
{
	if (!init())
	{
		return 1;
	}

	//游戏初始化
	gameInit();

	SDL_Event ev;
	while (true)
	{
		draw();
		if (player.isLive)
		{
			if (Timer(5, 3))
			{
				playerMove(1);
			}
			if (Timer(3, 5))
			{
				BulletMove(1);
			}

			if (Timer(500, 0))
			{
				createEnemy();
			}
			if (Timer(10, 2))
			{
				enemyMove(1);
			}
			//playPlance();
			PlayEnemyP();
		}
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				destroyResource();
				exit(0);
				break;
			case SDL_KEYDOWN:
				if (!player.isLive)	//玩家挂掉之后，按任意键退出
					exit(0);
				keycode.insert(ev.key.keysym.sym);
				break;
			case SDL_KEYUP:
				keycode.erase(ev.key.keysym.sym);
				break;
			default:
				break;
			}
		}

	}
	return 0;
}


/*
* 1,先安装开发包
* sudo apt-get install libsdl2-dev libsdl2-image-dev
* 2,生成可执行程序
* g++ main.cpp  -o planeWars  -lSDL2_image -lSDL2
* 3,运行
* ./planeWars
*/