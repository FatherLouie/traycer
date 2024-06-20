#ifndef HITTABLE_H
#define HITTABLE_H

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

#endif