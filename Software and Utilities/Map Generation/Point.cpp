#include "Point.h"

Point::Point()
{
	std::cout << "Point created! " << std::endl;

	_id = 0.0;
	_x = 0.0;
	_y = 0.0;
}

Point::~Point()
{

}

void Point::setID(double id)
{
	_id = id;
}

void Point::setX(double x)
{
	_x = x;
}

void Point::setY(double y)
{
	_y = y;
}

double Point::getID()
{
	return _id;
}

double Point::getX()
{
	return _x;
}

double Point::getY()
{
	return _y;
}
