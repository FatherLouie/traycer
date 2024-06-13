#ifndef HITTABLE_H
#define HITTABLE_H

#include<vector>
#include<memory>
using namespace std;

#include"ray.h"
#include"vec3.h"
#include"interval.h"

class record
{
    public:
    bool success;
    vec3 incidence;
    vec3 normal;
    double parameter;
    bool outside;

    record()
    {
        success = false;
        incidence = vec3();
        normal = vec3();
        parameter = 0;
        outside = true;
    }

    void set_normal(const ray r, const vec3 outer_normal)
    {
        (*this).outside = dot(r.dir(), outer_normal) < 0;
        (*this).normal = (*this).outside ? outer_normal : -outer_normal;
    }
};

//--------------------------------------------------------------------------------------------------------------------------

class hittable
{
    public:
    virtual ~hittable() = default;
    virtual record hit(const ray r, interval i) const = 0;
};

//--------------------------------------------------------------------------------------------------------------------------

class hittable_list : public hittable
{
    public:
    vector <shared_ptr<hittable>> objects;

    void add(shared_ptr<hittable> hptr)
    {
        objects.push_back(hptr);
    }

    void clear()
    {
        objects.clear();
    }

    record hit(const ray r, interval i) const
    {
        record rec = record();
        double t_largest = i.max;
        
        for (const auto& hptr : objects)
        {
            record current_rec = (*hptr).hit(r, interval(i.min, t_largest));
            if (current_rec.success)
            {
                rec = current_rec;
                t_largest = current_rec.parameter;
            }
        }

        return rec;
    }
};

#endif