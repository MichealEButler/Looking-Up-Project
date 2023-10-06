#include "Layer.h"

Layer::Layer()
{
	_x = 0.0;
	_y = 0.0;
	_var = 0.0;

	input = nullptr;
}

Layer::~Layer()
{

}

void Layer::storeLayer()
{
	input = new Input();

	input->storeASC("Input/SP_Extent_100m.asc", 300, 400, 0);
}
void Layer::setX(double x)
{
	_x = x;
}

void Layer::setY(double y)
{
	_y = y;
}

void Layer::setVar(double var)
{
	_var = var;
}

double Layer::getX()
{
	return _x;
}

double Layer::getY()
{
	return _y;
}

double Layer::getVar()
{
	return _var;
}