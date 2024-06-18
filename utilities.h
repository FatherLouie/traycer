#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <memory>

using namespace std;


const double infinity = numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline static double degrees_to_radians(double degrees)
{
    return degrees*pi/180.0;
}

inline static double random_double(double min = 0, double max = 1)
{
    return min + (max - min)*(rand()/(RAND_MAX + 1.0));
}

#endif