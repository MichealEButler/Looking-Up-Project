//class to store data from the input .asc layers

#ifndef LAYER_H
#define LAYER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>
#include <SDL2/SDL.h>
#include "Input.h"

class Layer
{
public:
	Layer();
	~Layer();

	void storeLayer(); //loads layer and stores it
	void setX(double x);
	void setY(double y);
	void setVar(double var);

	double getX();
	double getY();
	double getVar();

private:
	double _var;
	double _x;
	double _y;

	Input* input;
};

#endif
