#pragma once
#include<stdbool.h>
#include<SDL2/SDL_events.h>
//struct Window;
//typedef struct Window Window;
struct SDL_Window;
typedef struct SDL_Window SDL_Window;
struct SDL_Renderer;
typedef struct SDL_Renderer SDL_Renderer;


typedef void(*FunEventCallBack)(SDL_Event* ev);
/* @窗口*/
typedef struct Window
{
	SDL_Window* window;
	SDL_Renderer* render;
	//设置事件处理函数
	void (*setEventCallBack)(FunEventCallBack eventhand);
}Window;

//创建窗口
Window* createWindow(int w, int h);
//等待窗口销毁 true销毁 false不销毁
void waitWindowDestroy();

typedef  int Image;
/* @绘图*/
typedef struct Painter
{
	//设置属性
	void (*setColor)(Uint8  r, Uint8  g, Uint8  b, Uint8  a);
	//绘制函数
	void (*clear)();
	void (*flush)();
	void (*drawPoint)(int x, int y);
	void (*drawLine)(int x1, int y1, int x2, int y2);
	void (*drawRect)(int left, int top, int right, int bottom);
	void (*fillRect)(int left, int top, int right, int bottom);
	
	void (*drawImage)(int x, int y, Image img);
}Painter;
Painter* createPainter();
