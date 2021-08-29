#include "easySdl.h"

#define PI 3.1415926

/* 窗口结构体*/
Window *window;

/*@函数申明*/
#define interior	//内存函数
bool loadText(const char* family, int size);

//color -> SDL_Color
#define toSdlColor(color) \
(SDL_Color) {(color >> 16) & 0xff, (color >> 8) & 0xff, (color) & 0xff, color >> 24}
//color -> r g b a
#define toRgbaColor(color) (color >> 16) & 0xff, (color >> 8) & 0xff, (color) & 0xff, color >> 24

static bool init()
{
	if (TTF_Init())
	{
		SDL_Log("ttf init falied %s\n", SDL_GetError());
		return false;
	}
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("init SDL_INIT_VIDEO falied :%s", SDL_GetError());
		return false;
	}
	window = SDL_calloc(1, sizeof(Window));

	loadText("font/simhei.ttf",26);

	return true;
}
static void config()
{
	SDL_SetRenderDrawBlendMode(window->renderer, SDL_BLENDMODE_BLEND);
	window->fontColor = Black;
	window->lineColor = Black;
	window->fillColor = White;
}
void initgraph(int w, int h, int flag)
{
	if (!init())
	{
		SDL_Log("init falied :%s", SDL_GetError());
		return;
	}
	window->w = w;
	window->h = h;
	window->flag = flag | SDL_WINDOW_RESIZABLE;
	window->bkColor = Black;
	SDL_strlcpy(window->title, "easySdl",64);
	window->window =  SDL_CreateWindow(window->title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		window->w, window->h, window->flag);
	if (!window->window)
	{
		SDL_Log("create window failed %s\n",SDL_GetError());
		return;
	}

	window->winSurface = SDL_GetWindowSurface(window->window);
	window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
	config();
}

void closegraph()
{
	SDL_Quit();
	SDL_DestroyWindow(window->window);
	SDL_FreeSurface(window->winSurface);
	SDL_DestroyRenderer(window->renderer);
	TTF_CloseFont(window->font);
	SDL_free(window);
}

Window* getWindow()
{
	return window;
}

void setWindowTitle(const char* title)
{
	SDL_SetWindowTitle(window->window, title);
}



/*@ Image*/
/*
* 如果不对图片进行缩放那么w，h可填0
*/
void loadimage(Image* img, const char* fileName, int w, int h)
{
	img->surface = IMG_Load(fileName);
	img->texture = SDL_CreateTextureFromSurface(window->renderer, img->surface);
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
	//SDL_BlitSurface(img->surface, NULL, window->winSurface, &(SDL_Rect){x, y, -1, -1});
	//SDL_RenderCopy(window->renderer, img->texture, NULL, &(SDL_Rect){x,y,img->surface->w,img->surface->h});
	SDL_RenderCopy(window->renderer, img->texture, NULL, &(SDL_Rect){x, y, img->w, img->h});
}

/*@ Text*/
interior bool loadText(const char* family, int size)
{
	window->font = TTF_OpenFont(family, size);
	if (!window->font)
	{
		SDL_Log("font open falied\n");
		return false;
	}
	return true;
}
void outtextxy(int x, int y, const char* text)
{	
	SDL_Surface* tsurface = TTF_RenderUTF8_Blended(window->font, text, toSdlColor(window->fontColor));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(window->renderer, tsurface);
	SDL_RenderCopy(window->renderer, texture, NULL, &(SDL_Rect){x,y,tsurface->w,tsurface->h});

	//SDL_BlitSurface(t, NULL, window->winSurface, &(SDL_Rect){x, y, -1, -1});
	SDL_FreeSurface(tsurface);
	SDL_DestroyTexture(texture);
}

void settextstyle(int w, int h, const char* family)
{
	TTF_CloseFont(window->font);
	loadText(family, w);
	//SDL_Log("font name %s",TTF_FontFaceFamilyName(window->font));
}


COLORREF getlinecolor()
{
	return window->lineColor;
}

void setlinecolor(COLORREF color)
{
	window->lineColor = color;
}

COLORREF gettextcolor()
{
	return window->fontColor;
}

void settextcolor(COLORREF color)
{
	window->fontColor = color;
}

COLORREF getfillcolor()
{
	return window->fillColor;
}

void setfillcolor(COLORREF color)
{
	window->fillColor = color;
}

COLORREF getbkcolor()
{
	return window->bkColor;
}

void setbkcolor(COLORREF color)
{
	window->bkColor = color;
}

int getbkmode()
{
	SDL_BlendMode mode;
	SDL_GetRenderDrawBlendMode(window->renderer,&mode);
	return mode;
}

void setbkmode(int mode)
{
	SDL_SetRenderDrawBlendMode(window->renderer, mode);
}



/*@ DrawShape*/
COLORREF getpixel(int x, int y)
{
	/*有问题 获取不到真实的颜色 都是0*/
	return ((Uint32*)window->winSurface->pixels)[y * window->w + x];
}

