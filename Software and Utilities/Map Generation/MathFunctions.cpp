#include "MathFunctions.h"

MathFunctions::MathFunctions()
{
    _nsites = 0;

    _b0 = 0.0;
    _b1 = 0.0;
    _b2 = 0.0;
    _b3 = 0.0;
    _b4 = 0.0;
    _b5 = 0.0;

    _q1 = 0.0;
    _q2 = 0.0;
    _q3 = 0.0;
    _quant = 0.0;
    _median = 0.0;
}

MathFunctions::~MathFunctions()
{

}

void MathFunctions::linearRegression()
{
    //test linear relationship between presence and independent
}

void MathFunctions::logRegression() //original regression from https://www.analyticsvidhya.com/blog/2020/04/machine-learning-using-c-linear-logistic-regression/
{
	double x1[] = { 2.7810836, 1.465489372, 3.396561688, 1.38807019, 3.06407232,7.627531214,5.332441248,6.922596716,8.675418651 ,7.673756466 };
	double x2[] = { 2.550537003,2.362125076,4.400293529,1.850220317,3.005305973,2.759262235,2.088626775,1.77106367,-0.2420686549,3.508563011 };
	double y[] = { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 };

    std::vector<double>error; // for storing the error values
    double err;    // for calculating error on each stage
    double b0 = 0; // initializing b0
    double b1 = 0; // initializing b1
    double b2 = 0; // initializing b2
    double alpha = 0.01; // initializing our learning rate
    double  e = 2.71828;

        /*Training Phase*/
        for (int i = 0; i < 40; i++) { //Since there are 10 values in our dataset and we want to run for 4 epochs so total for loop run 40 times
            int idx = i % 10;   //for accessing index after every epoch
            double p = -(b0 + b1 * x1[idx] + b2 * x2[idx]); //making the prediction
            double pred = 1 / (1 + pow(e, p)); //calculating final prediction applying sigmoid
            err = y[idx] - pred;  //calculating the error
            b0 = b0 - alpha * err * pred * (1 - pred) * 1.0;   //updating b0
            b1 = b1 + alpha * err * pred * (1 - pred) * x1[idx];//updating b1
            b2 = b2 + alpha * err * pred * (1 - pred) * x2[idx];//updating b2
            std::cout << "B0=" << b0 << " " << "B1=" << b1 << " " << "B2=" << b2 << " error=" << err << std::endl;// printing values after every step
            error.push_back(err);
        }

    sort(error.begin(), error.end());//custom sort based on absolute error difference
    std::cout << "Final Values are: " << "B0=" << b0 << " " << "B1=" << b1 << " " << "B2=" << b2 << " error=" << error[0];

    /*Testing Phase*/
    double test1, test2; //enter test x1 and x2
    std::cin >> test1 >> test2;
    double pred = b0 + b1 * test1 + b2 * test2; //make prediction
    std::cout << "The value predicted by the model= " << pred << std::endl;
    if (pred > 0.5)
        pred = 1;
    else
        pred = 0;
    std::cout << "The class predicted by the model= " << pred;
}

