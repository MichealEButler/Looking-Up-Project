#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <SDL2/SDL.h>

class Input
{
public:
	Input();
	~Input();
	void loadASC(const char* filename); //load asc file for conversion
	void storeASC(std::string filename, int height, int width, int adLines); //stores value of xy in a 2d array of floats
	void loadSites(std::string filename, int x, int y);
	void readInFile(const char* filename, int line); // read line of configfile
	void storeOutFile(const char* filename, int height, int width, int adLines, int iteration, std::string dir);

	void readASC(); // reads the stored asc file
	void printStored(); //test ouput of stored array
	void renderInput(SDL_Renderer* renderer); //normal render for 1 - 5 scaling
	void renderInput2(SDL_Renderer* renderer); //scaled render
	void renderInput3(SDL_Renderer* renderer);

	void setCoord(int width, int height, float xxlcorner, float yllcorner, float cellSize); //for maually setting entent of area
	void resetCoord(); //reset x and y values

	float returnArray(int x, int y);

	void printSiteID();
	void printSiteX();
	void printSiteY();
	void printSiteE1();
	void printSiteE2();
	void printSiteE3();
	void printSiteE4();
	void printSiteE5();
	void printSiteE6();
	void printSiteE7();

	double returnID(int i); // return value at i from vector
	double returnX(int i); // return value at i from vector
	double returnY(int i); // return value at i from vector
	double returnE1(int i); // return value at i from vector
	double returnE2(int i); // return value at i from vector
	double returnE3(int i); // return value at i from vector
	double returnE4(int i); // return value at i from vector
	double returnE5(int i); // return value at i from vector
	double returnE6(int i); // return value at i from vector
	double returnE7(int i); // return value at i from vector

	double returnNX(int i);
	double returnNY(int i);

	double returnMinVar();
	double returnMaxVar();

	int getNFiles(); // returns number of files for use in populating vector in prediction.cpp
	int sizeX(); //returns number of values in vectors

private:
	int _width; //ncols
	int _height; //nrows
	float _xllcorner;
	float _yllcorner;
	float _cSize; //cell size
	int _nFiles; // number of input files

	//for stroing original values for conversion during output (displayed at the start of the asc file
	int _x1; //bottom left
	int _x2; // bottom right
	int _y1; //top left
	int _y2; //top right

	int _xi;
	int _yi;

	double _minVar;
	double _maxVar;

	float _value; // value stored of asc

	float** _valueArray;
	float** _siteArray;

	std::vector<double> _variables; //list of all values contained within each input raster layer

	//site variables
	std::vector<double> _id;
	std::vector<double> _x;
	std::vector<double> _y;
	std::vector<double> _e1;
	std::vector<double> _e2;
	std::vector<double> _e3;
	std::vector<double> _e4;
	std::vector<double> _e5;
	std::vector<double> _e6;
	std::vector<double> _e7;

	std::vector<double> _newX;
	std::vector<double> _newY;
};

#endif
