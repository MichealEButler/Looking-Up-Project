#include "Sites.h"

Sites::Sites()
{
	_nSites = 0;

	_id = 0;
	_x = 0;
	_y = 0;

}

Sites::~Sites()
{

}

void Sites::countNoSites(const char* filename)
{
	std::string line;
	std::ifstream file(filename);

	while (std::getline(file, line))
	{
		++_nSites;
	}

	file.close();
	//std::cout << "Number of sites in file = " << _nSites - 1 << std::endl;
}

void Sites::readSitesFile(const char* filename, int x)
{
	lSites = std::vector<Point*>(_nSites);

	std::string line;
	std::ifstream file(filename);

	double input = 0;

	for (int i = 0; i < 1; i++)
	{
		getline(file, line);
	}

	if (file.is_open())
	{

		for (int i = 0; i < x; i++)
		{
			//create new point object and to the vector
			//go through each line and assign id, x, and y

			
			lSites[i] = new Point();

			file >> input;
			lSites[i]->setID(input);
			file >> input;
			lSites[i]->setX(input);
			file >> input;
			lSites[i]->setY(input);
		}
	}
	file.close();
}

void Sites::outSites()
{
	std::cout << "ID        " << "X          " << "Y          " << std::endl;

	for (int i = 0; i < lSites.size(); i++)
	{
		std::cout << lSites[i]->getID() << " ";
		std::cout << lSites[i]->getX() << " ";
		std::cout << lSites[i]->getY() << std::endl;
	}
}

int Sites::getNSites()
{
	return _nSites;
}