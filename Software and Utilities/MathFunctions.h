#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>

class MathFunctions
{
public:
	MathFunctions();
	~MathFunctions();

	void linearRegression(); //simple linear regression to test each environmental variable in isolation

	//log regression functions
	void logRegression();
	void logRegression3();
	void logRegression5(std::vector<double> y, std::vector<double> x1, std::vector<double> x2, std::vector<double> x3, std::vector<double> x4, std::vector<double> x5, int values); //function used with avaiable iteration of site level raster data
	void logRegressionSites(std::vector<double> y, std::vector<double> x1, std::vector<double> x2, int values);

	double testLR2(double x1, double x5);
	double testLR5(double x1,double x2,double x3,double x4,double x5); //seperate function for checking all inputs from log regression
	double lp1(double x1);

	//quantile functions
	void setMedian(double median);
	void setQunatiles(double Q1, double Q2); // now a redunant method for obtaining quantiles
	void calcQuantile(double percentile, std::vector<double> dataset);

	void setQuartiles(std::vector<double> dataset);

	void randomSites(int nsites); //generates random sites an subsequent variables from input raster datasets

	int getNSites(); //returns number of random sites used

	bool custom_sort(double a, double b); // redundent function taken from online

	double getQuant();
	double getQ1();
	double getQ2();
	double getQ3();

	double getMedian();


private:
	std::vector<double> _spElevation = { 228.8999939,417.6000061,270.2000122,449.2000122,374.7000122,341, 270.2000122,426.6000061,
		445.3999939,352.7999878,346.7000122,462,335,366.5,351.3999939,432,407.3999939,432,425.2999878,351.3999939,398.7000122,449.7000122,449.2000122,
		388.2999878,452.7999878,351.8999939,449.2000122,270.2000122,462,465.6000061,398.3999939,266.1000061,514,344.3999939,427.3999939,417.6000061,
		439.2000122,456.7999878,364.5,420.8999939,451.8999939,378.2000122,384.2000122,407.8999939,266.1000061,458.7000122,420.2000122,
		346,429.2000122,522.7000122,335,449.2000122};

	std::vector<double> _spTri = { 62.9815979,33.42946243,49.84686279,21.47207451,30.25524902,24.60873032,49.84686279,30.19619751,
		26.31577301,12.313797,19.09605408,39.54856873,48.79938889,68.71833801,20.84540176,47.31818771,23.77309418,47.31818771,29.64118195,20.84540176,
		14.34571743,8.705726624,21.47207451,49.84487915,38.2954216,33.12112808,21.47207451,49.84686279,39.54856873,16.94314194,36.20581055,40.43909073,
		26.04362488,35.6655426,34.44139481,33.42946243,51.12046051,31.86472702,49.3563652,23.56820107,32.12508392,31.12715721,35.96791077,15.37889481,
		40.43909073,16.97676086,33.17378616,42.07397842,46.45083237,21.23181152,48.79938889
	};

	std::vector<double> _wikiE1 = { 6, 7, 15, 36, 39, 40, 41, 42, 43, 47, 49 };

	std::vector<double> _wikiE2 = { 7, 15, 36, 39, 40, 41 };

	int  _nsites;

	double _b0;
	double _b1;
	double _b2;
	double _b3;
	double _b4;
	double _b5;

	double _quant;
	double _q1; //first quantile
	double _q2; //second quantile (can represent both 2nd or median, dependent upon what the user wants)
	double _q3; //third quantile

	double _median;
};

#endif
