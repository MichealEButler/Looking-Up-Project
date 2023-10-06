#include "RandomSites.h"

RandomSites::RandomSites()
{
  _randomSites.clear();

  _rnSites = 0;
  _percentage = 0;
}

RandomSites::~RandomSites()
{

}

void RandomSites::createRandomSites(int nSites, float percentage)
{
  _percentage = percentage;
  _rnSites = nSites * percentage;

  std::cout << "Number of random sites = " << _rnSites << std::endl << std::endl;

  std::vector<int> array;
  array.clear();

  for(int i = 0; i < nSites; i++)
  {
    array.push_back(i);
  }

  std::random_device rd;
  std::mt19937 mt(rd());

  std::shuffle(std::begin(array), std::end(array), mt);

  for(int i = 0; i < _rnSites; i++)
  {
    //std::cout << array[i] << " ";
    _randomSites.push_back(array[i]);
  }
  //std::cout << std::endl;
}

void RandomSites::printAllSites()
{
  for(int i = 0; i < _randomSites.size(); i++)
  {
    std::cout << _randomSites[i] << " ";
  }
  std::cout << std::endl;
}

int RandomSites::returnRandomSite(int place)
{
  return _randomSites[place];
}

std::vector<int> RandomSites::returnVector()
{
  return _randomSites;
}
