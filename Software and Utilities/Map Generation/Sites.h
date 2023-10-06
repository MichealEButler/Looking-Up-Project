#ifndef SITES_H
#define SITES_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Point.h"

class Sites
{
public:
	Sites();
	~Sites();

	void countNoSites(const char* filename);
	void readSitesFile(const char* filename, int x);

	void outSites(); // to output the stored vector of points to check

	int getNSites();

private:
	int _nSites;

	double _id;
	double _x;
	double _y;

	std::vector<Point*> lSites;

};

#endif