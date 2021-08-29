#ifndef _EASYSDL_H_
#define _EASYSDL_H_

#include<stdbool.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#ifdef _WIN32
#include<Windows.h>
#include<tchar.h>
#endif // _WIN32

// 颜色
enum Color
{
	Black			= 0xFF000000,
	Blue			= 0xFF0000AA,
	Green			= 0xFF00AA00,
	Cyan			= 0xFF00AAAA,
	Red				= 0xFFAA0000,
	Magenta			= 0xFFAA00AA,
	Brown			= 0xFFAA5500,
	LightGray		= 0xFFAAAAAA,
	DarkGray		= 0xFF555555,
	LightBlue		= 0xFF5555FF,
	LightGreen		= 0xFF55FF55,
	LightCyan		= 0xFF55FFFF,
	LightRed		= 0xFFFF5555,
	LightMagenta	= 0xFFFF55FF,
	Yellow			= 0xFFFFFF55,
	White			= 0xFFFFFFFF,
};

#define rgb(r,g,b) ((Uint32)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((Uint32)(BYTE)(r))<<16)))
#define argb(a,color) (((Uint32)a << 24) | color)


typedef struct Window_
{
	int w;
	int h;
	char title[64];
	int flag;
	Uint32 bkColor;		//背景颜色
	/*窗口*/	
	SDL_Window  *window;		//窗口标识
	SDL_Surface *winSurface;	//窗口
	SDL_Renderer* renderer;		//渲染器

	TTF_Font* font;				//字体
	Uint32    fontColor;

	Uint32	lineColor;
	Uint32	fillColor;
}Window;

/*@ IMAGE*/
typedef struct IMAGE
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	int w;
	int h;
}Image;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	void initgraph(int w, int h, int flag);	// 初始化图形环境
	void closegraph();							// 关闭图形环境

	Window* getWindow();
	void setWindowTitle(const char* title);

	/*@ IMAGE*/
	void loadimage(Image* img, const char* fileName, int w, int h);
	void putimage(int x,int y,Image* img);

	/*@ TEXT*/
	void outtextxy(int x, int y, const char* text);
	void settextstyle(int w, int h, const char* family);


	COLORREF getlinecolor();			// 获取当前线条颜色
	void setlinecolor(COLORREF color);	// 设置当前线条颜色
	COLORREF gettextcolor();			// 获取当前文字颜色
	void settextcolor(COLORREF color);	// 设置当前文字颜色
	COLORREF getfillcolor();			// 获取当前填充颜色
	void setfillcolor(COLORREF color);	// 设置当前填充颜色
	COLORREF getbkcolor();				// 获取当前绘图背景色
	void setbkcolor(COLORREF color);	// 设置当前绘图背景色
	int  getbkmode();					// 获取背景混合模式
	void setbkmode(int mode);			// 设置背景混合模式

	/*@ DrawShape*/
	COLORREF getpixel(int x, int y);				// 获取点的颜色
	void putpixel(int x, int y, COLORREF color);	// 画点

	void line(int x1, int y1, int x2, int y2);		// 画线

	void rectangle(int left, int top, int right, int bottom);	// 画矩形
	void fillrectangle(int left, int top, int right, int bottom);	// 画填充矩形(有边框)
	void solidrectangle(int left, int top, int right, int bottom);	// 画填充矩形(无边框)
	void clearrectangle(int left, int top, int right, int bottom);	// 清空矩形区域

	void circle(int x, int y, int radius);		// 画圆
	void fillcircle(int x, int y, int radius);		// 画填充圆(有边框)
	void solidcircle(int x, int y, int radius);		// 画填充圆(无边框)
	void clearcircle(int x, int y, int radius);		// 清空圆形区域

	void ellipse(int left, int top, int right, int bottom);	// 画椭圆
	void fillellipse(int left, int top, int right, int bottom);	// 画填充椭圆(有边框)
	void solidellipse(int left, int top, int right, int bottom);	// 画填充椭圆(无边框)
	void clearellipse(int left, int top, int right, int bottom);	// 清空椭圆形区域

	void roundrect(int left, int top, int right, int bottom, int ellipsewidth, int ellipseheight);		// 画圆角矩形
	void fillroundrect(int left, int top, int right, int bottom, int ellipsewidth, int ellipseheight);		// 画填充圆角矩形(有边框)
	void solidroundrect(int left, int top, int right, int bottom, int ellipsewidth, int ellipseheight);		// 画填充圆角矩形(无边框)
	void clearroundrect(int left, int top, int right, int bottom, int ellipsewidth, int ellipseheight);		// 清空圆角矩形区域

	void arc(int left, int top, int right, int bottom, double stangle, double endangle);	// 画椭圆弧(起始角度和终止角度为弧度制)
	void pie(int left, int top, int right, int bottom, double stangle, double endangle);	// 画椭圆扇形(起始角度和终止角度为弧度制)
	void fillpie(int left, int top, int right, int bottom, double stangle, double endangle);	// 画填充椭圆扇形(有边框)
	void solidpie(int left, int top, int right, int bottom, double stangle, double endangle);	// 画填充椭圆扇形(无边框)
	void clearpie(int left, int top, int right, int bottom, double stangle, double endangle);	// 清空椭圆扇形区域

	void polyline(const POINT* points, int num);								// 画多条连续的线
	void polygon(const POINT* points, int num);								// 画多边形
	void fillpolygon(const POINT* points, int num);								// 画填充的多边形(有边框)
	void solidpolygon(const POINT* points, int num);								// 画填充的多边形(无边框)
	void clearpolygon(const POINT* points, int num);


	void update();

	/*@ Event*/