void MathFunctions::logRegression3() //implementation with 3 values
{
    double x1[] = { 2.7810836, 1.465489372, 3.396561688, 1.38807019, 3.06407232,7.627531214,5.332441248,6.922596716,8.675418651 ,7.673756466 };
    double x2[] = { 2.550537003,2.362125076,4.400293529,1.850220317,3.005305973,2.759262235,2.088626775,1.77106367,-0.2420686549,3.508563011 };
    double x3[] = { 2.250537003,2.562125076,4.100293529,1.550220317,3.305305973,2.659262235,2.688626775,1.67106367,-0.1420686549,3.208563011 };
    double y[] = { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 };

    std::vector<double>error; // for storing the error values
    double err;    // for calculating error on each stage
    double b0 = 0; // initializing b0
    double b1 = 0; // initializing b1
    double b2 = 0; // initializing b2
    double b3 = 0;
    double alpha = 0.01; // initializing our learning rate
    double  e = 2.71828;

    /*Training Phase*/
    for (int i = 0; i < 40; i++) { //Since there are 10 values in our dataset and we want to run for 4 epochs so total for loop run 40 times
        int idx = i % 10;   //for accessing index after every epoch
        double p = -(b0 + b1 * x1[idx] + b2 * x2[idx] + b3 * x3[idx]); //making the prediction
        double pred = 1 / (1 + pow(e, p)); //calculating final prediction applying sigmoid
        err = y[idx] - pred;  //calculating the error
        b0 = b0 - alpha * err * pred * (1 - pred) * 1.0;   //updating b0
        b1 = b1 + alpha * err * pred * (1 - pred) * x1[idx];//updating b1
        b2 = b2 + alpha * err * pred * (1 - pred) * x2[idx];//updating b2
        b3 = b3 + alpha * err * pred * (1 - pred) * x3[idx];
        std::cout << "B0=" << b0 << " " << "B1=" << b1 << " " << "B2=" << b2 << "B3 =" << b3 << "error = " << err << std::endl;// printing values after every step
        error.push_back(err);
    }

    sort(error.begin(), error.end());//custom sort based on absolute error difference
    std::cout << "Final Values are: " << "B0=" << b0 << " " << "B1=" << b1 << " " << "B2=" << b2 << "B3=" << b3 << " error=" << error[0];

    /*Testing Phase*/
    double test1, test2, test3; //enter test x1 x2 and x3
    std::cin >> test1 >> test2 >> test3;
    double pred = b0 + b1 * test1 + b2 * test2 + b3 * test3; //make prediction
    std::cout << "The value predicted by the model= " << pred << std::endl;
    if (pred > 0.5)
        pred = 1;
    else
        pred = 0;
    std::cout << "The class predicted by the model= " << pred;
}

void MathFunctions::logRegression5(std::vector<double> y, std::vector<double> x1, std::vector<double> x2, std::vector<double> x3, std::vector<double> x4, std::vector<double> x5, int values)
{
    std::vector<double>error; // for storing the error values
    double err;    // for calculating error on each stage
    double b0 = 0; 
    double b1 = 0; 
    double b2 = 0; 
    double b3 = 0;
    double b4 = 0;
    double b5 = 0;
    double alpha = 0.01; // initializing our learning rate
    double  e = 2.71828;

    int epochs = 10 * values;

    /*Training Phase*/
    for (int i = 0; i < epochs; i++) {
        //for accessing index after every epoch
        int idx = i % values;

        //making the prediction
        double p = -(b0 + b1 * x1[idx] + b2 * x2[idx] + b3 * x3[idx] + b4 * x4[idx] + b5 * x5[idx]);

        //calculating final prediction applying sigmoid
        double pred = 1 / (1 + pow(e, p)); 

        //calculating the error
        err = y[idx] - pred;  
        b0 = b0 - alpha * err * pred * (1 - pred) * 1.0;   
        b1 = b1 + alpha * err * pred * (1 - pred) * x1[idx];
        b2 = b2 + alpha * err * pred * (1 - pred) * x2[idx];
        b3 = b3 + alpha * err * pred * (1 - pred) * x3[idx];
        b4 = b4 + alpha * err * pred * (1 - pred) * x4[idx];
        b5 = b5 + alpha * err * pred * (1 - pred) * x5[idx];
        std::cout << "B0=" << b0 << " " << "B1=" << b1 << " " << "B2=" << b2 << "B3 =" << b3 << "B4 =" << b4 << "B5 =" << b5 << "error = " << err << std::endl;
        error.push_back(err);
    }

    //custom sort based on absolute error difference
    sort(error.begin(), error.end());

    std::cout << "Final Values are: " << "B0=" << b0 << " " << "B1=" << b1 << " " << "B2=" << b2 << "B3=" << b3 << "B4=" << b4 << "B5=" << b5 << " error=" << error[0] << std::endl;

    _b0 = b0;
    _b1 = b1;
    _b2 = b2;
    _b3 = b3;
    _b4 = b4;
    _b5 = b5;
}

