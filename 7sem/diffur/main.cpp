#include <iostream>
#include <math.h>
#include <fstream>
#include "rungeKutta.hpp"

using namespace std;


double dx(double x, double y);
double dy(double x, double y);

double dx(double x, double y)
{
    return y;
}
double dy(double x, double y)
{
    return /*alpha*/10*(1-x*x)*y-x;
}

int main (int argc, char** argv)
{

    double xStart = atof(argv[1]);
    double yStart = atof(argv[2]);
    int numberOfPoints = 0;
    findCycle(xStart, yStart, &dx, &dy, &numberOfPoints);
    cout << "Number of points: " << numberOfPoints << endl;

    return 0;
}