//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 12/4/22.
//

#ifndef RAYCASTER_TRIANGLE_H
#define RAYCASTER_TRIANGLE_H

#include <vector>
#include "Shape.h"

class Triangle : public Shape {
public:
    Triangle(const Vector4f& p1, const Vector4f& p2, const Vector4f& p3) : p1(p1), p2(p2), p3(p3) {
        e1 = p2 - p1;
        e2 = p3 - p1;
        normal = e2.cross3(e1).normalized();
    }

    Vector4f local_normal_at(const Vector4f& point, const Intersection& i={}) const override;
    std::vector<Intersection> local_intersect(const Ray& ray) const override;

    Vector4f p1;
    Vector4f p2;
    Vector4f p3;
    Vector4f e1;
    Vector4f e2;
    Vector4f normal;


};

#endif //RAYCASTER_TRIANGLE_H
