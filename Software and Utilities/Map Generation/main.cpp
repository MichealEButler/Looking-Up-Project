#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "StartScr.h"
#include "Display.h"
#include "Input.h"
#include "MathFunctions.h"
#include "Prediction.h"
#include "Sites.h"
#include "Dataset.h"
#include "Output.h"
#include "RandomSites.h"
#include <SDL2/SDL.h>

StartScr* startscr = nullptr;
Display* display = nullptr;
Prediction* prediction = nullptr; // speninnes
Prediction* prediction2 = nullptr;
Prediction* prediction3 = nullptr;

Prediction* cairngorms = nullptr;

Output* summaryAll = nullptr;
Output* summaryRun = nullptr;

std::vector<RandomSites*> rSites;

std::vector<double> gainList;

double elevationMinP;
double elevationMaxP;

void allSolution();

int main(int argc, char* args[])
{
	//allSolution();

	//sets how many random site list wanted
	rSites = std::vector<RandomSites*>(10);

	for(int i = 0; i < 10; i++)
	{
		rSites[i] = new RandomSites;
		rSites[i]->createRandomSites(33, 0.5);
		rSites[i]->printAllSites();
	}

	SDL_Init(SDL_INIT_EVERYTHING);

	summaryAll = new Output();
	summaryAll->openFile("Output/summary.txt");

	startscr = new StartScr();

	gainList.clear();
	elevationMinP = 0;
	elevationMaxP = 0;

	for(int j = 0; j < 10; j++)
	{

		prediction = new Prediction();
		prediction->setDir("Input/Tweed/20m/");
		prediction->setWH(1750,1500);
		prediction->setXYC(305000, 625000, 20);
		prediction->setnSites(33);
		prediction->setPerecnetRandomSites(0.5);
		prediction->loadMaps(true);
		prediction->storeDatsets("Input/Tweed/20m/");
		prediction->storeDatasetsRandom("Input/Tweed/20m/", rSites[j]->returnVector());
		prediction->storePSites();
		//prediction->checkMapRanges();

		elevationMinP = prediction->returnElevationMinPercent();
		elevationMaxP = prediction->returnElevationMaxPercent();

		for(int i = 0; i < 1; i++)
		{

			//std::string sumFile = "Input/SPeninnes/Output/run" + std::to_string(i) + "summary.txt";
			//prediction->setFileWeightings(1180);
			prediction->setFileWeightings7(20);
			//prediction->checkMapRangesWeightings(i, false, false, false, false, false);
			prediction->checkMapRangesWeightings7(i, false, false, false, false, false, false, false, j);
			prediction->checkSitesState();
			prediction->calcGain();
			prediction->calcPLand();

			//std::cout << "Number of high potential locations = " << prediction->getNHits() << std::endl << std::endl;
			std::cout << "Tweed run " << i << " ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;

			//summaryAll->masterFileOut("Tweed", i, prediction->getWV1(), prediction->getWV2(), prediction->getWV3(), prediction->getWV4(), prediction->getWV5(), prediction->getGain(), prediction->getPLand());
			summaryAll->masterFileOut7("Tweed", i, prediction->getWV1(), prediction->getWV2(), prediction->getWV3(), prediction->getWV4(), prediction->getWV5(), prediction->getWV6(), prediction->getWV7(), prediction->getGain(), prediction->getPLand());

			gainList.push_back(prediction->getGain());
			//ummaryRun->openFile(sumFile);
			//summaryRun->runFileSummary("Peninnes", 0.1, 0.9, prediction->getWV1(), prediction->getWV2(), prediction->getWV3(), prediction->getWV4(), prediction->getWV5(), prediction->getGain());
/*
			if (prediction->getGain() >= 0.7)
			{
				display = new Display();

				display->initDisplay(" ", 700, 100, prediction->getWidth(), prediction->getHeight(), true, i, 1, prediction->returnDir());
				display->updateDisplay();
				display->renderDisplay(i, prediction->getWidth(), prediction->getHeight(), 1, prediction->returnDir());
				display->renderPresent();
				//display->handleEvents();

				display->clearRenderer();
				display->cleanDisplay();

				delete display;
			}
*/
			std::cout << "Successful! " << std::endl;
			//prediction->freePRaster();


			//summaryRun->closeFile(sumFile);

		}

		delete prediction;

		cairngorms = new Prediction();
		cairngorms->setDir("Input/Cairngorms/20m/");
		cairngorms->setWH(3000, 2500);
		cairngorms->setXYC(275000, 770000, 20);
		cairngorms->setnSites(33);
		cairngorms->setPerecnetRandomSites(0.5);
		cairngorms->loadMaps(false);
		cairngorms->storeDatsets("Input/Tweed/20m/");
		prediction->storeDatasetsRandom("Input/Tweed/20m/", rSites[j]->returnVector());
		cairngorms->setSamplePR1(elevationMinP);
		cairngorms->setSamplePR2(elevationMaxP);
		//cairngorms->storePSites();
		//prediction->checkMapRanges();

		for (int i = 0; i < 1; i++)
		{
			//std::string sumFile = "Input/Cairngorms/Output/run_" + std::to_string(i) + "_summary.txt";
			//cairngorms->setFileWeightings(1180);
			cairngorms->setFileWeightings7(20);
			//cairngorms->checkMapRangesWeightings(i, true, false, false, false, false);
			cairngorms->checkMapRangesWeightings7(i, true, false, false, false, false, false, false, j);
			//cairngorms->checkSitesState();
			//cairngorms->calcGain();
			//std::cout << "Number of high potential locations = " << cairngorms->getNHits() << std::endl << std::endl;
			std::cout << "Cairngorms run " << i << " ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
			cairngorms->calcPLand();

			//summaryAll->masterFileOut("Cairngorms", i, cairngorms->getWV1(), cairngorms->getWV2(), cairngorms->getWV3(), cairngorms->getWV4(), cairngorms->getWV5(), gainList[i], cairngorms->getPLand());
			summaryAll->masterFileOut7("Cairngorms", i, cairngorms->getWV1(), cairngorms->getWV2(), cairngorms->getWV3(), cairngorms->getWV4(), cairngorms->getWV5(), cairngorms->getWV6(), cairngorms->getWV7(), gainList[i], cairngorms->getPLand());

			//summaryRun->openFile(sumFile);
			//summaryRun->runFileSummary("Cairngorms", 0.1, 0.9, cairngorms->getWV1(), cairngorms->getWV2(), cairngorms->getWV3(), cairngorms->getWV4(), cairngorms->getWV5(), prediction->getGain());

/*
			if (gainList[i] >= 0.7)
			{
				display = new Display();

				display->initDisplay(" ", 700, 100, cairngorms->getWidth(), cairngorms->getHeight(), true, i, 1, cairngorms->returnDir());
				display->updateDisplay();
				display->renderDisplay(i, cairngorms->getWidth(), cairngorms->getHeight(), 1, cairngorms->returnDir());
				display->renderPresent();
				//display->handleEvents();

				display->clearRenderer();
				display->cleanDisplay();

				delete display;

				//std::cout << " success " << std::endl;
				//cairngorms->freePRaster();
				//summaryRun->closeFile(sumFile);
			}
*/
		}

		delete cairngorms;
	}

	startscr->setDisplay();

	delete startscr;
	//delete cairngorms;


	//delete array of randomSites objects
	for(int i = 0; i < rSites.size(); i++)
	{
			delete rSites[i];
	}

	return 0;
}

