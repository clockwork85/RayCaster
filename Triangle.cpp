//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 12/4/22.
//

#include "Triangle.h"

std::vector<Intersection> Triangle::local_intersect(const Ray& ray) const {
    std::vector<Intersection> xs;
    Vector4f dir_cross_e2 = ray.direction.cross3(e2);
    float det = e1.dot(dir_cross_e2);
    if(fabs(det) < EPSILON) {
        return xs;
    }
    float f = 1.0f / det;
    Vector4f p1_to_origin = ray.origin - p1;
    float u = f * p1_to_origin.dot(dir_cross_e2);
    if(u < 0 || u > 1) {
        return xs;
    }
    Vector4f origin_cross_e1 = p1_to_origin.cross3(e1);
    float v = f * ray.direction.dot(origin_cross_e1);
    if(v < 0 || (u + v) > 1) {
        return xs;
    }
    float t = f * e2.dot(origin_cross_e1);
    xs.emplace_back(t, this);
    return xs;
}

Vector4f Triangle::local_normal_at(const Vector4f& point) const {
    return normal;
}