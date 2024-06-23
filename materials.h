#ifndef MATERIALS_H
#define MATERIALS_H

class material
{
    public:
    vec3 albedo;
    virtual ~material() = default;
    virtual ray scatter(const ray r_in, const record rec) const = 0;

    inline vec3 reflect(const vec3 ray_dir, const vec3 normal) const
    {
        return ray_dir - 2*dot(ray_dir, normal)*normal; 
    }

    inline vec3 refract(const vec3 ray_dir, const vec3 normal, double r_index) const
    {
        vec3 refracting_plane = cross(ray_dir, normal);
        double sin_incident = refracting_plane.length();
        double sin_refracted = r_index*sin_incident;

        if (sin_refracted > 1.0) return reflect(ray_dir, normal);
        else
        {
            double theta = asin(sin_refracted) - asin(sin_incident);
            return ray_dir*cos(theta) + cross(refracting_plane.normalize(), ray_dir)*sin(theta);
        }
    }
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
        vec3 reflect_dir = reflect(r_in.dir().normalize(), rec.normal);
        vec3 fuzz_dir = reflect_dir.normalize() + fuzz*(random_vec().normalize());
        return ray(rec.incidence, fuzz_dir);
    }
};



// -------------------------------------------------------------------------------------------------------------------------



class dielectric : public material
{
    double refractive_index;
    double reflectance(double cosine, double r_index) const
    {
        double r = pow((1.0 - r_index)/(1.0 + r_index), 2);
        return r + (1-r)*pow((1-cosine), 5);
    }

    public:
    dielectric(vec3 col = vec3(), double eta = 1.0)
    {
        albedo = col;
        refractive_index = eta;
    }

    ray scatter(const ray r_in, const record rec) const
    {
        double cos_incident = dot(r_in.dir().normalize(), -rec.normal);
        double rel_ref_index = rec.outside ? (1.0/refractive_index) : refractive_index;

        vec3 refracted_dir;
        if (reflectance(cos_incident, refractive_index) > random_double())
        {
            refracted_dir = reflect(r_in.dir().normalize(), rec.normal);
        }
        else
        {
            refracted_dir = refract(r_in.dir().normalize(), rec.normal, rel_ref_index);
        }
        return ray(rec.incidence, refracted_dir);
    }
};

#endif