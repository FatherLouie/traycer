#include"header.h"
#include"sphere.h"
#include"hittable.h"
#include"camera.h"

colour ray_colour(const ray, const hittable&);

int main()
{
    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.image_height = 360;
    cam.sample_size = 1;

    hittable_list world;
    world.add(make_shared<sphere>(point(0, -100.5, -1), 100));
    world.add(make_shared<sphere>(point(0, 0, -1), 0.5));

    cam.render(world);
}