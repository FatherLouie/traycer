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
    double fuzz;
    public:
    metal(vec3 col = vec3(), double f = 0.0)
    {
        albedo = col;
        fuzz = (f < 1) ? f : 1;
    }

    ray scatter(const ray r_in, const record rec) const
    {
        vec3 reflect_dir = r_in.dir() - 2*dot(r_in.dir(), rec.normal)*rec.normal;
        vec3 fuzz_dir = reflect_dir.normalize() + fuzz*(random_vec().normalize());
        return ray(rec.incidence, fuzz_dir);
    }
};



// -------------------------------------------------------------------------------------------------------------------------



class dielectric : public material
{
    double refractive_index;
    public:
    dielectric(vec3 col = vec3(), double eta = 1.0)
    {
        albedo = col;
        refractive_index = eta;
    }

    ray scatter(const ray r_in, const record rec) const
    {
        vec3 normal = rec.normal;
        vec3 refracting_plane = cross(r_in.dir().normalize(), normal.normalize());
        double sin_incident = refracting_plane.length();
        double rel_ref_index = rec.outside ? (1.0/refractive_index) : refractive_index;
        double sin_refracted = rel_ref_index*sin_incident;

        vec3 refracted_dir;
        if (sin_refracted > 1.0)
        {
            refracted_dir = r_in.dir() - 2*dot(r_in.dir(), rec.normal)*rec.normal;
        }
        else
        {
            int sign = (refractive_index <= 1.0) ? 1 : -1;
            double theta = sign*abs(asin(sin_refracted) - asin(sin_incident));
            refracted_dir = r_in.dir()*cos(theta) + cross(refracting_plane.normalize(), r_in.dir())*sin(theta);
        }
        return ray(rec.incidence, refracted_dir);
    }
};

#endif