enum MessageType
{

	M_MOUSEMOVE,		//The mouse moves.
	M_MOUSEWHEEL,		//The mouse wheel is rotated.
	M_LBUTTONDOWN,		//The left mouse button is pressed.
	M_LBUTTONUP	,		//The left mouse button is released.
	M_LBUTTONDBLCLK,	//The left mouse button is double-clicked.
	M_MBUTTONDOWN,		//The middle mouse button is pressed.
	M_MBUTTONUP,		//The middle mouse button is released.
	M_MBUTTONDBLCLK,	//The middle mouse button is double-clicked.
	M_RBUTTONDOWN,		//The right mouse button is pressed.
	M_RBUTTONUP,		//The right mouse button is released.
	M_RBUTTONDBLCLK,	//The right mouse button is double-clicked.
					
	M_KEYDOWN,			//A key is pressed.
	M_KEYUP,			//A key is released.
					
	M_CHAR,				//
					
	M_ACTIVATE,			//The window is activated or deactivated.
	M_MOVED,				//The window has been moved.
	M_SIZE,				//The size of window has changed.
	M_MINIMIZED,
	M_MAXIMIZED
};

enum VKCode
{
	RIGHT = 79,
	LEFT = 80,
	DOWN = 81,
	UP = 82,
};
// Message Structure
	typedef struct ExMessage
	{
		USHORT message;					// The message identifier.
		union
		{
			// Data of the mouse message
			struct
			{
				bool ctrl : 1;		// Indicates whether the CTRL key is pressed.
				bool shift : 1;		// Indicates whether the SHIFT key is pressed.
				bool lbutton : 1;		// Indicates whether the left mouse button is pressed.
				bool mbutton : 1;		// Indicates whether the middle mouse button is pressed.
				bool rbutton : 1;		// Indicates whether the right mouse button is pressed.
				short x;				// The x-coordinate of the cursor.
				short y;				// The y-coordinate of the cursor.
				short wheel;			// The distance the wheel is rotated, expressed in multiples or divisions of 120.
			};

			// Data of the key message
			struct
			{
				BYTE vkcode;			// The virtual-key code of the key.
				BYTE scancode;			// The scan code of the key. The value depends on the OEM.
				bool extended : 1;		// Indicates whether the key is an extended key, such as a function key or a key on the numeric keypad. The value is true if the key is an extended key; otherwise, it is false.
				bool prevdown : 1;		// Indicates whether the key is previously up or down.
			};

			// Data of the char message
			TCHAR ch;

			// Data of the window message
			struct
			{
				WPARAM wParam;
				LPARAM lParam;
			};
		};
	}ExMessage;
	bool peekMessage(ExMessage* message);

	/*@ Frame*/
	void start(Uint32 frame);
	void delay();


#ifdef _WIN32
	//获取窗口句柄
	HWND getHWnd();
#endif // _WIN32

#ifdef __cplusplus
}
#endif // __cplusplus
void drawEllipse(int x0, int y0, int a, int b);
#endif


