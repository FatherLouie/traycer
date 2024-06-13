#include"zheader.h"
#include"sphere.h"
#include"hittable.h"

colour ray_colour(const ray, const hittable&);

int main()
{
    double aspect_ratio = 16.0/9.0;
    int width = 1280;
    int height = width/aspect_ratio;
    cout << "P3\n" << width << " " << height << "\n255\n";

    double focal_length = double(height)/2.0;
    point camera_pos = point(0, 0, 0);

    point topleft_pixel = point(-(double(width)/2 - 0.5), (double(height)/2 - 0.5), -focal_length);
    point del_x = point(1, 0, 0), del_y = point(0, -1, 0);

    hittable_list world;
    world.add(make_shared<sphere>(point(0, -36180, -360), 36000));
    world.add(make_shared<sphere>(point(0, 0, -360), 180));

    for(double i = 0; i < height; i += 1)
    {
        for(double j = 0; j < width; j += 1)
        {
            point pixel = topleft_pixel + (del_x*j) + (del_y*i);
            ray pixel_ray = ray(camera_pos, pixel - camera_pos);
            colour pixel_colour = ray_colour(pixel_ray, world);
            write_colour(pixel_colour);
        }
    }
}

colour ray_colour(const ray r, const hittable& world)
{
    record rec = world.hit(r, interval(0, infinity));
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