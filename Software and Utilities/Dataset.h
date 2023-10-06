#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

#include "MathFunctions.h"


class Dataset
{
public:
	Dataset();
	~Dataset();

	void storeDataset(std::string filename); //reads in file and stores data in vector
	void resetDataset(std::vector<int> randomSites); // repopulates the dataset with the values from the random sites lists

	void setVar(double var);
	void setName(std::string name);
	void setID(int id);

	void calcQuarts();
	void calcQuantes(double q1, double q2);
	void percentRange(double min, double max);
	void recalcQuants(double min, double max, double pR1, double pR2);

	void printInfo(); //prints all info including Quartiles and Quantiles

	double getQuant1();
	double getQuant2();
	double getQuart1();
	double getQuart2();
	double getMedian();
	double getMean();

	double getVar();
	std::string getName();
	int getID();


private:
	MathFunctions* mfunc = nullptr;

	std::vector<double> _dataset;

	double _var; //data variables
	std::string _name; // name of dataset
	int _id;

	double _quant1;
	double _quant2;

	double _quart1;
	double _quart2;

	double _median;
	double _mean;

	double _pRange1;
	double _pRange2;
};

#endif
