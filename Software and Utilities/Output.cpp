#include "Output.h"

Output::Output()
{

}

Output::~Output()
{

}

void Output::openFile(std::string title)
{
    file.open(title);
}

void Output::sitesOutput(double state, double x, double y, double e1, double e2, double e3, double e4, double e5)
{
    file << state << ", ";
    file << x << ", ";
    file << y << ", ";
    file << e1 << ", ";
    file << e2 << ", ";
    file << e3 << ", ";
    file << e4 << ", ";
    file << e5 << " " << std::endl;

    file.close();
}

void Output::masterFileOut(std::string run,  int iteration, double weight1, double weight2, double weight3, double weight4, double weight5, double gain, double pLand)
{
    file << run << " run " << iteration << ", ";
    file << weight1 << ", ";
    file << weight2 << ", ";
    file << weight3 << ", ";
    file << weight4 << ", ";
    file << weight5 << ", ";
    file << gain << ", ";
    file << pLand << " " << std::endl;
}

void Output::masterFileOut7(std::string run,  int iteration, double weight1, double weight2, double weight3, double weight4, double weight5, double weight6, double weight7, double gain, double pLand)
{
    file << run << " run " << iteration << ", ";
    file << weight1 << ", ";
    file << weight2 << ", ";
    file << weight3 << ", ";
    file << weight4 << ", ";
    file << weight5 << ", ";
    file << weight6 << ", ";
    file << weight7 << ", ";
    file << gain << ", ";
    file << pLand << " " << std::endl;
}

void Output::runFileSummary(std::string run, double q1, double q2, double weight1, double weight2, double weight3, double weight4, double weight5, double gain)
{
    file << run << ", ";
    file << q1 << ", ";
    file << q2 << ", ";
    file << weight1 << ", ";
    file << weight2 << ", ";
    file << weight3 << ", ";
    file << weight4 << ", ";
    file << weight5 << ", ";
    file << gain << " " << std::endl;
}

void Output::closeFile(std::string title)
{
    file.close();
}