void putpixel(int x, int y, COLORREF color)
{
	SDL_SetRenderDrawColor(window->renderer, toRgbaColor(color));
	if (SDL_RenderDrawPoint(window->renderer, x, y))
	{
		SDL_Log("draw Point failed %s\n", SDL_GetError());
	}
}

void line(int x1, int y1, int x2, int y2)
{
	SDL_SetRenderDrawColor(window->renderer, toRgbaColor(window->lineColor));
	SDL_RenderDrawLine(window->renderer, x1, y1, x2, y2);
}

void rectangle(int left, int top, int right, int bottom)
{
	SDL_SetRenderDrawColor(window->renderer, toRgbaColor(window->lineColor));
	SDL_RenderDrawRect(window->renderer, &(SDL_Rect){left, top, right, bottom});
}

void fillrectangle(int left, int top, int right, int bottom)
{
	solidrectangle(left, top, right, bottom);
	rectangle(left, top, right, bottom);
}

void solidrectangle(int left, int top, int right, int bottom)
{
	SDL_SetRenderDrawColor(window->renderer, toRgbaColor(window->fillColor));
	SDL_RenderFillRect(window->renderer, &(SDL_Rect){left, top, right, bottom});
}

void clearrectangle(int left, int top, int right, int bottom)
{
	SDL_SetRenderDrawColor(window->renderer, toRgbaColor(window->bkColor));
	SDL_RenderFillRect(window->renderer, &(SDL_Rect){left, top, right, bottom});
}

static void _drawCircle(int x, int y, int radius)
{
	for (float radian = 0; radian < 2 * PI; radian += 0.01)
	{
		float fx = x + cos(radian) * radius;
		float fy = y + sin(radian) * radius;
		SDL_RenderDrawPointF(window->renderer, fx, fy);
	}
}
void circle(int x, int y, int radius)
{
	SDL_SetRenderDrawColor(window->renderer, toRgbaColor(window->lineColor));
	_drawCircle(x, y, radius);
}

void fillcircle(int x, int y, int radius)
{
	solidcircle(x, y, radius);
	circle(x, y, radius);
}

void solidcircle(int x, int y, int radius)
{
	SDL_SetRenderDrawColor(window->renderer, toRgbaColor(window->fillColor));
	while (radius >= 0)
	{
		_drawCircle(x, y, radius);
		radius--;
	}
}

void clearcircle(int x, int y, int radius)
{
	SDL_SetRenderDrawColor(window->renderer, toRgbaColor(window->bkColor));
	_drawCircle(x, y, radius);
}

void ellipse(int left, int top, int right, int bottom)
{


	//直线算法
	/*
	int x, y;
	int a, b, c, d, d1, d2;
	a = top - bottom;
	b = right - left;
	d = a + a + b;
	d1 = a + a;
	d2 = a+b+a+b;
	x = left;
	y = top;
	putpixel(x, y, window->lineColor);
	while (x < right)
	{
		if (d < 0)
		{
			x++;
			y++;
			d += d2;
		}
		else
		{
			x++;
			d += d1;
		}
		putpixel(x, y, window->lineColor);
	}*/
}

void fillellipse(int left, int top, int right, int bottom)
{
}

void solidellipse(int left, int top, int right, int bottom)
{
}

void clearellipse(int left, int top, int right, int bottom)
{
}

void roundrect(int left, int top, int right, int bottom, int ellipsewidth, int ellipseheight)
{
}

void fillroundrect(int left, int top, int right, int bottom, int ellipsewidth, int ellipseheight)
{
}

void solidroundrect(int left, int top, int right, int bottom, int ellipsewidth, int ellipseheight)
{
}

void clearroundrect(int left, int top, int right, int bottom, int ellipsewidth, int ellipseheight)
{
}

void arc(int left, int top, int right, int bottom, double stangle, double endangle)
{
}

void pie(int left, int top, int right, int bottom, double stangle, double endangle)
{
}

void fillpie(int left, int top, int right, int bottom, double stangle, double endangle)
{
}

void solidpie(int left, int top, int right, int bottom, double stangle, double endangle)
{
}

void clearpie(int left, int top, int right, int bottom, double stangle, double endangle)
{
}

void polyline(const POINT* points, int num)
{
	SDL_SetRenderDrawColor(window->renderer, toRgbaColor(window->lineColor));
	SDL_RenderDrawLines(window->renderer, (SDL_Point*)points, num);
}

void polygon(const POINT* points, int num)
{
	SDL_SetRenderDrawColor(window->renderer, toRgbaColor(window->lineColor));
	SDL_RenderDrawLines(window->renderer, (SDL_Point*)points, num);
	SDL_RenderDrawLine(window->renderer, points[num - 1].x, points[num - 1].y, points[num].x, points[num].y);
}

void fillpolygon(const POINT* points, int num)
{
	
}

void solidpolygon(const POINT* points, int num)
{
}

void clearpolygon(const POINT* points, int num)
{
}


