#include "Prediction.h"

Prediction::Prediction()
{
	_nnSites = 0;
	_nkSites = 0.0;
	_x = 0;
	_y = 0;
	_sumPixels = 0;

	_nHits = 0.0;
	_correctSites = 0.0;

	predictionRaster = nullptr;

	_state.clear(); // absense or presense
	_xs.clear(); //site x coord
	_ys.clear(); //site y coord
	_e1.clear();
	_e2.clear();
	_e3.clear();
	_e4.clear();
	_e5.clear();
	_e6.clear();
	_e7.clear();
	_castX.clear();
	_castY.clear();

	lRegression = nullptr;

	elevationMap = nullptr;
	slopeMap = nullptr;
	aspectMap = nullptr;
	triMap = nullptr;
	riversMap = nullptr;
	sites = nullptr;
	output = new Output;

	_wv1 = 0.0;
	_wv2 = 0.0;
	_wv3 = 0.0;
	_wv4 = 0.0;
	_wv5 = 0.0;
	_wv6 = 0.0;
	_wv7 = 0.0;

	_height = 0;
	_width = 0;

	_xllcorner = 0.0;
	_yllcorner = 0.0;
	_cellSize = 0.0;

	_nSites = 0;

	_fWeights1.clear();
	_fWeights2.clear();
	_fWeights3.clear();
	_fWeights4.clear();
	_fWeights5.clear();
	_fWeights6.clear();
	_fWeights7.clear();

	_percentRandomSites.clear();

	_gain = 0.0;
	_q1 = 0.0;
	_q2 = 0.0;

	_elevationMinPercent = 0.0;
	_elevationMaxPercent = 0.0;

	_samplePR1 = 0.0;
	_samplePR2 = 0.0;

	_perRSites = 0.0;
	_nRSites = 0;
}

Prediction::~Prediction()
{
	delete elevationMap;
	delete slopeMap;
	delete aspectMap;
	delete triMap;
	delete riversMap;
	delete visibilityMap;
	delete costMap;
	delete sites;
}

void Prediction::setDir(const char* dir)
{
	_dir = dir;
}

void Prediction::setWH(int width, int height)
{
	_width = width;
	_height = height;

	predLayer.resize(_height, std::vector<float>(_width));
}

void Prediction::setXYC(float xllcorner, float yllcorner, float cellSize)
{
	_xllcorner = xllcorner;
	_yllcorner = yllcorner;
	_cellSize = cellSize;
}

void Prediction::setnSites(int n)
{
	// 37 NYM Sites
	// 52 South Peninnes Sites
	// 33 Tweed Sites
	// 13 Swiss
	// 25 Austria
	_nSites = n;
}

void Prediction::loadMaps(bool isSites)
{
	std::string dir = _dir;

	elevationMap = new Input();
	slopeMap = new Input();
	aspectMap = new Input();
	triMap = new Input();
	riversMap = new Input();
	visibilityMap = new Input();
	costMap = new Input();

	sites = new Input();

	elevationMap->storeASC(dir + "elevation.asc", _height, _width, 0);
	std::cout << "Min and Max values for elevation = " << elevationMap->returnMinVar() << " - " << elevationMap->returnMaxVar() << std::endl << std::endl;

	slopeMap->storeASC(dir + "slope.asc", _height, _width, 0);
	std::cout << "Min and Max values for slope = " << slopeMap->returnMinVar() << " - " << slopeMap->returnMaxVar() << std::endl << std::endl;

	aspectMap->storeASC(dir + "aspect.asc", _height, _width, 0);
	std::cout << "Min and Max values for aspect = " << aspectMap->returnMinVar() << " - " << aspectMap->returnMaxVar() << std::endl << std::endl;

	triMap->storeASC(dir + "tri.asc", _height, _width, 0);
	std::cout << "Min and Max values for TRI = " << triMap->returnMinVar() << " - " << triMap->returnMaxVar() << std::endl << std::endl;

	riversMap->storeASC(dir + "dtr.asc", _height, _width, 0);
	std::cout << "Min and Max values for DTR = " << riversMap->returnMinVar() << " - " << riversMap->returnMaxVar() << std::endl << std::endl;

	visibilityMap->storeASC(dir + "visibility.asc", _height, _width, 0);
	std::cout << "Min and Max values for DTR = " << visibilityMap->returnMinVar() << " - " << visibilityMap->returnMaxVar() << std::endl << std::endl;

	costMap->storeASC(dir + "slope_cost.asc", _height, _width, 0);
	std::cout << "Min and Max values for DTR = " << costMap->returnMinVar() << " - " << costMap->returnMaxVar() << std::endl << std::endl;

	if (isSites)
	{
		sites->loadSites(dir + "sites_data_7.txt", _nSites, 7);
		sites->setCoord(_width, _height, _xllcorner, _yllcorner, _cellSize);
		sites->resetCoord();

		for (int i = 0; i < _nSites; i++)
		{
			std::cout << "x = " << sites->returnX(i) << " y = " << sites->returnY(i) << std::endl;
			std::cout << "New x = " << sites->returnNX(i) << " New y = " << sites->returnNY(i) << std::endl;
		}
	}

	_sumPixels = _height * _width;

}

