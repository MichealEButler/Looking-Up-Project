#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
public:
	Point();
	~Point();

	void setID(double id);
	void setX(double x);
	void setY(double y);

	double getID();
	double getX();
	double getY();

private:
	double _id;
	double _x;
	double _y;

};

#endif

