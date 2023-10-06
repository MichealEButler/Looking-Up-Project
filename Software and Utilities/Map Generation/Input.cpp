#include "Input.h"

Input::Input()
{
	_x1 = 0;
	_x2 = 0;
	_y1 = 0;
	_y2 = 0;

	_width = 0;
	_height = 0;
	_xllcorner = 0;
	_yllcorner = 0;

	_xi = 0;
	_yi = 0;

	_cSize = 0.0f;

	_value = 0.0f;

	_valueArray = 0;
	_siteArray = 0;

	_minVar = 0.0;
	_maxVar = 0.0;

	_variables.clear();

	_id.clear();
	_x.clear();
	_y.clear();
	_e1.clear();
	_e2.clear();
	_e3.clear();
	_e4.clear();
	_e5.clear();
	_e6.clear();
	_e7.clear();
}

Input::~Input()
{

}

void Input::loadASC(const char* filename)
{
	std::ifstream file(filename);

	//read (out)
	if (file.is_open())
	{

		std::string line;
		int nLines = 5; // how many lines to display

		std::cout << "File contains: " << std::endl;

		for (int i = 0; i < nLines; i++)
		{
			getline(file, line);
			printf("%s", line.c_str());
			std::cout << std::endl;
		}
		std::cout << "........" << std::endl;

		file.close();
	}
}

void Input::storeASC(std::string filename,int height, int width, int adLines)
{
	_variables.clear();

	std::string line;
	std::ifstream file(filename);

	_width = width;
	_height = height;

	for (int i = 0; i < 5+adLines; i++)
	{
		getline(file, line);
	}


	if (file.is_open())
	{

		_valueArray = new float* [height];

		for (int i = 0; i < height; i++)
		{
			_valueArray[i] = new float[width];

			for (int j = 0; j < width; j++)
			{
				file >> _valueArray[i][j];

				if (_valueArray[i][j] >= 0) // if nodata value is present in file
				{
					_variables.push_back(_valueArray[i][j]);
				}

			}
		}

		_maxVar = *std::max_element(_variables.begin(), _variables.end());
		_minVar = *std::min_element(_variables.begin(), _variables.end());
	}
	else
	{
		std::cout << "Error 1: Failed to load file. " << std::endl;
	}

}

void Input::storeOutFile(const char* filename, int height, int width, int adLines, int iteration, std::string dir)
{
	std::string line;
	//std::ifstream file(filename);

	std::string p1 = dir + "Output/Run";
	std::string p2 = ".asc";
	std::ifstream file(p1 + std::to_string(iteration) + p2);

	_width = width;
	_height = height;

	for (int i = 0; i < 5; i++)
	{
		getline(file, line);
	}

	if (file.is_open())
	{

		_valueArray = new float* [height];

		for (int i = 0; i < height; i++)
		{
			_valueArray[i] = new float[width];
			for (int j = 0; j < width; j++)
			{
				file >> _valueArray[i][j];
			}
		}
	}
	else
	{
		std::cout << "Error 1: Failed to load file. " << std::endl;
	}
}

void Input::loadSites(std::string filename, int x, int y)
{
	std::string line;
	std::ifstream file(filename);

	double input = 0;

	_xi = x;
	_yi = y;

	for (int i = 0; i < 1; i++)
	{
		getline(file, line);
	}

	if (file.is_open())
	{

		for (int i = 0; i < x; i++)
		{
			file >> input;
			_id.push_back(input);
			file >> input;
			_x.push_back(input);
			file >> input;
			_y.push_back(input);
			file >> input;
			_e1.push_back(input);
			file >> input;
			_e2.push_back(input);
			file >> input;
			_e3.push_back(input);
			file >> input;
			_e4.push_back(input);
			file >> input;
			_e5.push_back(input);
			//additional input due to extra columns in file (7 variables etc.)
			file >> input;
			_e6.push_back(input);
			file >> input;
			_e7.push_back(input);
		}
	}
}

