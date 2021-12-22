#pragma once
class GSize
{
public:
	GSize();
	GSize(int width,int height);
	int width();
	int height();

	void setHeight(int height);
	void setWidth(int width);

private:
	int _width;
	int _height;
};

