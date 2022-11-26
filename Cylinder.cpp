//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/25/22.
//

#include "Cylinder.h"
#include <iostream>

void Cylinder::intersect_caps(const Ray& ray, std::vector<Intersection>& xs) const {
    if(!closed || is_equal(fabs(ray.direction.y()), 0.0, EPSILON)) {
        return;
    }
    auto t = (minimum - ray.origin.y()) / ray.direction.y();
    if(check_cap(ray, t)) {
        xs.push_back(Intersection(t, this));
    }
    t = (maximum - ray.origin.y()) / ray.direction.y();
    if(check_cap(ray, t)) {
        xs.push_back(Intersection(t, this));
    }
}

std::vector<Intersection> Cylinder::local_intersect(const Ray& ray) const {
    std::vector<Intersection> xs;
    auto a = (ray.direction.x() * ray.direction.x()) + (ray.direction.z() * ray.direction.z());
    if(is_equal(fabs(a), 0.0, EPSILON)) {
        intersect_caps(ray, xs);
        return xs;
    }
    auto b = 2 * ray.origin.x() * ray.direction.x() + 2 * ray.origin.z() * ray.direction.z();
    auto c = (ray.origin.x() * ray.origin.x()) + (ray.origin.z() * ray.origin.z()) - 1;
    auto discriminant = (b * b) - (4 * a * c);
    if(discriminant < 0) {
        return {};
    }
    auto t0 = (-b - sqrt(discriminant)) / (2.0f * a);
    auto t1 = (-b + sqrt(discriminant)) / (2.0f * a);
    if(t0 > t1) {
        std::swap(t0, t1);
    }
    auto y0 = ray.origin.y() + t0 * ray.direction.y();
    auto y1 = ray.origin.y() + t1 * ray.direction.y();
    if(minimum < y0 && y0 < maximum) {
        xs.push_back(Intersection(t0, this));
    }
    if(minimum < y1 && y1 < maximum) {
        xs.push_back(Intersection(t1, this));
    }
//    std::cout << "Length before intersect_caps: " << xs.size() << std::endl;
    intersect_caps(ray, xs);
//    std::cout << "Length after intersect_caps: " << xs.size() << std::endl;
    return xs;
}

bool Cylinder::check_cap(const Ray& ray, float t) const {
    auto x = ray.origin.x() + t * ray.direction.x();
    auto z = ray.origin.z() + t * ray.direction.z();
    const auto radius = (x * x + z * z);
    return (radius < 1 || is_equal(radius, 1.0f, EPSILON));
}



Vector4f Cylinder::local_normal_at(const Vector4f& local_point) const {
    return create_vector(local_point.x(), 0, local_point.z());
}