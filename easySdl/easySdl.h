#ifndef _EASYSDL_H_
#define _EASYSDL_H_
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include<stdbool.h>

#ifdef _WIN32
#include<Windows.h>
#include<tchar.h>
#endif // _WIN32

// 颜色
enum Color
{
	Black			= 0,
	Blue			= 0x0000AA,
	Green			= 0x00AA00,
	Cyan			= 0x00AAAA,
	Red				= 0xAA0000,
	Magenta			= 0xAA00AA,
	Brown			= 0xAA5500,
	LightGray		= 0xAAAAAA,
	DarkGray		= 0x555555,
	LightBlue		= 0x5555FF,
	LightGreen		= 0x55FF55,
	LightCyan		= 0x55FFFF,
	LightRed		= 0xFF5555,
	LightMagenta	= 0xFF55FF,
	Yellow			= 0xFFFF55,
	White			= 0xFFFFFF,
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
	SDL_Window  *window;
	SDL_Surface *winSurface;

	TTF_Font* font;
}Window;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	void* initgraph(int w, int h, int flag);
	void closegraph();

	Window* getWindow();
	void setbkcolor(Uint32 color);

	/*@ IMAGE*/
	typedef struct IMAGE
	{
		SDL_Surface *surface;
	}Image;
	void loadImage(Image* img, const char* fileName, int w, int h);
	void putImage(int x,int y,Image* img);

	/*@ TEXT*/
	void outtextxy(int x, int y, const char* text,Uint32 color);

	/*@ DrawShape*/
	void fillRect(int x, int y, int w, int h, UINT32 color);
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
#endif


