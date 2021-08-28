#include"easySdl.h"

Image snow;
//#include<easyx.h>
static int x = 0,y;
void keyDeal(int key);
int main(int argc, char* argv[])
{
    initgraph(640, 480, SDL_WINDOW_SHOWN);
    setbkcolor(White);
    loadImage(&snow, "千仞雪.jpg", 0, 0);

    ExMessage msg = {0};
    while (true)
    {
        start(60);
        if (peekMessage(&msg))
        {
            switch (msg.message)
            {
            case M_KEYDOWN:
                break;
            }
        }            
        putImage(50, 50, &snow);  
        outtextxy(50, 50, "hello 你好",argb(255,Red));     
        fillRect(x, y, 100, 100, argb(20, Green));

        keyDeal(10);
        delay();
    }
    closegraph();
    return 0;
}

void keyDeal(int speed)
{ 
    if (GetAsyncKeyState(VK_UP))
    {
        y-=speed;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        y+= speed;
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        x-= speed;
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
        x+= speed;
    }
}

/*
  switch (msg.message)
            {
            case M_MOUSEMOVE:
                SDL_Log("mouse move (%d,%d)\n", msg.x, msg.y);
                break;
            case M_LBUTTONDOWN:
                SDL_Log("mouse leftdown (%d,%d)\n", msg.x, msg.y);
                break;
            case M_RBUTTONDOWN:
                SDL_Log("mouse rightdown (%d,%d)\n", msg.x, msg.y);
                break;
            case M_MBUTTONDOWN:
                SDL_Log("mouse MIDdown (%d,%d)\n", msg.x, msg.y);
                break;
            case M_MOUSEWHEEL:
                SDL_Log("mouse wheel (%d,%d) %d\n", msg.x, msg.y,msg.wheel);
                break;
            case M_LBUTTONDBLCLK:
                SDL_Log("mouse leftdouble (%d,%d)\n", msg.x, msg.y);
                break;
            case M_KEYDOWN:
                VK_SPACE;
                SDL_Log("vkcode(%d %c)  scancode(%d %c)\n", msg.vkcode, msg.vkcode, msg.scancode, msg.scancode);
                break;
            case M_MINIMIZED:
                SDL_Log("M_MINIMIZED");
                break;
            case M_MAXIMIZED:
                SDL_Log("M_MAXIMIZED");
                break;
            case M_MOVED:
                SDL_Log("M_MOVED");
                break;
            default:
                break;
            }
*/