void Prediction::storePSites()
{
	_nkSites = 0.0;

	for (int i = 0; i < sites->sizeX(); i++)
	{
		_state.push_back(1);
		_xs.push_back(sites->returnNX(i));
		_ys.push_back(sites->returnNY(i));
		_e1.push_back(sites->returnE1(i));
		_e2.push_back(sites->returnE2(i));
		_e3.push_back(sites->returnE3(i));
		_e4.push_back(sites->returnE4(i));
		_e5.push_back(sites->returnE5(i));
		_e6.push_back(sites->returnE6(i));
		_e7.push_back(sites->returnE7(i));
		_castX.push_back(sites->returnNX(i));
		_castY.push_back(sites->returnNY(i));
		_nkSites = _nkSites + 1.0;
	}

	std::cout << "Number of known sites = " << _nkSites << std::endl << std::endl;
}

void Prediction::randomNonSites(int nnSites, int x, int y)
{
	srand(time(0));

	_nnSites = nnSites;
	int rx = 0;
	int ry = 0;

	for (int i = 0; i < nnSites; i++)
	{
		//generate an x and y value
		//rx = randomN(0, x);
		//ry = randomN(0, y);
		rx = rand() % x + 1;
		ry = rand() % y + 1;

		std::cout << "generated random number, x = " << rx << " y = " << ry << std::endl;

		//check if they are in the sea
		while(elevationMap->returnArray(rx,ry) <= 1)
		{
			//rx = randomN(0, x);
			//ry = randomN(0, y);
			rx = rand() % x + 1;
			ry = rand() % y + 1;
			std::cout << "checked values against data " << std::endl;
		}

		//store values to vectors
		_state.push_back(0);
		_xs.push_back(rx);
		_ys.push_back(ry);
		_e1.push_back(elevationMap->returnArray(rx, ry));
		_e2.push_back(slopeMap->returnArray(rx, ry));
		_e3.push_back(triMap->returnArray(rx, ry));
		_e4.push_back(aspectMap->returnArray(rx, ry));
		_e5.push_back(riversMap->returnArray(rx, ry));
		_e6.push_back(visibilityMap->returnArray(rx, ry));
		_e7.push_back(costMap->returnArray(rx, ry));
	}
	//populate

}

void Prediction::outputSites()
{
	output->openFile("Output/Output.txt");

}

int Prediction::randomN(int i, int j)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(i, j);

	return dist6(rng);
}

