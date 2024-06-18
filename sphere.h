#ifndef SPHERE_H
#define SPHERE_H

#include "classes.h"

class sphere : public hittable
{
    point centre;
    double radius;

    public:
    sphere(point p = point(0, 0, 0), double r = 1.0)
    {
        centre = p;
        radius = r;
    }

    record hit(const ray r, interval i) const
    {
        double a = dot(r.dir(), r.dir());
        double h = dot(r.dir(), (*this).centre - r.org());
        double c = dot((*this).centre - r.org(), (*this).centre - r.org()) - ((*this).radius)*((*this).radius);
        double discriminant = h*h - a*c;

        if (discriminant < 0) return record();

        //roots exist; if both lie out of range return false record, else set t to be the one in range
        double t;
        double t1 = (h - sqrt(discriminant))/a;
        double t2 = (h + sqrt(discriminant))/a;

        if (!i.contains(t1) && !i.contains(t2))
        {
            return record();
        }
        else
        {
            t = (!i.contains(t1)) ? t2 : t1;
        }
        // t = t2;
        // if (!i.contains(t))
        // {
        //     t = t1;
        //     if (!i.contains(t)) return record();
        // }

        record hit;
        hit.success = true;
        hit.incidence = r.point(t);
        point outer_normal = (r.point(t) - (*this).centre).normalize();
        hit.set_normal(r, outer_normal);
        hit.parameter = t;

        return hit;
    }
};

#endif