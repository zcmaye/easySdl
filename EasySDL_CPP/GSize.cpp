#include "GSize.h"

GSize::GSize():GSize(0,0)
{}

GSize::GSize(int width, int height)
	:_width(width),_height(height)
{}

int GSize::width()
{
	return _width;
}

int GSize::height()
{
	return _height;
}

void GSize::setHeight(int height)
{
	_height = height;
}

void GSize::setWidth(int width)
{
	_width = width;
}
