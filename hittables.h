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
    vec3 centre;
    double radius;

    public:
    sphere(vec3 p = vec3(0, 0, 0), double r = 1.0, shared_ptr<material> m = nullptr)
    {
        centre = p;
        radius = r;
        finish = m;
    }

    record hit(const ray r, interval i) const
    {
        double a = dot(r.dir(), r.dir());
        double h = dot(r.dir(), centre - r.org());
        double c = dot(centre - r.org(), centre - r.org()) - (radius)*(radius);
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
        vec3 outer_normal = (r.point(t) - centre).normalize();
        hit.set_normal(r, outer_normal);
        hit.parameter = t;

        return hit;
    }
};



// -------------------------------------------------------------------------------------------------------------------------



class cylinder : public hittable
{
    circle base, top;
    double height;

    public:
    cylinder(circle c, double h = 0, shared_ptr<material> m = nullptr)
    {
        base = c;
        height = h;
        finish = m;
        top = circle(-base.plane, base.centre - height*base.plane.normalize(), base.radius);
    }

    record hit(const ray r, interval i) const
    {
        record hit = record();
        double t_min = i.max;
        double t;

        t = base.ray_hit(r);
        if (t < t_min && i.contains(t))
        {
            t_min = t;
            hit.success = true;
            hit.set_normal(r, base.plane);
        }
        t = top.ray_hit(r);
        if (t < t_min && i.contains(t))
        {
            t_min = t;
            hit.success = true;
            hit.set_normal(r, top.plane);
        }

        vec3 d = r.org() - base.centre;
        vec3 temp = top.plane, n = temp.normalize();
        double a = dot(r.dir(), r.dir()) - pow(dot(r.dir(), n), 2);
        double b = 2*dot(r.dir(), d) - 2*dot(r.dir(), n)*dot(d, n);
        double c = dot(d, d) - pow(dot(d, n), 2) - pow(base.radius, 2);
        double disc = b*b - 4*a*c;

        if (disc < 0) return record();
        double t1 = (-b + sqrt(disc))/(2*a);
        double t2 = (-b - sqrt(disc))/(2*a);

        t = (t2 < 0) ? t1 : t2;
        if (t < t_min && i.contains(t) && interval(0, height).contains(dot(d + r.dir()*t, n)))
        {
            t_min = t;
            hit.success = true;
            vec3 outer_normal = d + r.dir()*t - dot(d + r.dir()*t, n)*n;
        }

        if (hit.success)
        {
            hit.incidence = r.point(t_min);
            hit.parameter = t_min;
        }
        return hit;
    }
};



// -------------------------------------------------------------------------------------------------------------------------



class cone : public hittable
{
    circle base;
    double height;

    public:
    cone(circle c, double h, shared_ptr<material> m = nullptr)
    {
        base = c;
        height = h;
        finish = m;
    }

    record hit(const ray r, interval i) const
    {
        record hit = record();
        double t_min = i.max;
        double t;

        t = base.ray_hit(r);
        if (t < t_min && i.contains(t))
        {
            t_min = t;
            hit.success = true;
            hit.set_normal(r, base.plane);
        }

        vec3 temp = base.plane, n = temp.normalize();
        vec3 d = r.org() - base.centre + n*height;
        double lambda = dot(d, n), mu = dot(r.dir(), n);
        double a = pow(mu, 2)*(pow(base.radius, 2) + pow(height, 2)) - dot(r.dir(), r.dir())*pow(height, 2);
        double b = 2*mu*lambda*(pow(base.radius, 2) + pow(height, 2)) - 2*dot(d, r.dir())*pow(height, 2);
        double c = pow(lambda, 2)*(pow(base.radius, 2) + pow(height, 2)) - dot(d, d)*pow(height, 2);
        double disc = b*b - 4*a*c;

        if (disc < 0) return record();
        double t1 = (-b + sqrt(disc))/(2*a);
        double t2 = (-b - sqrt(disc))/(2*a);

        t = (t2 < 0) ? t1 : t2;
        if (t < t_min && i.contains(t) && interval(0, height).contains(dot(d + r.dir()*t, n)))
        {
            t_min = t;
            hit.success = true;
            vec3 outer_normal = d + r.dir()*t - dot(d + r.dir()*t, n)*n;
        }

        if (hit.success)
        {
            hit.incidence = r.point(t_min);
            hit.parameter = t_min;
        }
        return hit;
    }
};



// -------------------------------------------------------------------------------------------------------------------------



class prism : public hittable
{
    polygon base;
    vec3 spine;
    vector<polygon> faces;

    public:
    prism(polygon f, vec3 s, shared_ptr<material> m = nullptr)
    {
        base = f;
        spine = s;
        finish = m;

        base.plane = (dot(f.plane, spine) < 0) ? f.plane : -f.plane; 
        faces.push_back(base);

        polygon top(-base.plane, f.edgecount, f.centroid + spine);
        for (vec3 vertex: base.vertices) {top.next_vertex(vertex + spine);}
        faces.push_back(top);

        for (int k = 0; k < f.edgecount; k += 1)
        {
            int j = (k+1) % f.edgecount;
            vec3 normal = cross((f.vertices[j] - f.vertices[k]), spine).normalize();

            polygon quad(normal, 4, (f.vertices[k] + f.vertices[j] + spine)/2.0);
            quad.next_vertex(base.vertices[k]);
            quad.next_vertex(base.vertices[j]);
            quad.next_vertex(top.vertices[j]);
            quad.next_vertex(top.vertices[k]);

            faces.push_back(quad);
        }
    }

    record hit(const ray r, interval i) const
    {
        record hit = record();
        double t_min = i.max;
        double t;

        for(polygon face : faces)
        {
            t = face.ray_hit(r);
            if (t < t_min && i.contains(t))
            {
                t_min = t;
                hit.success = true;
                hit.set_normal(r, face.plane);
                hit.incidence = r.point(t_min);
                hit.parameter = t_min;
            }
        }

        return hit;
    }
};



// -------------------------------------------------------------------------------------------------------------------------



class pyramid : public hittable
{
    polygon base;
    vec3 tip;
    vector<polygon> faces;

    public:
    pyramid(polygon f, vec3 t, shared_ptr<material> m = nullptr)
    {
        base = f;
        tip = t;
        finish = m;

        base.plane = (dot(f.plane, tip - f.centroid) < 0) ? f.plane : -f.plane; 
        faces.push_back(base);

        for (int k = 0; k < f.edgecount; k += 1)
        {
            int j = (k+1) % f.edgecount;
            vec3 normal = cross(f.vertices[j] - t, f.vertices[k] - t).normalize();
            vec3 outer_normal = (dot(normal, (f.vertices[j] + f.vertices[k])/2.0 - f.centroid) > 0) ? normal : -normal; 

            polygon triangle(outer_normal, 3, (f.vertices[k] + f.vertices[j] + tip)/3.0);
            triangle.next_vertex(f.vertices[k]);
            triangle.next_vertex(f.vertices[j]);
            triangle.next_vertex(tip);

            faces.push_back(triangle);
        }
    }

    record hit(const ray r, interval i) const
    {
        record hit = record();
        double t_min = i.max;
        double t;

        for(polygon face : faces)
        {
            t = face.ray_hit(r);
            if (t < t_min && i.contains(t))
            {
                t_min = t;
                hit.success = true;
                hit.set_normal(r, face.plane);
                hit.incidence = r.point(t_min);
                hit.parameter = t_min;
            }
        }

        return hit;
    }
};

#endif