void Prediction::storeDatsets(std::string directory)
{
	dataframe = std::vector<Dataset*>(7);

	std::string dir = directory;

	// loops need to be modified to take in name of variable and name of file for storing of each

	dataframe[0] = new Dataset();
	dataframe[0]->setID(1);
	dataframe[0]->setName("Elevation");
	dataframe[0]->storeDataset(dir + "sites_elevation.txt");
	dataframe[0]->calcQuarts();
	dataframe[0]->calcQuantes(0.1, 0.9);
	dataframe[0]->printInfo();
	dataframe[0]->percentRange(elevationMap->returnMinVar(), elevationMap->returnMaxVar());
	_elevationMinPercent = elevationMap->returnMinVar();
	_elevationMaxPercent = elevationMap->returnMaxVar();

	dataframe[1] = new Dataset();
	dataframe[1]->setID(2);
	dataframe[1]->setName("Slope");
	dataframe[1]->storeDataset(dir + "sites_slope.txt");
	dataframe[1]->calcQuarts();
	dataframe[1]->calcQuantes(0.1, 0.9);
	dataframe[1]->printInfo();
	dataframe[1]->percentRange(slopeMap->returnMinVar(), slopeMap->returnMaxVar());

	dataframe[2] = new Dataset();
	dataframe[2]->setID(3);
	dataframe[2]->setName("Aspect");
	dataframe[2]->storeDataset(dir + "sites_aspect.txt");
	dataframe[2]->calcQuarts();
	dataframe[2]->calcQuantes(0.1, 0.9);
	dataframe[2]->printInfo();
	dataframe[2]->percentRange(aspectMap->returnMinVar(), aspectMap->returnMaxVar());

	dataframe[3] = new Dataset();
	dataframe[3]->setID(4);
	dataframe[3]->setName("TRI");
	dataframe[3]->storeDataset(dir + "sites_TRI.txt");
	dataframe[3]->calcQuarts();
	dataframe[3]->calcQuantes(0.1, 0.9);
	dataframe[3]->printInfo();
	dataframe[3]->percentRange(triMap->returnMinVar(), triMap->returnMaxVar());

	dataframe[4] = new Dataset();
	dataframe[4]->setID(5);
	dataframe[4]->setName("DTR");
	dataframe[4]->storeDataset(dir + "sites_dtr.txt");
	dataframe[4]->calcQuarts();
	dataframe[4]->calcQuantes(0.1, 0.9);
	dataframe[4]->printInfo();
	dataframe[4]->percentRange(riversMap->returnMinVar(), riversMap->returnMaxVar());

	dataframe[5] = new Dataset();
	dataframe[5]->setID(6);
	dataframe[5]->setName("Vsibility");
	dataframe[5]->storeDataset(dir + "sites_visibility.txt");
	dataframe[5]->calcQuarts();
	dataframe[5]->calcQuantes(0.1, 0.9);
	dataframe[5]->printInfo();
	dataframe[5]->percentRange(visibilityMap->returnMinVar(), visibilityMap->returnMaxVar());

	dataframe[6] = new Dataset();
	dataframe[6]->setID(7);
	dataframe[6]->setName("Slope Cost");
	dataframe[6]->storeDataset(dir + "sites_slope_cost.txt");
	dataframe[6]->calcQuarts();
	dataframe[6]->calcQuantes(0.1, 0.9);
	dataframe[6]->printInfo();
	dataframe[6]->percentRange(costMap->returnMinVar(), costMap->returnMaxVar());

}

