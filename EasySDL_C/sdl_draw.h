#pragma once
#include<SDL2/SDL.h>

/*
* 直线
* 矩形
* 点
*/
/*
* 绘制椭圆
*/
void drawEllipse(SDL_Renderer* renderer, SDL_Color* color, int left, int top, int right, int bottom);

/*
* 绘制圆形
*/
void drawCircle(SDL_Renderer* renderer, int x, int y, int radius);


void drawArc(SDL_Renderer* renderer, int ox, int oy, int r, double radf, double radt);



/*
* 绘制椭圆
*/
void drawFillEllipse(SDL_Renderer* renderer, SDL_Color* color, int left, int top, int right, int bottom);

/*
* 绘制圆形
*/
void drawFillCircle(SDL_Renderer* renderer, int x, int y, int radius);