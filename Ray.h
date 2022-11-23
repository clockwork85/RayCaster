//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/23/22.
//

#ifndef RAYCASTER_RAY_H
#define RAYCASTER_RAY_H

#include <Eigen/Core>

using Vector4f = Eigen::Vector4f;
using Matrix4f = Eigen::Matrix4f;

class Ray {
public:
    Ray() : origin(0.0f, 0.0f, 0.0f, 1.0f), direction(0.0f, 0.0f, 0.0f, 0.0f) {}
    Ray(const Vector4f& origin, const Vector4f& direction) : origin(origin), direction(direction) {}
    Ray(const Ray& ray) : origin(ray.origin), direction(ray.direction) {}

    Vector4f origin;
    Vector4f direction;

    Vector4f position(float t) const {
        return origin + (direction * t);
    }
    Ray transform_ray(const Matrix4f& transform) const {
        return Ray(transform * origin, transform * direction);
    }
};

#endif //RAYCASTER_RAY_H
