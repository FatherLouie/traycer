#ifndef CAMERA_H
#define CAMERA_H

#include "classes.h"

class camera
{
    public:
        // Output details
    int image_height;
    double aspect_ratio;
    int pixel_sample_size;
    int ray_reflection_count;
        // Camera position
    double fov;
    vec3 lookfrom, lookat, up;
        // Lens properties
    double defocus_angle;
    double focal_length;

    void render(const hittable& world)
    {
        viewport();
        cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        for(int i = 0; i < image_height; i += 1)
        {
            clog << "Progress: " << i << "/" << image_height << '\n' << flush;
            for(int j = 0; j < image_width; j += 1)
            {
                colour pixel_colour = colour(0, 0, 0);
                for (int k = 0; k < pixel_sample_size; k += 1)
                {
                    ray r = random_ray(j, i);
                    pixel_colour += ray_colour(r, world, ray_reflection_count);
                }
                pixel_colour /= double(pixel_sample_size);
                write_colour(pixel_colour);
            }
        }
    }

    private:
    int image_width;

    point topleft_pixel;
    vec3 del_u, del_v;
    vec3 u, v, w;

    void viewport()
    {
        image_width = image_height*aspect_ratio;
        double viewport_height = 2*tan(degrees_to_radians(fov)/2)*focal_length;
        double viewport_width = viewport_height * (double(image_width)/double(image_height));

        w = (lookfrom - lookat).normalize();
        v = ((w == up) || (w == -up)) ? vec3(0, 0, 1) : cross(w, cross(up, w)).normalize();
        u = cross(v, w).normalize();

        del_u = (viewport_width/double(image_width))*u;
        del_v = (viewport_height/double(image_height))*(-v);
        topleft_pixel = lookfrom - (focal_length*w) + (viewport_width/2.0)*(-u) + (viewport_height/2.0)*(v) + (del_u + del_v)/2.0;
    }

    ray random_ray(int x, int y)
    {
        double blur_radius = focal_length*tan(degrees_to_radians(defocus_angle/2.0));
        vec3 rand_org;
        do
        {
            vec3 rand_vec = random_double(-blur_radius, blur_radius)*u + random_double(-blur_radius, blur_radius)*v;
            rand_org = lookfrom + rand_vec;
        }
        while ((rand_org - lookfrom).length() > blur_radius);
        
        point rand_pt = topleft_pixel + (x + random_double(-0.5, 0.5))*del_u + (y + random_double(-0.5, 0.5))*del_v;
        return ray(rand_org, rand_pt - rand_org);
    }

    colour ray_colour(ray r, const hittable& w, double recurrence)
    {
        if (recurrence <= 0) return colour();
        record rec = w.hit(r, interval(0.001, infinity));
        if (rec.success)
        {
            ray reflected = (*(*rec.object).finish).scatter(r, rec);
            return ((*(*rec.object).finish).albedo)*ray_colour(reflected, w, recurrence - 1);
        }
        else
        {
            vec3 unit_direction = (r.dir()).normalize();
            double frac = 0.5*(unit_direction.y() + 1.0);
            return (1.0 - frac)*colour(1.0, 1.0, 1.0) + (frac)*colour(0.5, 0.7, 1.0);
        }
    }
};

#endif