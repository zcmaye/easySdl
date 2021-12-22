#include"GWidget.h"
#include"GWindow.h"
#include<easyx.h>
int main(int argc,char*argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	GWindow w(640,480);

	static SDL_Event ev;
	while (true)
	{
		w.update();
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				exit(0);
				break;
			default:
				break;
			}
		}
	}
	return 0;
}