#ifndef INTERVAL_H
#define INTERVAL_H
#include"zheader.h"

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

    static const interval empty, universe;
};

const interval interval::empty = interval();
const interval interval::universe = interval(-infinity, +infinity);

#endif