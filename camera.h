#ifndef CAMERA_H
#define CAMERA_H

#include"header.h"
#include"hittable.h"

class camera
{
    public:
    int image_height;
    double aspect_ratio;

    void render(const hittable& world)
    {
        viewport();
        cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        for(int i = 0; i < image_height; i += 1)
        {
            for(int j = 0; j < image_width; j += 1)
            {
                point pixel = topleft_pixel + (del_x*j) + (del_y*i);
                ray pixel_ray = ray(camera_pos, pixel - camera_pos);
                colour pixel_colour = ray_colour(pixel_ray, world);
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

    colour ray_colour(ray r, const hittable& w)
    {
        record rec = w.hit(r, interval(0, infinity));
        if (rec.success)
        {
            return 0.5*(rec.normal + colour(1.0, 1.0, 1.0));
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