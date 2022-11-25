//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/25/22.
//

#include "Cube.h"

std::vector<Intersection> Cube::local_intersect(const Ray& ray) const {
    auto x_bounds = check_axis(ray.origin.x(), ray.direction.x());
    auto y_bounds = check_axis(ray.origin.y(), ray.direction.y());
    auto z_bounds = check_axis(ray.origin.z(), ray.direction.z());

    auto t_min = std::max(std::max(x_bounds.t_min, y_bounds.t_min), z_bounds.t_min);
    auto t_max = std::min(std::min(x_bounds.t_max, y_bounds.t_max), z_bounds.t_max);

    if(t_min > t_max) {
        return {};
    }
    return {Intersection(t_min, this), Intersection(t_max, this)};
}

Vector4f Cube::local_normal_at(const Vector4f& point) const {
    auto max_c = std::max(std::max(fabs(point.x()), fabs(point.y())), fabs(point.z()));

    if(is_equal(max_c, fabs(point.x()))) {
        return Vector4f(point.x(), 0, 0, 0);
    } else if(is_equal(max_c, fabs(point.y()))) {
        return Vector4f(0, point.y(), 0, 0);
    } else {
        return Vector4f(0, 0, point.z(), 0);
    }
}

Bounds Cube::check_axis(float origin, float direction) const {
    auto t_min_numerator = -1 - origin;
    auto t_max_numerator = 1 - origin;

    float t_min, t_max;

    if(fabs(direction) >= EPSILON) {
        t_min = t_min_numerator / direction;
        t_max = t_max_numerator / direction;
    } else {
        t_min = t_min_numerator * INFINITY;
        t_max = t_max_numerator * INFINITY;
    }

    if(t_min > t_max) {
        std::swap(t_min, t_max);
    }

    return {t_min, t_max};
}