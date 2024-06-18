#ifndef INTERVAL_H
#define INTERVAL_H

#include "utilities.h"

class interval
{
    public:
    double min, max;
    interval(double m1 = +infinity, double m2 = -infinity)
    {
        min = m1;
        max = m2;
    }

    double size() const
    {
        return (*this).max - (*this).min;
    }

    bool contains(double x) const
    {
        return (x >= (*this).min) && (x <= (*this).max);
    }

    double constrain(double x) const
    {
        if (x < (*this).min) return (*this).min;
        else if (x > (*this).max) return (*this).max;
        else return x;
    }

    static const interval empty, universe;
};

const interval interval::empty = interval();
const interval interval::universe = interval(-infinity, +infinity);

#endif