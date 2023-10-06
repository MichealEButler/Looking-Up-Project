//stores one itearation of sites to be used in the generation of sites used for the predictions
//returns list of the sites to be used in that iteration

#ifndef RANDOMSITES_H
#define RANDOMSITES_H

#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <algorithm>

class RandomSites
{
public:
  RandomSites();
  ~RandomSites();

  void createRandomSites(int nSites, float percentage);
  void printAllSites();

  int returnRandomSite(int place);
  std::vector<int> returnVector();

private:
  std::vector<int> _randomSites;

  int _rnSites; // number of sites calculate to actual number reduced by the percent of those we are using in creating the models
  float _percentage;
};

#endif
