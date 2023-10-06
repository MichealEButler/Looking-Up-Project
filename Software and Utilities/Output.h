#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <cstring>

class Output
{
public:
    Output();
    ~Output();
    void openFile(std::string title);
    void sitesOutput(double state, double x, double y, double e1, double e2, double e3, double e4, double e5);
    void masterFileOut(std::string run, int iteration, double weight1, double weight2, double weight3, double weight4, double weight5, double gain, double pLand);
    void masterFileOut7(std::string run,  int iteration, double weight1, double weight2, double weight3, double weight4, double weight5, double weight6, double weight7, double gain, double pLand);
    void runFileSummary(std::string run, double q1, double q2, double weight1, double weight2, double weight3, double weight4, double weight5, double gain);
    void closeFile(std::string title);

    std::ofstream file;
    std::ofstream f;
private:

};

#endif
