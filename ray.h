#ifndef RAY_H
#define RAY_H

#include"vec3.h"
#include<iostream>
using namespace std;

class ray
{
    vec3 origin;
    vec3 direction;

    public:
    ray(vec3 o = vec3(0,0,0), vec3 d = vec3(0,0,0))
    {
        origin = o;
        direction = d;
    }

    vec3 org() const { return origin; }
    vec3 dir() const { return direction; }

    vec3 point(double parameter) const
    {
        return (origin + parameter*direction);
    }
};

ostream& operator << (ostream& ost, const ray& r)
{
    return ost << "(" << r.org() << ") + t*" << "(" << r.dir() << ")";
}

#endif