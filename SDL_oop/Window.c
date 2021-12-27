#include "Window.h"
#include<SDL2/SDL.h>

static Window g_window;
static FunEventCallBack g_event;
static Painter g_painter;

//初始化
static bool initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		return false;
	}
	return true;
}
//事件处理，必须重写
static void _event(SDL_Event* ev)
{
	SDL_Log(u8"warning 尚未设置事件处理函数...\n");
}

void _setEventCallBack(FunEventCallBack eventhand)
{
	g_event = eventhand;
}

Window* createWindow(int w, int h)
{
	if (!initSDL())
	{
		SDL_Log(u8"init failed~\n");
		return NULL;
	}

	if (-1 == SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, &g_window.window, &g_window.render))
	{
		return NULL;
	}

	//初始化函数指针
	g_window.setEventCallBack = _setEventCallBack;
	g_event = _event;

	return &g_window;
}

void waitWindowDestroy()
{
	bool isDone = false;
	while (!isDone)
	{
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				isDone = true;
				break;
			default:
				g_event(&ev);
				break;
			}

		}
	}

	SDL_DestroyWindow(g_window.window);
	SDL_DestroyRenderer(g_window.render);
	SDL_Quit();
}


/* @绘图*/
static void clear()
{
	SDL_RenderClear(g_window.window);
}

static void flush()
{
	SDL_RenderPresent(g_window.render);
}

static void drawPoint(int x, int y)
{
	SDL_RenderDrawPoint(g_window.render, x, y);
}
static void drawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLineF(g_window.render, x1, y1, x2, y2);
}
static void drawRect(int left, int top, int right, int bottom)
{
	SDL_RenderDrawRect(g_window.render, &(SDL_Rect){left, top, right - left, bottom - top});
}
static void fillRect(int left, int top, int right, int bottom)
{
	SDL_RenderFillRect(g_window.render, &(SDL_Rect){left, top, right - left, bottom - top});
}

static void drawImage(int x, int y, Image img)
{

}

static void setColor(Uint8  r, Uint8  g, Uint8  b, Uint8  a)
{
	SDL_SetRenderDrawColor(g_window.render, r, g, b, a);
}

Painter* createPainter()
{
	g_painter.setColor = setColor;

	g_painter.drawLine = drawLine;
	g_painter.clear = clear;
	g_painter.drawImage = drawImage;
	g_painter.drawPoint = drawPoint;
	g_painter.drawRect = drawRect;
	g_painter.fillRect = fillRect;
	g_painter.flush = flush;

	return &g_painter;
}
