#ifndef HITTABLES_H
#define HITTABLES_H

class hittable
{
    public:
    shared_ptr<material> finish;
    virtual ~hittable() = default;
    virtual record hit(const ray r, interval i) const = 0;
};



//--------------------------------------------------------------------------------------------------------------------------



class hittable_list : public hittable
{
    public:
    vector <shared_ptr<hittable>> objects;

    void add(shared_ptr<hittable> hptr)
    {
        objects.push_back(hptr);
    }

    void clear()
    {
        objects.clear();
    }

    record hit(const ray r, interval i) const
    {
        record rec = record();
        double t_largest = i.max;
        
        for (const auto& hptr : objects)
        {
            record current_rec = (*hptr).hit(r, interval(i.min, t_largest));
            if (current_rec.success)
            {
                rec = current_rec;
                rec.object = hptr;
                t_largest = current_rec.parameter;
            }
        }

        return rec;
    }
};



//--------------------------------------------------------------------------------------------------------------------------



class sphere : public hittable
{
    point centre;
    double radius;

    public:
    sphere(point p = point(0, 0, 0), double r = 1.0, shared_ptr<material> m = nullptr)
    {
        centre = p;
        radius = r;
        finish = m;
    }

    record hit(const ray r, interval i) const
    {
        double a = dot(r.dir(), r.dir());
        double h = dot(r.dir(), (*this).centre - r.org());
        double c = dot((*this).centre - r.org(), (*this).centre - r.org()) - ((*this).radius)*((*this).radius);
        double discriminant = h*h - a*c;

        if (discriminant < 0) return record();

        //roots exist; if both lie out of range return false record, else set t to be the one in range
        double t;
        double t1 = (h - sqrt(discriminant))/a;
        double t2 = (h + sqrt(discriminant))/a;

        if (!i.contains(t1) && !i.contains(t2)) return record();
        else t = (!i.contains(t1)) ? t2 : t1;

        record hit;
        hit.success = true;
        hit.incidence = r.point(t);
        point outer_normal = (r.point(t) - (*this).centre).normalize();
        hit.set_normal(r, outer_normal);
        hit.parameter = t;

        return hit;
    }
};

#endif