void Prediction::storeDatasetsRandom(std::string directory, std::vector<int> randomSites)
{
	dataframe = std::vector<Dataset*>(7);

	std::string dir = directory;

	// loops need to be modified to take in name of variable and name of file for storing of each

	dataframe[0] = new Dataset();
	dataframe[0]->setID(1);
	dataframe[0]->setName("Elevation");
	dataframe[0]->storeDataset(dir + "sites_elevation.txt");
	dataframe[0]->resetDataset(randomSites);
	dataframe[0]->calcQuarts();
	dataframe[0]->calcQuantes(0.1, 0.9);
	dataframe[0]->printInfo();
	dataframe[0]->percentRange(elevationMap->returnMinVar(), elevationMap->returnMaxVar());
	_elevationMinPercent = elevationMap->returnMinVar();
	_elevationMaxPercent = elevationMap->returnMaxVar();

	dataframe[1] = new Dataset();
	dataframe[1]->setID(2);
	dataframe[1]->setName("Slope");
	dataframe[1]->storeDataset(dir + "sites_slope.txt");
	dataframe[1]->resetDataset(randomSites);
	dataframe[1]->calcQuarts();
	dataframe[1]->calcQuantes(0.1, 0.9);
	dataframe[1]->printInfo();
	dataframe[1]->percentRange(slopeMap->returnMinVar(), slopeMap->returnMaxVar());

	dataframe[2] = new Dataset();
	dataframe[2]->setID(3);
	dataframe[2]->setName("Aspect");
	dataframe[2]->storeDataset(dir + "sites_aspect.txt");
	dataframe[2]->resetDataset(randomSites);
	dataframe[2]->calcQuarts();
	dataframe[2]->calcQuantes(0.1, 0.9);
	dataframe[2]->printInfo();
	dataframe[2]->percentRange(aspectMap->returnMinVar(), aspectMap->returnMaxVar());

	dataframe[3] = new Dataset();
	dataframe[3]->setID(4);
	dataframe[3]->setName("TRI");
	dataframe[3]->storeDataset(dir + "sites_TRI.txt");
	dataframe[3]->resetDataset(randomSites);
	dataframe[3]->calcQuarts();
	dataframe[3]->calcQuantes(0.1, 0.9);
	dataframe[3]->printInfo();
	dataframe[3]->percentRange(triMap->returnMinVar(), triMap->returnMaxVar());

	dataframe[4] = new Dataset();
	dataframe[4]->setID(5);
	dataframe[4]->setName("DTR");
	dataframe[4]->storeDataset(dir + "sites_dtr.txt");
	dataframe[4]->resetDataset(randomSites);
	dataframe[4]->calcQuarts();
	dataframe[4]->calcQuantes(0.1, 0.9);
	dataframe[4]->printInfo();
	dataframe[4]->percentRange(riversMap->returnMinVar(), riversMap->returnMaxVar());

	dataframe[5] = new Dataset();
	dataframe[5]->setID(6);
	dataframe[5]->setName("Vsibility");
	dataframe[5]->storeDataset(dir + "sites_visibility.txt");
	dataframe[5]->resetDataset(randomSites);
	dataframe[5]->calcQuarts();
	dataframe[5]->calcQuantes(0.1, 0.9);
	dataframe[5]->printInfo();
	dataframe[5]->percentRange(visibilityMap->returnMinVar(), visibilityMap->returnMaxVar());

	dataframe[6] = new Dataset();
	dataframe[6]->setID(7);
	dataframe[6]->setName("Slope Cost");
	dataframe[6]->storeDataset(dir + "sites_slope_cost.txt");
	dataframe[6]->resetDataset(randomSites);
	dataframe[6]->calcQuarts();
	dataframe[6]->calcQuantes(0.1, 0.9);
	dataframe[6]->printInfo();
	dataframe[6]->percentRange(costMap->returnMinVar(), costMap->returnMaxVar());
}

void Prediction::univariateAnalysis()
{

}

void Prediction::checkMapRanges()
{
	int sum = 0;
	_nHits = 0.0;

	std::ofstream out("Output/Output.txt");

	predictionRaster = new float* [_height];

	for (int i = 0; i < _height; i++)
	{
		predictionRaster[i] = new float[_width];
		for (int j = 0; j < _width; j++)
		{
			sum = 0;

			if (elevationMap->returnArray(i, j) >= dataframe[0]->getQuart1() && elevationMap->returnArray(i, j) <= dataframe[0]->getQuart2())
			{
				sum = sum + 1;
			}
			if (slopeMap->returnArray(i, j) >= dataframe[1]->getQuart1() && slopeMap->returnArray(i, j) <= dataframe[1]->getQuart2())
			{
				sum = sum + 1;
			}
			if (aspectMap->returnArray(i, j) >= dataframe[2]->getQuart1() && aspectMap->returnArray(i, j) <= dataframe[2]->getQuart2())
			{
				sum = sum + 1;
			}
			if (triMap->returnArray(i, j) >= dataframe[3]->getQuart1() && triMap->returnArray(i, j) <= dataframe[3]->getQuart2())
			{
				sum = sum + 1;
			}
			if (riversMap->returnArray(i, j) >= dataframe[4]->getQuart1() && riversMap->returnArray(i, j) <= dataframe[4]->getQuart2())
			{
				sum = sum + 1;

			}
			if (visibilityMap->returnArray(i, j) >= dataframe[0]->getQuart1() && visibilityMap->returnArray(i, j) <= dataframe[0]->getQuart2())
			{
				sum = sum + 1;
			}
			if (costMap->returnArray(i, j) >= dataframe[0]->getQuart1() && costMap->returnArray(i, j) <= dataframe[0]->getQuart2())
			{
				sum = sum + 1;
			}

			predictionRaster[i][j] = sum;
			if (sum == 7)
			{
				_nHits = _nHits + 1.0;
			}

			out << predictionRaster[i][j] << " ";
		}
		out << std::endl;
	}

	out.close();
}