void Input::readInFile(const char* filename, int line)
{
	std::ifstream file(filename);

	//read (out)
	if (file.is_open())
	{

		std::string line;
		int nLines = 5; // how many lines to display

		std::cout << "File contains: " << std::endl;

		for (int i = 0; i < nLines; i++)
		{
			getline(file, line);
			printf("%s", line.c_str());
			std::cout << std::endl;
		}
		std::cout << "........" << std::endl;

		file.close();
	}
}

void Input::printStored()
{
	/*
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			std::cout << _valueArray[i][j];
		}
		std::cout << std::endl;
	}
	*/

	for (int i = 0; i < _xi; i++)
	{
		for (int j = 0; j < _yi; j++)
		{
			std::cout << _siteArray[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Input::renderInput(SDL_Renderer* renderer)
{
	int value;

	for (int i = 0; i < 300; i++)
	{
		for (int j = 0; j < 400; j++)
		{
			value = _valueArray[i][j];

			switch(value)
			{
			case 1:
				//blue
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				SDL_RenderDrawPoint(renderer, j, i);
				break;
			case 2:
				SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
				SDL_RenderDrawPoint(renderer, j, i);
				break;
			case 3:
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderDrawPoint(renderer, j, i);
				break;
			case 4:
				SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
				SDL_RenderDrawPoint(renderer, j, i);
				break;
			case 5:
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderDrawPoint(renderer, j, i);
				break;
			default:
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawPoint(renderer, j, i);

			}

		}
	}
}

void Input::renderInput2(SDL_Renderer* renderer)
{
	float value;

	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			value = _valueArray[i][j];

			if (value <= 0.2)
			{
				//blue
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				SDL_RenderDrawPoint(renderer, j*2, i*2);
				SDL_RenderDrawPoint(renderer, j*2, (i*2) + 1);
				SDL_RenderDrawPoint(renderer, (j*2) + 1, i*2);
				SDL_RenderDrawPoint(renderer, (j*2) +1, (i*2) +1);
			}
			if (value > 0.2 && value <= 0.4)
			{
				SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
				SDL_RenderDrawPoint(renderer, j * 2, i * 2);
				SDL_RenderDrawPoint(renderer, j * 2, (i * 2) + 1);
				SDL_RenderDrawPoint(renderer, (j * 2) + 1, i * 2);
				SDL_RenderDrawPoint(renderer, (j * 2) + 1, (i * 2) + 1);
			}
			if (value > 0.4 && value <= 0.6)
			{
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderDrawPoint(renderer, j * 2, i * 2);
				SDL_RenderDrawPoint(renderer, j * 2, (i * 2) + 1);
				SDL_RenderDrawPoint(renderer, (j * 2) + 1, i * 2);
				SDL_RenderDrawPoint(renderer, (j * 2) + 1, (i * 2) + 1);
			}
			if (value > 0.6 && value <= 0.8)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
				SDL_RenderDrawPoint(renderer, j * 2, i * 2);
				SDL_RenderDrawPoint(renderer, j * 2, (i * 2) + 1);
				SDL_RenderDrawPoint(renderer, (j * 2) + 1, i * 2);
				SDL_RenderDrawPoint(renderer, (j * 2) + 1, (i * 2) + 1);
			}
			if (value > 0.8)
			{
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderDrawPoint(renderer, j * 2, i * 2);
				SDL_RenderDrawPoint(renderer, j * 2, (i * 2) + 1);
				SDL_RenderDrawPoint(renderer, (j * 2) + 1, i * 2);
				SDL_RenderDrawPoint(renderer, (j * 2) + 1, (i * 2) + 1);
			}

		}
	}
}

void Input::renderInput3(SDL_Renderer* renderer)
{
	float value;

	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			value = _valueArray[i][j];

			if (value <= 0.2)
			{
				//blue
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				SDL_RenderDrawPoint(renderer, j, i);
			}
			if (value > 0.2 && value <= 0.4)
			{
				SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
				SDL_RenderDrawPoint(renderer, j, i);
			}
			if (value > 0.4 && value <= 0.6)
			{
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderDrawPoint(renderer, j, i);
			}
			if (value > 0.6 && value <= 0.8)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
				SDL_RenderDrawPoint(renderer, j, i);
			}
			if (value > 0.8)
			{
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderDrawPoint(renderer, j, i);

			}

		}
	}
}

