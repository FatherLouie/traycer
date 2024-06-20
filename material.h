#ifndef MATERIAL_H
#define MATERIAL_H

class material
{
    public:
    vec3 albedo;
    virtual ~material() = default;
    virtual ray scatter(const ray r_in, const record rec) const = 0;
};



// -------------------------------------------------------------------------------------------------------------------------



class lambertian : public material
{
    public:
    lambertian(vec3 col = vec3())
    {
        albedo = col;
    }

    ray scatter(const ray r_in, const record rec) const
    {
        vec3 dir = rec.normal + random_vec().normalize();
        if (dir.near_zero()) dir = rec.normal;
        return ray(rec.incidence, dir);
    }
};



// -------------------------------------------------------------------------------------------------------------------------



class metal : public material
{
    public:
    metal(vec3 col = vec3())
    {
        albedo = col;
    }

    ray scatter(const ray r_in, const record rec) const
    {
        vec3 reflect_dir = r_in.dir() - 2*dot(r_in.dir(), rec.normal)*rec.normal;
        return ray(rec.incidence, reflect_dir);
    }
};

#endif