void update()
{
	//SDL_UpdateWindowSurface(window->window);
	SDL_RenderPresent(window->renderer);
}

/*@ Event*/
bool peekMessage(ExMessage* msg)
{	
	update();
	SDL_SetRenderDrawColor(window->renderer, toRgbaColor(window->bkColor));
	SDL_RenderClear(window->renderer);

	static SDL_Event ev;
	SDL_PollEvent(&ev);	
	switch (ev.type)
	{
		/*鼠标*/
	case SDL_MOUSEMOTION:
		msg->x = ev.motion.x;
		msg->y = ev.motion.y;
		msg->message = M_MOUSEMOVE;
		return true;
	case SDL_MOUSEBUTTONDOWN:
		msg->x = ev.button.x;
		msg->y = ev.button.y;
		//单击
		if (ev.button.clicks == 1)
		{
			if (ev.button.button == SDL_BUTTON_LEFT)
			{			
				msg->lbutton = SDL_PRESSED;
				msg->message = M_LBUTTONDOWN;
			}
			else if (ev.button.button == SDL_BUTTON_RIGHT)
			{
				msg->rbutton = SDL_PRESSED;
				msg->message = M_RBUTTONDOWN;
			}
			else if (ev.button.button == SDL_BUTTON_MIDDLE)
			{
				msg->mbutton = SDL_PRESSED;
				msg->message = M_MBUTTONDOWN;
			}
		}
		//双击
		else if(ev.button.clicks == 2)
		{
			if (ev.button.button == SDL_BUTTON_LEFT)
			{
				msg->lbutton = SDL_RELEASED;
				msg->message = M_LBUTTONDBLCLK;
			}
			else if (ev.button.button == SDL_BUTTON_RIGHT)
			{
				msg->rbutton = SDL_RELEASED;
				msg->message = M_RBUTTONDBLCLK;
			}
			else if (ev.button.button == SDL_BUTTON_MIDDLE)
			{
				msg->mbutton = SDL_RELEASED;
				msg->message = M_MBUTTONDBLCLK;
			}
		}
		return true;
	case SDL_MOUSEBUTTONUP:
		msg->x = ev.button.x;
		msg->y = ev.button.y;
		if (ev.button.button == SDL_BUTTON_LEFT)
		{
			msg->message = M_LBUTTONUP;
		}
		else if (ev.button.button == SDL_BUTTON_RIGHT)
		{
			msg->message = M_RBUTTONUP;
		}
		else if (ev.button.button == SDL_BUTTON_MIDDLE)
		{
			msg->message = M_MBUTTONUP;
		}
		return true;
	case SDL_MOUSEWHEEL:
		msg->x = ev.motion.x;
		msg->y = ev.motion.y;
		msg->message = M_MOUSEWHEEL;
		msg->wheel = ev.wheel.y;
		return true;
		/*键盘*/
	case SDL_KEYDOWN:
		msg->message = M_KEYDOWN;
		msg->vkcode = ev.key.keysym.sym;
		msg->scancode = ev.key.keysym.scancode;

		return true;
	case SDL_KEYUP:
		msg->message = M_KEYUP;
		msg->vkcode = ev.key.keysym.sym;
		msg->scancode = ev.key.keysym.scancode;
		return true;
		/*窗口*/
	case SDL_WINDOWEVENT:
		//SDL_Log("windoevent %d\n", ev.window.event);
		switch (ev.window.event)
		{
		case SDL_WINDOWEVENT_NONE:
			msg->message = -1;
			break;
		case SDL_WINDOWEVENT_MINIMIZED:	//窗口最小化
			msg->message = M_MINIMIZED;
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:	//窗口最大化
			msg->message = M_MAXIMIZED;
			break;
		case SDL_WINDOWEVENT_MOVED:		//窗口移动
			msg->message = M_MOVED;
			break;
		default:
			break;
		}
		return true;
		/*系统*/
	case SDL_SYSWMEVENT:

		return true;
		/*退出*/
	case SDL_QUIT:
		closegraph();
		exit(0);
		return true;
	default:
		msg->message = -1;
		return true;
	}
	return false;
}

/*@ Frame 控制每秒帧数*/
struct Frame
{
	int start;
	int frameCnt;   //每秒帧数
}SDL_frame;
void start(Uint32 frame)
{
	SDL_frame.frameCnt = frame;
	SDL_frame.start = SDL_GetTicks();
}

void delay()
{
	int delayTime = 1000 / SDL_frame.frameCnt - (SDL_GetTicks() - SDL_frame.start);
	if (delayTime > 0)
	{
		//SDL_Log("delayTime:%d\n", delayTime);
		SDL_Delay(delayTime);
	}
}

#ifdef _WIN32
HWND getHWnd()
{
	HWND hq = FindWindow(NULL, _T("easySdl"));
	if (!hq)
	{
		SDL_Log("find Window falied\n");
		return NULL;
	}
	return hq;
}
#endif