#ifndef COLOUR_H
#define COLOUR_H

#include <iostream>
using namespace std;
#include "vec3.h"
#include "interval.h"

static const interval intensity = interval(0, 0.999);
void write_colour(vec3& pixel)
{
    int r = int(intensity.constrain(pixel.x())*256);
    int g = int(intensity.constrain(pixel.y())*256);
    int b = int(intensity.constrain(pixel.z())*256);
    cout << vec3(r, g, b) << '\n';
}

#endif