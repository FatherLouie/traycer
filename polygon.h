#ifndef POLYGON_H
#define POLYGON_H

class polygon
{
    public:
    int edgecount;
    vec3 plane, centroid;
    vector<vec3> vertices;
    polygon(vec3 perp = vec3(0, 1, 0), int n = 1, vec3 ctr = vec3())
    {
        edgecount = n;
        plane = perp;
        centroid = ctr;
    }

    inline void next_vertex(const vec3 v)
    {
            vertices.push_back(v);
    }

    inline void generate_regular(const vec3 seed_vec)
    {
        double theta = 2*pi/double(edgecount);
        next_vertex(seed_vec);
            for (int i = 1; i < edgecount; i += 1)
            {
                vec3 old_vec = vertices[i - 1] - centroid;
                vec3 new_vec = old_vec*cos(theta) + cross(plane.normalize(), old_vec)*sin(theta);
                vertices.push_back(new_vec + centroid);
            }
    }

    virtual bool inside(const vec3 v) const
    {
        const interval domain(-1, 1);
        double angle_sum = 0;
        for (int i = 0; i < edgecount; i += 1)
        {
            int j = (i+1)%edgecount;
            vec3 side_a = (vertices[j] - v).normalize();
            vec3 side_b = (vertices[i] - v).normalize();
            angle_sum += acos(domain.constrain(dot(side_a, side_b)));
        }
        double close = abs(angle_sum) - 2*pi;
        return (abs(close) < 1e-3);
    }

    double ray_hit(const ray r) const
    {
        if (abs(dot(r.dir(), plane)) < 1e-3) return 0;
        else
        {
            double root = -dot((r.org() - centroid), plane) / dot(r.dir(), plane);
            if (inside(r.point(root))) return root;
            else return 0;
        }
    }
};



// -------------------------------------------------------------------------------------------------------------------------



class circle
{
    public:
    vec3 plane, centre;
    double radius;
    circle(vec3 p = vec3(0, 1, 0), vec3 ctr = vec3(), double r = 1)
    {
        plane = p;
        centre = ctr;
        radius = r;
    }

    bool inside(const vec3 v) const
    {
        return (abs(dot(v - centre, plane)) < 1e-3 && (v - centre).length() < radius);
    }

    double ray_hit(const ray r) const
    {
        if (abs(dot(r.dir(), plane)) < 1e-3) return 0;
        else
        {
            double root = -dot((r.org() - centre), plane) / dot(r.dir(), plane);
            if (inside(r.point(root))) return root;
            else return 0;
        }
    }
};

#endif