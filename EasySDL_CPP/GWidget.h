#pragma once
#include"GWindow.h"
class GWidget
{
public:	
	GWidget(GWidget* parent = nullptr);
	virtual ~GWidget();
protected:
	int _x;
	int _y;
	GSize _size;
	GWindow* _parent;
};

