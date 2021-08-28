#include "easySdl.h"

/* 窗口结构体*/
Window *window;

/*@函数申明*/
#define interior	//内存函数
bool loadText(const char* family, int size);

#define toSdlColor(color) \
(SDL_Color) {(color >> 16) & 0xff, (color >> 8) & 0xff, (color) & 0xff, color >> 24}

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

	loadText("font/simhei.ttf",36);

	return true;
}
void* initgraph(int w, int h, int flag)
{
	if (!init())
	{
		SDL_Log("init falied :%s", SDL_GetError());
		return NULL;
	}
	window->w = w;
	window->h = h;
	window->flag = flag;
	window->bkColor = Black;
	SDL_strlcpy(window->title, "easySdl",64);
	window->window =  SDL_CreateWindow(window->title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		window->w, window->h, window->flag);
	if (!window->window)
	{
		SDL_Log("create window failed %s\n",SDL_GetError());
		return NULL;
	}

	window->winSurface = SDL_GetWindowSurface(window->window);
#ifdef _WIN32
	return getHWnd();
#endif // _WIN32
}

void closegraph()
{
	SDL_Quit();
	SDL_DestroyWindow(window->window);
	SDL_FreeSurface(window->winSurface);
	SDL_free(window);
}

Window* getWindow()
{
	return window;
}

void setbkcolor(Uint32 color)
{
	window->bkColor = color;
}


/*@ Image*/
void loadImage(Image* img, const char* fileName, int w, int h)
{
	img->surface = IMG_Load(fileName);
}
void putImage(int x, int y, Image* img)
{
	SDL_BlitSurface(img->surface, NULL, window->winSurface, &(SDL_Rect){x, y, -1, -1});
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
void outtextxy(int x, int y, const char* text,Uint32 color)
{	
	SDL_Surface* t = TTF_RenderUTF8_Blended(window->font, text, toSdlColor(color));
	SDL_BlitSurface(t, NULL, window->winSurface, &(SDL_Rect){x, y, -1, -1});
	SDL_FreeSurface(t);
}

/*@ DrawShape*/
void fillRect(int x, int y, int w, int h, UINT32 color)
{
	SDL_FillRect(window->winSurface, &(SDL_Rect){x, y, w, h}, color);
}

void update()
{
	SDL_UpdateWindowSurface(window->window);
}

bool peekMessage(ExMessage* msg)
{	
	update();
	fillRect(0, 0, 640, 480, window->bkColor);

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