#include"classes.h"
#include"sphere.h"
#include"camera.h"

int main()
{
    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.image_height = 360;
    cam.pixel_sample_size = 100;
    cam.ray_reflection_count = 20;

    auto ground = make_shared<lambertian>(colour(0.75, 1, 0));
    auto centre = make_shared<lambertian>(colour(0.1, 0.2, 0.5));
    auto left = make_shared<metal>(colour(0.8, 0.8, 0.8));
    auto right = make_shared<metal>(colour(0.86, 0, 0.5));

    hittable_list world;
    world.add(make_shared<sphere>(point(0, -100.5, -1), 100, ground));
    world.add(make_shared<sphere>(point(0, 0, -1.2), 0.5, centre));
    world.add(make_shared<sphere>(point(-1, 0, -1), 0.5, left));
    world.add(make_shared<sphere>(point(1, 0, -1), 0.5, right));

    cam.render(world);
}