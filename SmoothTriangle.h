//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 12/5/22.
//

#ifndef RAYCASTER_SMOOTHTRIANGLE_H
#define RAYCASTER_SMOOTHTRIANGLE_H

#include "Shape.h"
#include <iostream>

class SmoothTriangle : public Shape {
public:
    SmoothTriangle(const Vector4f& p1, const Vector4f& p2, const Vector4f& p3, const Vector4f& n1, const Vector4f& n2, const Vector4f& n3);
    Vector4f local_normal_at(const Vector4f& point, const Intersection& intersection) const override;
    std::vector<Intersection> local_intersect(const Ray& ray) const override;
    Vector4f p1, p2, p3;
    Vector4f n1, n2, n3;
    Vector4f e1, e2;
    Vector4f normal;
    float u, v;
};

#endif //RAYCASTER_SMOOTHTRIANGLE_H