void Prediction::setTestWeights(int iteration)
{
	_wv1 = 0.0;
	_wv2 = 0.0;
	_wv3 = 0.0;
	_wv4 = 0.0;
	_wv5 = 0.0;

	switch (iteration)
	{
	case 0:
		_wv1 = testset1[0];
		_wv2 = testset1[1];
		_wv3 = testset1[2];
		_wv4 = testset1[3];
		_wv5 = testset1[4];
		break;
	case 1:
		_wv1 = testset2[0];
		_wv2 = testset2[1];
		_wv3 = testset2[2];
		_wv4 = testset2[3];
		_wv5 = testset2[4];
		break;
	case 2:
		_wv1 = testset3[0];
		_wv2 = testset3[1];
		_wv3 = testset3[2];
		_wv4 = testset3[3];
		_wv5 = testset3[4];
		break;
	case 3:
		_wv1 = testset4[0];
		_wv2 = testset4[1];
		_wv3 = testset4[2];
		_wv4 = testset4[3];
		_wv5 = testset4[4];
		break;
	case 4:
		_wv1 = testset5[0];
		_wv2 = testset5[1];
		_wv3 = testset5[2];
		_wv4 = testset5[3];
		_wv5 = testset5[4];
		break;
	case 5:
		_wv1 = testset6[0];
		_wv2 = testset6[1];
		_wv3 = testset6[2];
		_wv4 = testset6[3];
		_wv5 = testset6[4];
		break;
	case 6:
		_wv1 = testset7[0];
		_wv2 = testset7[1];
		_wv3 = testset7[2];
		_wv4 = testset7[3];
		_wv5 = testset7[4];
		break;
	case 7:
		_wv1 = testset8[0];
		_wv2 = testset8[1];
		_wv3 = testset8[2];
		_wv4 = testset8[3];
		_wv5 = testset8[4];
		break;
	case 8:
		_wv1 = testset9[0];
		_wv2 = testset9[1];
		_wv3 = testset9[2];
		_wv4 = testset9[3];
		_wv5 = testset9[4];
		break;
	case 9:
		_wv1 = testset10[0];
		_wv2 = testset10[1];
		_wv3 = testset10[2];
		_wv4 = testset10[3];
		_wv5 = testset10[4];
		break;
	}
}

void Prediction::checkMapRangesWeightings(int iteration, bool rc1, bool rc2, bool rc3, bool rc4, bool rc5)
{
	//setTestWeights(iteration);

	_wv1 = _fWeights1[iteration];
	_wv2 = _fWeights2[iteration];
	_wv3 = _fWeights3[iteration];
	_wv4 = _fWeights4[iteration];
	_wv5 = _fWeights5[iteration];


	if (rc1)
	{
		dataframe[0]->recalcQuants(elevationMap->returnMinVar(), elevationMap->returnMaxVar(), _samplePR1, _samplePR2);
	}
	if (rc2)
	{
		//dataframe[1]->recalcQuants(slopeMap->returnMinVar(), slopeMap->returnMaxVar());
	}
	if (rc3)
	{
		//dataframe[2]->recalcQuants(aspectMap->returnMinVar(), aspectMap->returnMaxVar());
	}
	if (rc4)
	{
		//dataframe[3]->recalcQuants(triMap->returnMinVar(), triMap->returnMaxVar());
	}
	if (rc5)
	{
		//dataframe[4]->recalcQuants(riversMap->returnMinVar(), riversMap->returnMaxVar());
	}

	std::string dir = _dir;

	float sum = 0;
	_nHits = 0.0;

	std::string p1 = dir + "Output/Run";
	std::string p2 = ".asc";
	std::ofstream out(p1 + std::to_string(iteration) + p2);

	out << "ncols\t" << _width << std::endl;
	out << "nrows\t" << _height << std::endl;
	out << "xllcorner\t" << _xllcorner << std::endl;
	out << "yllcorner\t" << _yllcorner << std::endl;
	out << "cellsize\t" << _cellSize << std::endl;

	//predictionRaster = new float* [_height];

	for (int i = 0; i < _height; i++)
	{
		//predictionRaster[i] = new float[_width];

		for (int j = 0; j < _width; j++)
		{
			sum = 0;

			if (elevationMap->returnArray(i, j) >= dataframe[0]->getQuart1() && elevationMap->returnArray(i, j) <= dataframe[0]->getQuart2())
			{
				//sum = sum + _fWeights1[iteration];
				sum = sum + _wv1;
			}
			if (slopeMap->returnArray(i, j) >= dataframe[1]->getQuart1() && slopeMap->returnArray(i, j) <= dataframe[1]->getQuart2())
			{
				//sum = sum + _fWeights2[iteration];
				sum = sum + _wv2;
			}
			if (aspectMap->returnArray(i, j) >= dataframe[2]->getQuart1() && aspectMap->returnArray(i, j) <= dataframe[2]->getQuart2())
			{
				//sum = sum + _fWeights3[iteration];
				sum = sum + _wv3;
			}
			if (triMap->returnArray(i, j) >= dataframe[3]->getQuart1() && triMap->returnArray(i, j) <= dataframe[3]->getQuart2())
			{
				//sum = sum + _fWeights4[iteration];
				sum = sum + _wv4;
			}
			if (riversMap->returnArray(i, j) >= dataframe[4]->getQuart1() && riversMap->returnArray(i, j) <= dataframe[4]->getQuart2())
			{
				//sum = sum + _fWeights5[iteration];
				sum = sum + _wv5;

			}

			//predictionRaster[i][j] = sum;
			predLayer[i][j] = sum;

			if (sum >= 6)
			{
				_nHits = _nHits + 1.0;
			}

			out << sum << " ";
		}
		out << std::endl;
	}

	out.close();
}

