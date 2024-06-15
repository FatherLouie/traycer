#ifndef CAMERA_H
#define CAMERA_H

#include"header.h"
#include"hittable.h"

class camera
{
    public:
    int image_height;
    double aspect_ratio;
    int pixel_sample_size;
    int ray_reflection_count;

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
    point camera_pos = point(0, 0, 0);
    double focal_length = 1.0;

    point topleft_pixel;
    vec3 del_x, del_y;

    void viewport()
    {
        image_width = image_height*aspect_ratio;
        double viewport_height = 2.0;
        double viewport_width = viewport_height * (double(image_width)/double(image_height));

        topleft_pixel = point(-0.5*(viewport_width), 0.5*(viewport_height), -focal_length) + del_x + del_y;
        del_x = vec3((viewport_width/double(image_width)), 0, 0);
        del_y = vec3(0, -(viewport_height/double(image_height)), 0);
    }

    ray random_ray(int x, int y)
    {
        point rand_pt = topleft_pixel + (x + random(-0.5, 0.5))*del_x + (y + random(-0.5, 0.5))*del_y;
        return ray(camera_pos, rand_pt - camera_pos);
    }

    colour ray_colour(ray r, const hittable& w, double recurrence)
    {
        if (recurrence <= 0) return colour();
        record rec = w.hit(r, interval(0.001, infinity));
        if (rec.success)
        {
            ray diffused_ray = ray(rec.incidence, rand_diffused(rec.normal));
            return 0.9*ray_colour(diffused_ray, w, recurrence - 1);
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