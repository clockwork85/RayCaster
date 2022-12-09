//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 12/5/22.
//


#include "SmoothTriangle.h"

SmoothTriangle::SmoothTriangle(const Vector4f& p1, const Vector4f& p2, const Vector4f& p3, const Vector4f& n1, const Vector4f& n2, const Vector4f& n3) : p1(p1), p2(p2), p3(p3), n1(n1), n2(n2), n3(n3) {
    e1 = p2 - p1;
    e2 = p3 - p1;
    normal = e2.cross3(e1).normalized();
}

std::vector<Intersection> SmoothTriangle::local_intersect(const Ray& ray) const {
    const auto dir_cross_e2 = ray.direction.cross3(e2);
    const auto det = e1.dot(dir_cross_e2);
    if (fabs(det) < EPSILON) {
        return {};
    }
    const auto f = 1 / det;
    const auto p1_to_origin = ray.origin - p1;
    const auto u = f * p1_to_origin.dot(dir_cross_e2);
    if (u < 0 || u > 1) {
        return {};
    }
    const auto origin_cross_e1 = p1_to_origin.cross3(e1);
    const auto v = f * ray.direction.dot(origin_cross_e1);
    if (v < 0 || (u + v) > 1) {
        return {};
    }
    const auto t = f * e2.dot(origin_cross_e1);
    return {Intersection(t, this, u, v)};
}

Vector4f SmoothTriangle::local_normal_at(const Vector4f& local_point, const Intersection& i) const {
//    std::cout << "Intersection u: " << i.u << " v: " << i.v << std::endl;
//    std::cout << "n1: " << n1 << " n2: " << n2 << " n3: " << n3 << std::endl;
//    std::cout << "n2 * i.u: " << n2 * i.u << std::endl;
//    std::cout << "n3 * i.v: " << n3 * i.v << std::endl;
//    std::cout << "n1 * (1 - i.u - i.v): " << n1 * (1 - i.u - i.v) << std::endl;
    return n2 * i.u + n3 * i.v + n1 * (1 - i.u - i.v);
}
