#include"easySdl.h"

Image snow;
//#include<easyx.h>
static int x = 0,y;
void keyDeal(int key);
int main(int argc, char* argv[])
{
    
    initgraph(640, 480, SDL_WINDOW_SHOWN);
    setWindowTitle("我的Sdl窗口");
    setbkcolor(White);
    loadimage(&snow, "千仞雪.jpg", 0, 0);
    
    SDL_CreateWindow("subWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 460, 300, SDL_WINDOW_SHOWN);  

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
        putimage(50, 50, &snow);  
        
        //fillRect(x, y, 100, 100, argb(200, Green));
       // line(50, 50, 250, 250,Red);
        //outtextxy(50, 50, "hello 你好");
        //outtextxy(100, 250, "我是顽石老师");
       
        //settextstyle(26,0,"font/simhei.ttf");
        //settextcolor(argb(255, Red));

        for (size_t i = 0; i < 100; i++)
        {
            putpixel(30 + i, 30, Red);
        }
      
        //SDL_Log("color %x\n",getpixel(100, 100));

        line(50, 50, 100, 100);
        rectangle(0, 0, 20, 20);
        fillrectangle(30, 0, 20, 20);
        setfillcolor(Red);
        solidrectangle(60, 0, 20, 20);
        
        circle(110,20, 20);
        solidcircle(150, 20, 20);
        fillcircle(190, 20, 20);
        //ellipse(300, 0, 300 + 60, 30);
        //ellipse(300, 0, 300 + 10, 5);

        setlinecolor(Green);
        drawEllipse(250, 250, 60, 30);

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



