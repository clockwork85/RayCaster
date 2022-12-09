//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/23/22.
//

#include "Sphere.h"
#include "Intersection.h"

//using Vector4f = Eigen::Vector4f;
//using Matrix4f = Eigen::Matrix4f;

Vector4f Sphere::local_normal_at(const Vector4f& local_point, const Intersection& i) const {
    return local_point - create_point(0, 0, 0);
}

std::vector<Intersection> Sphere::local_intersect(const Ray& ray) const {
    const auto sphere_to_ray = ray.origin - create_point(0, 0, 0);
    const auto a = ray.direction.dot(ray.direction);
    const auto b = 2 * ray.direction.dot(sphere_to_ray);
    const auto c = sphere_to_ray.dot(sphere_to_ray) - 1;
    const auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return {};
    }

    const auto t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    const auto t2 = (-b + std::sqrt(discriminant)) / (2 * a);
    return {Intersection(t1, this), Intersection(t2, this)};
}
