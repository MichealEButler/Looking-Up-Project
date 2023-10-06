//need separte arrays to store the raster data from each environmental layer
//need to input site locations
//need to generate random absense data

#ifndef PREDICTION_H
#define PREDICTION_H

#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include "MathFunctions.h"
#include "Raster.h"
#include "Input.h"
#include "Output.h"
#include "Dataset.h"

class Prediction
{
public:
	Prediction();
	~Prediction();

	void loadMaps(bool isSites);

	//need a function to
	void storePSites(); // stores site presnce data
	void randomNonSites(int nnSites, int x, int y); // needs to create a 2d array of site loacation x, and y floats preferred as these can be rasterised
	void outputSites(); // outputs presense and absense data
	void printSites(int n);
	void runPredicition();
	void checkMaps(); // apply predictions to landscape

	void setDir(const char* dir); // sets directory for the input files
	void setWH(int width, int height); // number of cells on x and y
	void setXYC(float xllcorner, float yllcorner, float cellSize);
	void setnSites(int n);

	int randomN(int i, int j); //generates random coordinates (i and j indicate range)

	void storeDatsets(std::string directory); // store all input datasets into dataframe vector
	void storeDatasetsRandom(std::string directory, std::vector<int> randomSites); // same as above but with modified calculation using random values
	void univariateAnalysis(); // apply calculations to each dataset in the frame, outputting ranges
	void checkMapRanges(); // applys the univariate ranges to the layer datasets giving a 1 or 0 to the sfactor variable
	void checkMapRangesWeightings(int iteration, bool rc1, bool rc2, bool rc3, bool rc4, bool rc5);
	void checkMapRangesWeightings7(int iteration, bool rc1, bool rc2, bool rc3, bool rc4, bool rc5, bool rc6, bool rc7, int run);
	void setFileWeightings(int n);
	void setFileWeightings7(int n);
	void weightings(int nSets); //adds weighting to each of the variables (nSets = number of datasets within the dataframe
	void checkSitesState(); // check to see if a site is on an area of high potential
	void calcGain();
	void calcPLand();

	void setTestWeights(int iteration);

	void freePRaster();

	void setX(int x);
	void setY(int y);

	void setSamplePR1(double pr1);
	void setSamplePR2(double pr2);
	void setPerecnetRandomSites(double percent);

	void genRandomSitesList(); // populates a list of which sties to use in the run

	int getNHits();

	float getWV1();
	float getWV2();
	float getWV3();
	float getWV4();
	float getWV5();
	float getWV6();
	float getWV7();

	int getHeight();
	int getWidth();

	float getXllcorner();
	float getYllcorner();
	float getCellSize();

	double getGain();
	double getQ1();
	double getQ2();
	double getPLand();

	double returnElevationMinPercent();
	double returnElevationMaxPercent();

	std::string returnDir(); // return string from const car directroy input

private:
	int _nSites; // specified on initialisation nmber f sites in the input file
	int _width;
	int _height;

	double _gain;
	double _pLand;
	double _q1;
	double _q2;

	float _xllcorner;
	float _yllcorner;
	float _cellSize;

	int _nnSites; // number of non sites
	double _nkSites; // number of known sites obtained from input data
	std::vector<int> _percentRandomSites; // sites to be used based on percent allocation, randomised for each run
	int _x; // x extent of map area, used for calculating nonsite locations
	int _y; // y extent of map area
	double _sumPixels; // total number of cells within the area
	double _perRSites; // percentage of sites to be used for random
	int _nRSites; // number of sites for random

	float** predictionRaster;

	std::vector<Dataset*> dataframe; // array of all datasets
	double _nHits; // counts the number of locations which contain the hightest potential for a site
	double _correctSites; //number of known sites on area of high potential

	const char* _dir;

	std::vector<double> _v1;
	std::vector<double> _v2;
	std::vector<double> _v3;
	std::vector<double> _v4;
	std::vector<double> _v5;
	std::vector<double> _v6;
	std::vector<double> _v7;

	std::vector<std::vector<double>> nonSites; //locations of random generated absense data
	std::vector<std::vector<double>> knownSites; // locations of known sites

	std::vector<std::vector<double>> allSites;

	//site variables
	std::vector<double> _state; // absense or presense
	std::vector<double> _xs; //site x coord
	std::vector<double> _ys; //site y coord
	std::vector<double> _e1;
	std::vector<double> _e2;
	std::vector<double> _e3;
	std::vector<double> _e4;
	std::vector<double> _e5;
	std::vector<double> _e6;
	std::vector<double> _e7;

	std::vector<double> _castX; //converted x and y coords
	std::vector<double> _castY;


	MathFunctions* lRegression;
	Input* elevationMap;
	Input* slopeMap;
	Input* aspectMap;
	Input* triMap;
	Input* riversMap;
	Input* visibilityMap;
	Input* costMap;
	Input* sites;

	Output* output;

	std::vector<double> _fWeights1;
	std::vector<double> _fWeights2;
	std::vector<double> _fWeights3;
	std::vector<double> _fWeights4;
	std::vector<double> _fWeights5;
	std::vector<double> _fWeights6;
	std::vector<double> _fWeights7;

	float _wv1; // weights for each individual variable
	float _wv2;
	float _wv3;
	float _wv4;
	float _wv5;
	float _wv6;
	float _wv7;

	//vector array equivalant for the prediction raster
	std::vector<std::vector<float>> predLayer;

	//percent ranges to convert cairngorms scalings
	double _elevationMinPercent;
	double _elevationMaxPercent;

	double _samplePR1;
	double _samplePR2;

	//test weight sets
	float testset1[5] = { 0.2, 0.2, 0.2, 0.2, 0.2 };
	float testset2[5] = { 0.4, 0.2, 0.2, 0.1, 0.1 };
	float testset3[5] = { 0.2, 0.4, 0.1, 0.1, 0.2 };
	float testset4[5] = { 0.1, 0.2, 0.4, 0.1, 0.2 };
	float testset5[5] = { 0.1, 0.1, 0.2, 0.4, 0.2 };
	float testset6[5] = { 0.2, 0.1, 0.2, 0.1, 0.4 };
	float testset7[5] = { 0.3, 0.2, 0.3, 0.1, 0.1 };
	float testset8[5] = { 0.3, 0.3, 0.1, 0.1, 0.2 };
	float testset9[5] = { 0.2, 0.1, 0.3, 0.3, 0.1 };
	float testset10[5] = { 0.5, 0.1, 0.1, 0.1, 0.1 };


};

#endif
