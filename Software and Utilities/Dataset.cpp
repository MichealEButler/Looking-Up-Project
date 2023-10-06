#include "Dataset.h"

Dataset::Dataset()
{
	mfunc = new MathFunctions();

	_quant1 = 0.0;
	_quant2 = 0.0;

	_quart1 = 0.0;
	_quart2 = 0.0;

	_pRange1 = 0.0;
	_pRange2 = 0.0;

	_median = 0.0;
	_mean = 0.0;
	_var = 0.0;

	_dataset.clear();
}

Dataset::~Dataset()
{

}

void Dataset::storeDataset(std::string filename)
{
	std::ifstream file(filename);
	std::string temp;

	//read (out)
	while(getline(file, temp))
	{
		//std::cout << "In loop " << std::endl;
		double in = atof(temp.c_str());
		_dataset.push_back(in);
	}

	//std::cout << "Size of dataset = " << _dataset.size() << std::endl;

	for (int i = 0; i < _dataset.size(); i++)
	{
		//std::cout << _dataset[i] << std::endl;
	}

	file.close();
}

void Dataset::resetDataset(std::vector<int> randomSites)
{
	std::vector<double> temp;

	for(int i = 0; i < randomSites.size(); i++)
	{
		int n = randomSites[i];
		temp.push_back(_dataset[n]);
	}

	_dataset.clear();

	for(int i = 0; i < randomSites.size(); i++)
	{
		double j = temp[i];
		_dataset.push_back(j);
	}

}

void Dataset::setVar(double var)
{
	_var = var;
}

void Dataset::setName(std::string name)
{
	_name = name;
}

void Dataset::setID(int id)
{
	_id = id;
}

void Dataset::calcQuarts()
{
	mfunc->setQuartiles(_dataset);

	_quart1 = mfunc->getQ1();

	_quart2 = mfunc->getQ2();
}

void Dataset::calcQuantes(double q1, double q2)
{
	mfunc->calcQuantile(q1, _dataset);
	_quant1 = mfunc->getQuant();

	mfunc->calcQuantile(q2, _dataset);
	_quant2 = mfunc->getQuant();
}

void Dataset::printInfo()
{
	std::cout << _name << std::endl << std::endl;

	std::cout << "Q1 = " << _quant1 << std::endl;
	std::cout << "Q2 = " << _quant2 << std::endl << std::endl;

	std::cout << "Quartile 1 (25%) = " << _quart1 << std::endl;
	std::cout << "Quartile 3 (75%) = " << _quart2 << std::endl;

	std::cout << "--------------------------" << std::endl << std::endl;

}

void Dataset::percentRange(double min, double max)
{
	//converts current q1 and q3 into percentage of overall landscape range

	double s = max - min;
	double i = _quant1 - min;
	double j = _quant2 - min;

	_pRange1 = i / s;
	_pRange2 = j / s;

	//std::cout << "Pecentage range = " << _pRange1 << " -- " << _pRange2 << std::endl;
}


void Dataset::recalcQuants(double min, double max, double pR1, double pR2)
{
	double s = max - min;

	_quant1 = (s * pR1) + min;
	_quant2 = (s * pR2) + min;
}

double Dataset::getQuant1()
{
	return _quant1;
}

double Dataset::getQuant2()
{
	return _quant2;
}

double Dataset::getQuart1()
{
	return _quart1;
}

double Dataset::getQuart2()
{
	return _quart2;
}

double Dataset::getMedian()
{
	return _median;
}

double Dataset::getMean()
{
	return _mean;
}

double Dataset::getVar()
{
	return _var;
}

std::string Dataset::getName()
{
	return _name;
}
int Dataset::getID()
{
	return _id;
}
