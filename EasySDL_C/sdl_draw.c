#include"sdl_draw.h"

void drawEllipse(SDL_Renderer* renderer, SDL_Color* color, int left, int top, int right, int bottom)
{
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	// ÍÖÔ²°ë¾¶
	double a = (right - left) / 2.0;
	double b = (bottom - top) / 2.0;

	SDL_FPoint pos = { 0, 0 };
	for (double x = a ; x >= -a; x -= 0.01)
	{
		double y = sqrt((1 - (x * x) / (a * a)) * (b * b));
		pos.x = x + a + left;
		pos.y = y + b + top;
		SDL_RenderDrawPointF(renderer, pos.x, pos.y);
		pos.x = x  + a + left;
		pos.y = -y + b + top;
		SDL_RenderDrawPointF(renderer, pos.x, pos.y);
	}

}

void drawCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
	for (double radian = 0; radian <= 2 * 3.1415926; radian += 0.001)
	{
		double fx = x + cos(radian) * radius;
		double fy = y + sin(radian) * radius;
		SDL_RenderDrawPointF(renderer, fx, fy);
	}
}

void drawArc(SDL_Renderer* renderer, int ox, int oy, int r, double startRadian, double endRadian)
{
	if (r <= 0)
		return;
	double ad = 1.0 / r;
	for (double ri = startRadian; ri < endRadian; ri += ad)
	{
		int x = r * cos(ri) + ox + .5;
		int y = oy - r * sin(ri) + .5;
		SDL_RenderDrawPointF(renderer, x, y);
	}
}


/*fill*/
void drawFillEllipse(SDL_Renderer* renderer, SDL_Color* color, int left, int top, int right, int bottom)
{
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	// ÍÖÔ²°ë¾¶
	double a = (right - left) / 2.0;
	double b = (bottom - top) / 2.0;

	SDL_FPoint pos = { 0, 0 };
	for (double x = a; x >= -a; x -= 0.01)
	{
		double y = sqrt((1 - (x * x) / (a * a)) * (b * b));
		pos.x = x + a + left;
		pos.y = y + b + top;
		SDL_RenderDrawPointF(renderer, pos.x, pos.y);
		SDL_RenderDrawLineF(renderer, pos.x,pos.y, left + a, top + b);
		pos.x = x + a + left;
		pos.y = -y + b + top;
		SDL_RenderDrawPointF(renderer, pos.x, pos.y);
		SDL_RenderDrawLineF(renderer, pos.x, pos.y, left + a, top + b);
	}

}

void drawFillCircle(SDL_Renderer* renderer, int x, int y, int radius)
{

	for (double radian = 0; radian <= 2 * 3.1415926; radian += 0.001)
	{
		double fx = x + cos(radian) * radius;
		double fy = y + sin(radian) * radius;
		SDL_RenderDrawPointF(renderer, fx, fy);
		SDL_RenderDrawLineF(renderer, fx, fy, x, y);
	}
}