void MathFunctions::logRegressionSites(std::vector<double> y, std::vector<double> x1, std::vector<double> x2, int values)
{
    std::vector<double>error; // for storing the error values
    double err;    // for calculating error on each stage
    double b0 = 0; // initializing b0
    double b1 = 0; // initializing b1
    double b2 = 0; // initializing b2
    double alpha = 0.01; // initializing our learning rate
    double  e = 2.71828;

    int epoch = 10 * values;

    /*Training Phase*/
    for (int i = 0; i < epoch; i++) { //Since there are 10 values in our dataset and we want to run for 4 epochs so total for loop run 40 times
        int idx = i % values;   //for accessing index after every epoch
        double p = -(b0 + b1 * x1[idx] + b2 * x2[idx]); //making the prediction
        double pred = 1 / (1 + pow(e, p)); //calculating final prediction applying sigmoid
        err = y[idx] - pred;  //calculating the error
        b0 = b0 - alpha * err * pred * (1 - pred) * 1.0;   //updating b0
        b1 = b1 + alpha * err * pred * (1 - pred) * x1[idx];//updating b1
        b2 = b2 + alpha * err * pred * (1 - pred) * x2[idx];//updating b2
        std::cout << "B0=" << b0 << " " << "B1=" << b1 << " " << "B2=" << b2 << " error=" << err << std::endl;// printing values after every step
        error.push_back(err);
    }

    sort(error.begin(), error.end());//custom sort based on absolute error difference
    std::cout << "Final Values are: " << "B0=" << b0 << " " << "B1=" << b1 << " " << "B2=" << b2 << " error=" << error[0];

    _b0 = b0;
    _b1 = b1;
    _b5 = b2;
}

double MathFunctions::testLR2(double x1, double x5)
{

    //double pred = _b0 + _b1 * x1 + _b5 * x5;
    double pred = -37.03745916 + 0.04794891 * x1 + 0.26990113 * x5;

    //cout << "Prediction = " << pred << endl;

    return pred;
}

double MathFunctions::testLR5(double x1, double x2, double x3, double x4, double x5)
{
  
    //double pred = _b0 + _b1 * x1 + _b2 * x2 + _b3 * x3 + _b4 * x4 +_b5 * x5; 
    double pred = -57.46813755 + 0.15695115 * x1 + 1.09106017 * x2 + -0.48961895 * x3 + -0.0800426 * x4 + 0.23709521 * x5; 
    //cout << "Prediction = " << pred << endl;

    return pred;
 
}

void MathFunctions::setMedian(double median)
{
    _median = median;
}

void MathFunctions::setQunatiles(double Q1, double Q2)
{
    _quant= 0.0;

    std::vector<double> testList = _spElevation;

    std::cout << "Size of list = " << testList.size() << std::endl;
    double quant1 = testList.size() / (1 / Q1);
    double quant2 = testList.size() / (1 / Q2);

    std::cout << "Ist Quantile Position = " << quant1 << std::endl;
    std::cout << "2nd Quantile Position = " << quant2 << std::endl;

    std::sort(testList.begin(), testList.end());

    if (testList.size() % 2 == 0)
    {
        _median = (testList[testList.size() / 2 - 1] + testList[testList.size() / 2]) / 2;
    }
    else
    {
        _median = testList[testList.size() / 2];
    }

    std::cout << "Test Median = " << _median << std::endl << std::endl;

    _q1 = testList[quant1];
    _q2 = testList[quant2];

    std::cout << "Ist Quantile = " << _q1 << std::endl;
    std::cout << "2nd Quantile = " << _q2 << std::endl;
}