void Prediction::checkMapRangesWeightings7(int iteration, bool rc1, bool rc2, bool rc3, bool rc4, bool rc5, bool rc6, bool rc7, int run)
{
	//setTestWeights(iteration);

	_wv1 = _fWeights1[iteration];
	_wv2 = _fWeights2[iteration];
	_wv3 = _fWeights3[iteration];
	_wv4 = _fWeights4[iteration];
	_wv5 = _fWeights5[iteration];
	_wv6 = _fWeights6[iteration];
	_wv7 = _fWeights7[iteration];


	if (rc1)
	{
		dataframe[0]->recalcQuants(elevationMap->returnMinVar(), elevationMap->returnMaxVar(), _samplePR1, _samplePR2);
	}
	if (rc2)
	{
		//dataframe[1]->recalcQuants(slopeMap->returnMinVar(), slopeMap->returnMaxVar());
	}
	if (rc3)
	{
		//dataframe[2]->recalcQuants(aspectMap->returnMinVar(), aspectMap->returnMaxVar());
	}
	if (rc4)
	{
		//dataframe[3]->recalcQuants(triMap->returnMinVar(), triMap->returnMaxVar());
	}
	if (rc5)
	{
		//dataframe[4]->recalcQuants(riversMap->returnMinVar(), riversMap->returnMaxVar());
	}
	if (rc6)
	{
		//dataframe[5]->recalcQuants(visibilityMap->returnMinVar(), visibilityMap->returnMaxVar());
	}
	if (rc7)
	{
		//dataframe[6]->recalcQuants(costMap->returnMinVar(), costMap->returnMaxVar());
	}
	std::string dir = _dir;

	float sum = 0;
	_nHits = 0.0;

	std::string p1 = dir + "Output/Run";
	std::string p2 = ".asc";
	std::ofstream out(p1 + std::to_string(run) + p2);

	out << "ncols\t" << _width << std::endl;
	out << "nrows\t" << _height << std::endl;
	out << "xllcorner\t" << _xllcorner << std::endl;
	out << "yllcorner\t" << _yllcorner << std::endl;
	out << "cellsize\t" << _cellSize << std::endl;

	//predictionRaster = new float* [_height];

	for (int i = 0; i < _height; i++)
	{
		//predictionRaster[i] = new float[_width];

		for (int j = 0; j < _width; j++)
		{
			sum = 0;

			if (elevationMap->returnArray(i, j) >= dataframe[0]->getQuart1() && elevationMap->returnArray(i, j) <= dataframe[0]->getQuart2())
			{
				//sum = sum + _fWeights1[iteration];
				sum = sum + _wv1;
			}
			if (slopeMap->returnArray(i, j) >= dataframe[1]->getQuart1() && slopeMap->returnArray(i, j) <= dataframe[1]->getQuart2())
			{
				//sum = sum + _fWeights2[iteration];
				sum = sum + _wv2;
			}
			if (aspectMap->returnArray(i, j) >= dataframe[2]->getQuart1() && aspectMap->returnArray(i, j) <= dataframe[2]->getQuart2())
			{
				//sum = sum + _fWeights3[iteration];
				sum = sum + _wv3;
			}
			if (triMap->returnArray(i, j) >= dataframe[3]->getQuart1() && triMap->returnArray(i, j) <= dataframe[3]->getQuart2())
			{
				//sum = sum + _fWeights4[iteration];
				sum = sum + _wv4;
			}
			if (riversMap->returnArray(i, j) >= dataframe[4]->getQuart1() && riversMap->returnArray(i, j) <= dataframe[4]->getQuart2())
			{
				//sum = sum + _fWeights5[iteration];
				sum = sum + _wv5;

			}
			if (visibilityMap->returnArray(i, j) >= dataframe[5]->getQuart1() && visibilityMap->returnArray(i, j) <= dataframe[5]->getQuart2())
			{
				//sum = sum + _fWeights6[iteration];
				sum = sum + _wv6;

			}
			if (costMap->returnArray(i, j) >= dataframe[6]->getQuart1() && costMap->returnArray(i, j) <= dataframe[6]->getQuart2())
			{
				//sum = sum + _fWeights7[iteration];
				sum = sum + _wv7;

			}

			//predictionRaster[i][j] = sum;
			predLayer[i][j] = sum;

			if (sum >= 7)
			{
				_nHits = _nHits + 1.0;
			}

			out << sum << " ";
		}
		out << std::endl;
	}

	out.close();
}

