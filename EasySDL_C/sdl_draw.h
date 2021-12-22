#pragma once
#include<SDL.h>

/*
* ֱ��
* ����
* ��
*/
/*
* ������Բ
*/
void drawEllipse(SDL_Renderer* renderer, SDL_Color* color, int left, int top, int right, int bottom);

/*
* ����Բ��
*/
void drawCircle(SDL_Renderer* renderer, int x, int y, int radius);


void drawArc(SDL_Renderer* renderer, int ox, int oy, int r, double radf, double radt);



/*
* ������Բ
*/
void drawFillEllipse(SDL_Renderer* renderer, SDL_Color* color, int left, int top, int right, int bottom);

/*
* ����Բ��
*/
void drawFillCircle(SDL_Renderer* renderer, int x, int y, int radius);