void allSolution()
{
	//initialise variables
	std::string line;
	std::ofstream file("Input/scalers.txt");

	int varSum = 0;
	int numComs = 0;

	int vecRow = 0;

	std::vector<std::string> finalList;

	std::vector<std::vector<int>> vect(5);

	double allArray[5];

	for (int a = 0; a < 10; a++)
	{
		for (int b = 0; b < 10; b++)
		{
			allArray[0] = a;
			allArray[1] = b;
			allArray[2] = b;
			allArray[3] = b;
			allArray[4] = b;

			varSum = allArray[0] + allArray[1] + allArray[2] + allArray[3] + allArray[4];

			if (varSum == 10)
			{
				std::cout << allArray[0] / 10 << " " << allArray[1] / 10 << " " << allArray[2] / 10 << " " << allArray[3] / 10 << " " << allArray[4] / 10 << std::endl;
				file << allArray[0] / 10 << " " << allArray[1] / 10 << " " << allArray[2] / 10 << " " << allArray[3] / 10 << " " << allArray[4] / 10 << std::endl;
				numComs++;
			}

			for (int c = 0; c < 10; c++)
			{
				allArray[0] = a;
				allArray[1] = b;
				allArray[2] = c;
				allArray[3] = c;
				allArray[4] = c;

				varSum = allArray[0] + allArray[1] + allArray[2] + allArray[3] + allArray[4];

				if (varSum == 10)
				{
					std::cout << allArray[0] / 10 << " " << allArray[1] / 10 << " " << allArray[2] / 10 << " " << allArray[3] / 10 << " " << allArray[4] / 10 << std::endl;
					file << allArray[0] / 10 << " " << allArray[1] / 10 << " " << allArray[2] / 10 << " " << allArray[3] / 10 << " " << allArray[4] / 10 << std::endl;
					numComs++;
				}

				for (int d = 0; d < 10; d++)
				{
					allArray[0] = a;
					allArray[1] = b;
					allArray[2] = c;
					allArray[3] = d;
					allArray[4] = d;

					varSum = allArray[0] + allArray[1] + allArray[2] + allArray[3] + allArray[4];

					if (varSum == 10)
					{
						std::cout << allArray[0] / 10 << " " << allArray[1] / 10 << " " << allArray[2] / 10 << " " << allArray[3] / 10 << " " << allArray[4] / 10 << std::endl;
						file << allArray[0] / 10 << " " << allArray[1] / 10 << " " << allArray[2] / 10 << " " << allArray[3] / 10 << " " << allArray[4] / 10 << std::endl;
						numComs++;
					}

					for (int e = 0; e < 10; e++)
					{
						allArray[0] = a;
						allArray[1] = b;
						allArray[2] = c;
						allArray[3] = d;
						allArray[4] = e;

						varSum = allArray[0] + allArray[1] + allArray[2] + allArray[3] + allArray[4];

						if (varSum == 10)
						{
							std::cout << allArray[0] / 10 << " " << allArray[1] / 10 << " " << allArray[2] / 10 << " " << allArray[3] / 10 << " " << allArray[4] / 10 << std::endl;
							file << allArray[0] / 10 << " " << allArray[1] / 10 << " " << allArray[2] / 10 << " " << allArray[3] / 10 << " " << allArray[4] / 10 << std::endl;
							numComs++;
						}

					}
				}
			}
		}


	}

	//have an array containing 5 numbers
	//iterate through the whole with every combination
	//add these together a check if they are equal to 1
	//if they are add to a seperate list

	file.close();

	std::cout << "Number of combinations = " << numComs << std::endl;
	std::cout << "Size of vector list = " << vect.size() << std::endl;
}