void Prediction::setFileWeightings(int n)
{
	//std::ifstream file("Input/t5_scalers.txt");
	std::ifstream file("Input/scalers.txt");

	double input = 0;

	if (file.is_open())
	{

		for (int i = 0; i < n; i++)
		{
			file >> input;
			_fWeights1.push_back(input);
			file >> input;
			_fWeights2.push_back(input);
			file >> input;
			_fWeights3.push_back(input);
			file >> input;
			_fWeights4.push_back(input);
			file >> input;
			_fWeights5.push_back(input);
		}
	}

	/*
	for (int j = 0; j < _fWeights1.size(); j++)
	{
		std::cout << _fWeights1[j]  << " " << _fWeights2[j] << " " << _fWeights3[j] << " " << _fWeights4[j] << " " << _fWeights5[j] << std::endl;
	}
*/
}

void Prediction::setFileWeightings7(int n)
{
	std::ifstream file("Input/scalers7.txt");

	double input = 0;

	if (file.is_open())
	{

		for (int i = 0; i < n; i++)
		{
			file >> input;
			_fWeights1.push_back(input);
			file >> input;
			_fWeights2.push_back(input);
			file >> input;
			_fWeights3.push_back(input);
			file >> input;
			_fWeights4.push_back(input);
			file >> input;
			_fWeights5.push_back(input);
			file >> input;
			_fWeights6.push_back(input);
			file >> input;
			_fWeights7.push_back(input);
		}
	}

	/*
	for (int j = 0; j < _fWeights1.size(); j++)
	{
		std::cout << _fWeights1[j]  << " " << _fWeights2[j] << " " << _fWeights3[j] << " " << _fWeights4[j] << " " << _fWeights5[j] << std::endl;
	}
	*/
}

void Prediction::weightings(int nSets)
{


}

void Prediction::checkSitesState()
{
	_correctSites = 0.0;

	for (int i = 0; i < _nkSites; i++)
	{

		if (predLayer[int(_castY[i])][int(_castX[i])] >= 7)
		{
			_correctSites = _correctSites + 1.0;
		}

	}

	std::cout << "Number of known sites located on high potential area = " << _correctSites << std::endl;
}

void Prediction::calcGain()
{
	double gain = 0.0;

	double pLand = (_nHits * 100) / _sumPixels;
	double pSite = (_correctSites * 100) / _nkSites;

	gain = 1 - (pLand / pSite);

	_gain = gain;

	std::cout << "Gain = " << gain << std::endl;
}

