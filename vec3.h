#ifndef VEC3_H
#define VEC3_H

class vec3
{
    double xyz[3];
    public:

    vec3(double p = 0, double q = 0, double r = 0)
    {
        xyz[0] = p; xyz[1] = q; xyz[2] = r;
    }

    double x() const { return xyz[0]; }
    double y() const { return xyz[1]; }
    double z() const { return xyz[2]; }

    vec3 operator - () const
    {
        return vec3(-(*this).x(), -(*this).y(), -(*this).z());
    }

    vec3& operator = (const vec3& v)
    {
        (*this).xyz[0] = v.x();
        (*this).xyz[1] = v.y();
        (*this).xyz[2] = v.z();
        return *this;
    }

    vec3& operator += (const vec3 v)
    {
        (*this).xyz[0] += v.x();
        (*this).xyz[1] += v.y();
        (*this).xyz[2] += v.z();
        return *this;
    }

    vec3& operator *= (double t)
    {
        (*this).xyz[0] *= t;
        (*this).xyz[1] *= t;
        (*this).xyz[2] *= t;
        return *this;
    }

    vec3& operator /= (double t)
    {
        return (*this) *= (1/t);
    }

    double length() const
    {
        return sqrt((*this).x()*(*this).x() + (*this).y()*(*this).y() + (*this).z()*(*this).z());
    }

    vec3& normalize()
    {
        return (*this) /= (*this).length();
    }

    bool near_zero() const
    {
        double s = 1e-8;
        return ((fabs(xyz[0]) < s) && (fabs(xyz[1]) < s) && (fabs(xyz[2]) < s));
    }
};

ostream& operator << (ostream& ost, const vec3& v)
{
    return ost << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator + (const vec3& u, const vec3& v)
{
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator - (const vec3& u, const vec3& v)
{
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vec3 operator * (const vec3& u, const vec3& v)
{
    return vec3(u.x()*v.x(), u.y()*v.y(), u.z()*v.z());
}

inline vec3 operator * (double t, const vec3& v)
{
    return vec3(t*v.x(), t*v.y(), t*v.z());
}

inline vec3 operator * (const vec3& v, double t)
{ 
    return t*v;
}

inline vec3 operator / (const vec3& v, double t)
{
    return (1/t)*v;
}

inline double dot(const vec3& u, const vec3& v)
{
    return (u.x()*v.x() + u.y()*v.y() + u.z()*v.z());
}

inline vec3 cross(const vec3& u, const vec3& v)
{
    return vec3(u.y()*v.z() - u.z()*v.y(), u.z()*v.x() - u.x()*v.z(), u.x()*v.y() - u.y()*v.x());
}

inline static vec3 random_vec(double min = 0, double max = 1)
{
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

#endif