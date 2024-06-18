#include"classes.h"
#include"sphere.h"
#include"camera.h"

int main()
{
    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.image_height = 360;
    cam.pixel_sample_size = 100;
    cam.ray_reflection_count = 50;

    hittable_list world;
    world.add(make_shared<sphere>(point(0, -100.5, -1), 100));
    world.add(make_shared<sphere>(point(0, 0, -1), 0.5));

    cam.render(world);
}