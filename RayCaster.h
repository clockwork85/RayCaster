//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/13/22.
//

#ifndef RAYCASTER_RAYCASTER_H
#define RAYCASTER_RAYCASTER_H

#include "MathUtils.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <vector>
#include <iostream>

using Vector = Eigen::Vector3f;

class Sphere {
public:
    Sphere() : center(0.0f, 0.0f, 0.0f, 1.0f), radius(1.0f) {}

    float id = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    Eigen::Matrix4f transform = Eigen::Matrix4f::Identity();
    // Center of the sphere is the translation of the transform
    Tuple center = get_center();
    // Get radius of a sphere from the transform
    float radius = get_radius();

    void set_transform(Eigen::Matrix4f t) {
        transform = t;
    }
    Tuple get_center() {
        return Tuple(transform(0, 3), transform(1, 3), transform(2, 3), 1.0f);
    }

    float get_radius() {
        return transform(0, 0);
    }

    void set_transform(Eigen::Transform<float, 3, Eigen::Affine> t) {
        transform = t.matrix();
        center = get_center();
        radius = get_radius();
    }

    bool operator==(const Sphere& rhs) const {
        return (center == rhs.center && radius == rhs.radius && transform == rhs.transform);
    }


};


class Intersection {
public:
    Intersection() : t(0.0f), object(nullptr) {}
    Intersection(float t, Sphere* object) : t(t), object(object) { }

    float t;
    Sphere* object;
};

class Ray {
public:
    Ray() : origin(0.0f, 0.0f, 0.0f, 1.0f), direction(0.0f, 0.0f, 0.0f, 0.0f) {}
    Ray(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) : origin(Tuple(origin)), direction(Tuple(direction)) {}
    Ray(const Point point, const Vector vector) : origin(Tuple(point)), direction(Tuple(vector)) {}
    Ray(const Tuple point, const Tuple vector) : origin(point), direction(vector) {}
    Ray(const Ray& ray) : origin(ray.origin), direction(ray.direction) {}

    Tuple origin;
    Tuple direction;
    std::vector<Intersection> intersections;

    Eigen::Vector4f position(float t) const {
        return origin + (direction * t);
    }

    std::vector<Intersection> intersect(Sphere* object) const {
        Tuple sphere_to_ray = origin - object->center;
        float a = direction.dot(direction);
        float b = 2 * direction.dot(sphere_to_ray);
        float c = sphere_to_ray.dot(sphere_to_ray) - (object->radius * object->radius);
        float discriminant = (b * b) - (4 * a * c);

        if (discriminant < 0) {
            return std::vector<Intersection>();
        }
        else {
            float t1 = (-b - sqrt(discriminant)) / (2 * a);
            float t2 = (-b + sqrt(discriminant)) / (2 * a);
            return std::vector<Intersection>({ Intersection(t1, object), Intersection(t2, object) });
        }
    }
    Ray translate(const Eigen::Vector3f& translation) const {
        return Ray(origin + translation, direction);
    }

    Ray scale(const Eigen::Vector3f& scale) const {
        Eigen::Transform<float, 3, Eigen::Affine> transform = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
        transform.scale(scale);
        Tuple new_origin = transform * origin;
        Tuple new_direction = transform * direction;
        return Ray(new_origin, new_direction);
    }
};

Intersection hit(const std::vector<Intersection>& intersections) {
    Intersection closest = Intersection();
    for (Intersection intersection : intersections) {
        if (intersection.t > 0 && (intersection.t < closest.t || closest.t == 0)) {
            closest = intersection;
        }
    }
    return closest;
}

#endif //RAYCASTER_RAYCASTER_H
