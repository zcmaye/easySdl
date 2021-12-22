#include "GWidget.h"

GWidget::GWidget(GWidget* parent)
	:_x(0),_y(0),_size(640,480)
	,_parent(parent)
{
	
}

GWidget::~GWidget()
{
}