void Input::setCoord(int width, int height, float xllcorner, float yllcorner, float cellSize)
{
	_width = width;
	_height = height;
	_xllcorner = xllcorner;
	_yllcorner = yllcorner;
	_cSize = cellSize;
}

void Input::resetCoord()
{
	int value = 0;

	for (int i = 0; i < _x.size(); i++)
	{
		value = _x[i] - _xllcorner;
		value = value / _cSize;
		_newX.push_back(value);
	}

	for (int i = 0; i < _y.size(); i++)
	{
		value = _y[i] - _yllcorner;
		value = _height - (value / _cSize);
		_newY.push_back(value);
	}

	for (int i = 0; i < _x.size(); i++)
	{
		std::cout << " x = " << _newX[i];
		std::cout << " y = " << _newY[i];

	}
}

float Input::returnArray(int x, int y)
{
	return _valueArray[x][y];
}

void Input::printSiteID()
{
	for (int i = 0; i < _id.size(); i++)
	{
		std::cout << _id[i];
	}

	std::cout << std::endl;
}

void Input::printSiteX()
{
	for (int i = 0; i < _x.size(); i++)
	{
		std::cout << _x[i];
	}

	std::cout << std::endl;
}

void Input::printSiteY()
{
	for (int i = 0; i < _y.size(); i++)
	{
		std::cout << _y[i];
	}

	std::cout << std::endl;
}

void Input::printSiteE1()
{
	for (int i = 0; i < _e1.size(); i++)
	{
		std::cout << _e1[i];
	}

	std::cout << std::endl;
}
void Input::printSiteE2()
{
	for (int i = 0; i < _e2.size(); i++)
	{
		std::cout << _e2[i];
	}

	std::cout << std::endl;
}

void Input::printSiteE3()
{
	for (int i = 0; i < _e3.size(); i++)
	{
		std::cout << _e3[i];
	}

	std::cout << std::endl;
}

void Input::printSiteE4()
{
	for (int i = 0; i < _e4.size(); i++)
	{
		std::cout << _e4[i];
	}

	std::cout << std::endl;
}

void Input::printSiteE5()
{
	for (int i = 0; i < _e5.size(); i++)
	{
		std::cout << _e5[i];
	}

	std::cout << std::endl;
}

void Input::printSiteE6()
{
	for (int i = 0; i < _e6.size(); i++)
	{
		std::cout << _e6[i];
	}

	std::cout << std::endl;
}

void Input::printSiteE7()
{
	for (int i = 0; i < _e7.size(); i++)
	{
		std::cout << _e7[i];
	}

	std::cout << std::endl;
}

double Input::returnID(int i)
{
	return _id[i];
}

double Input::returnX(int i)
{
	return _x[i];
}

double Input::returnY(int i)
{
	return _y[i];
}
double Input::returnE1(int i)
{
	return _e1[i];
}

double Input::returnE2(int i)
{
	return _e2[i];
}

double Input::returnE3(int i)
{
	return _e3[i];
}

double Input::returnE4(int i)
{
	return _e4[i];
}

double Input::returnE5(int i)
{
	return _e5[i];
}

double Input::returnE6(int i)
{
	return _e6[i];
}

double Input::returnE7(int i)
{
	return _e7[i];
}

double Input::returnNX(int i)
{
	return _newX[i];
}

double Input::returnNY(int i)
{

	return _newY[i];
}

int Input::sizeX()
{
	return _xi;
}

double Input::returnMinVar()
{
	return _minVar;
}

double Input::returnMaxVar()
{
	return _maxVar;
}
