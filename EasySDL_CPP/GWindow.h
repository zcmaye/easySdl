#pragma once
#include"GConfigure.h"
#include"GSize.h"
class GWindow
{
public:
	GWindow(int width,int height, Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	virtual ~GWindow();
	SDL_Renderer* renderer();	//获取渲染器
	void update();				//更新窗口
protected:
	int _x;
	int _y;
	GSize _size;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};

