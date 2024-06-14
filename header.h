#ifndef HEADER_H
#define HEADER_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>


// C++ Std Usings

using namespace std;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Common Headers

#include "colour.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

using point = vec3;
using colour = vec3;

#endif