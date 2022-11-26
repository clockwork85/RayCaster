//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/25/22.
//

#ifndef RAYCASTER_CYLINDER_H
#define RAYCASTER_CYLINDER_H

#include "Shape.h"

class Cylinder : public Shape {
public:
    Vector4f local_normal_at(const Vector4f& point) const override;
    std::vector<Intersection> local_intersect(const Ray& ray) const override;
    bool check_cap(const Ray& ray, float t) const;
    void intersect_caps(const Ray& ray, std::vector<Intersection>& xs) const;

    // minimum and maximum
    float minimum = -INFINITY;
    float maximum = INFINITY;
    bool closed = false;
};

#endif //RAYCASTER_CYLINDER_H
