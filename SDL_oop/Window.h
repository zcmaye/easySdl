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
/* @����*/
typedef struct Window
{
	SDL_Window* window;
	SDL_Renderer* render;
	//�����¼�������
	void (*setEventCallBack)(FunEventCallBack eventhand);
}Window;

//��������
Window* createWindow(int w, int h);
//�ȴ��������� true���� false������
void waitWindowDestroy();

typedef  int Image;
/* @��ͼ*/
typedef struct Painter
{
	//��������
	void (*setColor)(Uint8  r, Uint8  g, Uint8  b, Uint8  a);
	//���ƺ���
	void (*clear)();
	void (*flush)();
	void (*drawPoint)(int x, int y);
	void (*drawLine)(int x1, int y1, int x2, int y2);
	void (*drawRect)(int left, int top, int right, int bottom);
	void (*fillRect)(int left, int top, int right, int bottom);
	
	void (*drawImage)(int x, int y, Image img);
}Painter;
Painter* createPainter();
