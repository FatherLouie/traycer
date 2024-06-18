#ifndef COLOUR_H
#define COLOUR_H

static const double gamma_val = 2.2;
static const interval intensity = interval(0, 0.999);

vec3 lin_to_gam(const vec3& v)
{
    double x = pow(v.x(), 1.0/gamma_val);
    double y = pow(v.y(), 1.0/gamma_val);
    double z = pow(v.z(), 1.0/gamma_val);
    return vec3(x, y, z);
}

void write_colour(const vec3& v)
{
    vec3 pixel = lin_to_gam(v);
    int r = int(intensity.constrain(pixel.x())*256);
    int g = int(intensity.constrain(pixel.y())*256);
    int b = int(intensity.constrain(pixel.z())*256);
    cout << vec3(r, g, b) << '\n';
}

#endif