#ifndef RECORD_H
#define RECORD_H

class hittable;

class record
{
    public:
    bool success;
    shared_ptr<hittable> object;
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
 
#endif