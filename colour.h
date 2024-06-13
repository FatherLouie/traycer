#ifndef COLOUR_H
#define COLOUR_H

#include<iostream>
#include"vec3.h"
using namespace std;

void write_colour(vec3& pixel)
{
    int r = int(pixel.x()*255.999);
    int g = int(pixel.y()*255.999);
    int b = int(pixel.z()*255.999);
    cout << vec3(r,g,b) << '\n';
}

#endif