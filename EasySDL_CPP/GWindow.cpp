#include "GWindow.h"


GWindow::GWindow(int width, int height, Uint32 flags)
	:_x(SDL_WINDOWPOS_UNDEFINED),_y(SDL_WINDOWPOS_UNDEFINED)
	,_size(width,height)
{
	_window = SDL_CreateWindow("GWidget", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

GWindow::~GWindow()
{
}

SDL_Renderer* GWindow::renderer()
{
	return _renderer;
}

void GWindow::update()
{
	SDL_RenderPresent(_renderer);
}
