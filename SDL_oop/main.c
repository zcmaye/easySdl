#include"Window.h"
#include<stdio.h>

void handingEvent(SDL_Event* ev)
{
	printf("hello\n");
}

int main(int argc, char* argv[])
{
	Window*window = createWindow(640, 480);
	window->setEventCallBack(handingEvent);

	Painter* painter = createPainter();
	painter->setColor(255, 0, 0, 200);
	painter->drawRect(0, 0, 50, 50);
	painter->flush();

	waitWindowDestroy();
	return 0;
}