void Prediction::calcPLand()
{
	double pLand = (_nHits * 100) / _sumPixels;

	_pLand = pLand;

	std::cout << "Percentage high potential areas = " << pLand << std::endl;
}

void Prediction::printSites(int n)
{
	std::ofstream out("Sites.txt");

	for (int i = 0; i < n; i++)
	{
		std::cout << _state[i] << " ";
		std::cout << _xs[i] << " ";
		std::cout << _ys[i] << " ";
		std::cout << _e1[i] << " ";
		std::cout << _e2[i] << " ";
		std::cout << _e3[i] << " ";
		std::cout << _e4[i] << " ";
		std::cout << _e5[i] << " ";
		std::cout << _e6[i] << " ";
		std::cout << _e7[i] << " " << std::endl;

		out << _state[i] << " ";
		out << _xs[i] << " ";
		out << _ys[i] << " ";
		out << _e1[i] << " ";
		out << _e2[i] << " ";
		out << _e3[i] << " ";
		out << _e4[i] << " ";
		out << _e5[i] << " ";
		out << _e6[i] << " ";
		out << _e7[i] << " " << std::endl;
	}
	out.close();
}

void Prediction::setX(int x)
{
	_x = x;
}

void Prediction::setY(int y)
{
	_y = y;
}

void Prediction::runPredicition()
{
	lRegression = new MathFunctions();

	//lRegression->logRegression5(_state, _e1, _e2, _e3, _e4, _e5, 87);
	lRegression->logRegressionSites(_state, _e1, _e5, 87);
}

void Prediction::checkMaps()
{
	std::ofstream out("Output.txt");

	predictionRaster = new float* [_height];

	for (int i = 0; i < _height; i++)
	{
		predictionRaster[i] = new float[_width];
		for (int j = 0; j < _width; j++)
		{

			//predictionRaster[i][j] = lRegression->testLR5(elevationMap->returnArray(i, j), slopeMap->returnArray(i, j), triMap->returnArray(i, j), aspectMap->returnArray(i, j), riversMap->returnArray(i, j));
			//predictionRaster[i][j] = lRegression->testLR2(elevationMap->returnArray(i, j), riversMap->returnArray(i, j));
			predictionRaster[i][j] = lRegression->lp1(elevationMap->returnArray(i, j));
			out << predictionRaster[i][j] << " ";
		}
		out << std::endl;
	}

	out.close();
}

void Prediction::freePRaster()
{
	for (int i = 0; i < _height; i++)
	{
		delete [] predictionRaster[_height];
	}
	delete [] predictionRaster;

	std::cout << "Memory free'd - prediction raster ----------- " << std::endl;
}

void Prediction::setSamplePR1(double pr1)
{
	_samplePR1 = pr1;
}

void Prediction::setSamplePR2(double pr2)
{
	_samplePR2 = pr2;
}

void Prediction::setPerecnetRandomSites(double percent)
{
	_perRSites = percent;

	_nRSites = _nSites * percent;
}

int Prediction::getNHits()
{
	return _nHits;
}


float Prediction::getWV1()
{
	return _wv1;
}

float Prediction::getWV2()
{
	return _wv2;
}

float Prediction::getWV3()
{
	return _wv3;
}

float Prediction::getWV4()
{
	return _wv4;
}

float Prediction::getWV5()
{
	return _wv5;
}

float Prediction::getWV6()
{
	return _wv6;
}

float Prediction::getWV7()
{
	return _wv7;
}

int Prediction::getHeight()
{
	return _height;
}

int Prediction::getWidth()
{
	return _width;
}

float Prediction::getXllcorner()
{
	return _xllcorner;
}

float Prediction::getYllcorner()
{
	return _yllcorner;
}

float Prediction::getCellSize()
{
	return _cellSize;
}

std::string Prediction::returnDir()
{
	std::string dir = _dir;

	return dir;
}

double Prediction::getGain()
{
	return _gain;
}

double Prediction::getQ1()
{
	return _q1;
}

double Prediction::getQ2()
{
	return _q2;
}

double Prediction::getPLand()
{
	return _pLand;
}

double Prediction::returnElevationMinPercent()
{
	return _elevationMinPercent;
}

double Prediction::returnElevationMaxPercent()
{
	return _elevationMaxPercent;
}