void MathFunctions::calcQuantile(double percentile, std::vector<double> dataset)
{
    _quant = 0.0;

    std::vector<double> testList = dataset;

    double position, fractpart, intpart;

    int vSize = testList.size();
    position = percentile * (vSize - 1) + 1;

    std::sort(testList.begin(), testList.end());

    if (floor(position) == ceil(position))
    {
        //if the number is an integer
        _quant = testList[position];

        //std::cout << "Number is an integer! " << std::endl;
    } 
    else
    {
        fractpart = modf(position, &intpart);

        _quant = ((testList[intpart] - testList[intpart-1]) * fractpart) + testList[intpart-1];
        //_quant = (testList[intpart + 1] - testList[intpart]);

        //std::cout << "Integer = " << intpart << " | fractional = " << fractpart << std::endl;

       // std::cout << "Number is NOT an integer! " << std::endl;
    }

    //std::cout << "Element is at position = " << position << std::endl << std::endl;
    //std::cout << "Percentile " << percentile << " = " << _quant << std::endl;

}

void MathFunctions::setQuartiles(std::vector<double> dataset)
{
    _q1 = 0.0;
    _q2 = 0.0;

    std::vector<double> testList = dataset;
    std::vector<double> lower;
    std::vector<double> upper;

    lower.clear();
    upper.clear();

    int vSize = testList.size();

    std::sort(testList.begin(), testList.end());

    if (testList.size() % 2 == 0)
    {
        _median = (testList[vSize / 2 - 1] + testList[vSize / 2]) / 2;

        if ((vSize / 2) % 2 == 0)
        {
            for (int i = 0; i < (vSize / 2); i++)
            {
                lower.push_back(testList[i]);
                upper.push_back(testList[i + (vSize / 2)]);
            }

        _q1 = (lower[lower.size() / 2 - 1] + lower[lower.size() / 2]) / 2;
        _q2 = (upper[upper.size() / 2 - 1] + upper[upper.size() / 2]) / 2;
        }
        else
        {

            for (int i = 0; i < ((vSize - 1) / 2); i++)
            {
                lower.push_back(testList[i]);
                upper.push_back(testList[i + (((vSize - 1) / 2) + 1)]);
            }

            _q1 = lower[lower.size() / 2];
            _q2 = upper[upper.size() / 2];
        }
    }
    else
    {
        _median = testList[(vSize+1) / 2];

        if ((vSize / 2) % 2 == 0)
        {
            for (int i = 0; i < (vSize / 2); i++)
            {
                lower.push_back(testList[i]);
                upper.push_back(testList[i + (vSize / 2)]);
            }

            _q1 = (lower[lower.size() / 2 - 1] + lower[lower.size() / 2]) / 2;
            _q2 = (upper[upper.size() / 2 - 1] + upper[upper.size() / 2]) / 2;
        }
        else
        {

            for (int i = 0; i < ((vSize-1) / 2); i++)
            {
                lower.push_back(testList[i]);
                upper.push_back(testList[i + (((vSize - 1) / 2) + 1)]);
            }

            _q1 = lower[lower.size() / 2];
            _q2 = upper[upper.size() / 2];
        }
    }

    //std::cout << "Test Median = " << _median << std::endl << std::endl;

    //std::cout << "Ist Quantile = " << _q1 << std::endl;
    //std::cout << "2nd Quantile = " << _q2 << std::endl;
}

double MathFunctions::lp1(double x1)
{
    double pred = -7.27563569 + 0.03265495 * x1;
    return pred;
}

void MathFunctions::randomSites(int nsites)
{
    _nsites = nsites;
}

bool MathFunctions::custom_sort(double a, double b) /* this custom sort function is defined to
                                     sort on basis of min absolute value or error*/
{
    double  a1 = abs(a - 0);
    double  b1 = abs(b - 0);
    return a1 < b1;
}

double MathFunctions::getQuant()
{
    return _quant;
}

double MathFunctions::getQ1()
{
    return _q1;

}

double MathFunctions::getQ2()
{
    return _q2;
}

double MathFunctions::getQ3()
{
    return _q3;
}

double MathFunctions::getMedian()
{
    return _median;
}