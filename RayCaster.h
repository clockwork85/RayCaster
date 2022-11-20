//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/13/22.
//

#ifndef RAYCASTER_RAYCASTER_H
#define RAYCASTER_RAYCASTER_H

#include "Lights.h"
#include "MathUtils.h"
#include "Sphere.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <vector>
#include <iostream>

using Vector3f = Eigen::Vector3f;
using Vector4f = Eigen::Vector4f;
using Matrix4f = Eigen::Matrix4f;


class Intersection {
public:
    Intersection() : t(0.0f), object(nullptr) {}
    Intersection(float t, Sphere* sphere) : t(t), object(sphere) {}

    float t;
    Sphere* object;
};

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
};

Ray transform_ray(Ray& ray, Matrix4f transform) {
    Vector4f origin = transform * ray.origin;
    Vector4f direction = transform * ray.direction;
    return Ray(origin, direction);
}

std::vector<Intersection> intersect(Sphere* sphere, Ray& ray) {
    std::vector<Intersection> intersections;
    Ray ray_local = transform_ray(ray, sphere->inverse());
    Vector4f sphere_to_ray = ray_local.origin - create_point(0.0f, 0.0f, 0.0f);
    float a = ray_local.direction.dot(ray_local.direction);
    float b = 2 * ray_local.direction.dot(sphere_to_ray);
    float c = sphere_to_ray.dot(sphere_to_ray) - 1.0f;
    float discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0) {
        return intersections;
    }
    float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
    float t2 = (-b + sqrt(discriminant)) / (2.0f * a);
    intersections.push_back(Intersection(t1, sphere));
    intersections.push_back(Intersection(t2, sphere));
    return intersections;
}

Vector4f normal_at(Sphere* sphere, Vector4f& world_point) {
    Vector4f object_point = sphere->inverse() * world_point;
    Vector4f object_normal = object_point - create_point(0.0f, 0.0f, 0.0f);
    Vector4f world_normal = sphere->inverse().transpose() * object_normal;
    world_normal(3) = 0.0f;
    return world_normal.normalized();
}

Vector4f reflect(Vector4f& in, Vector4f& normal) {
    return in - (normal * 2 * in.dot(normal));
}

Intersection hit(std::vector<Intersection> intersections) {
    Intersection closest = Intersection();
    for (Intersection intersection : intersections) {
        if (intersection.t > 0 && (intersection.t < closest.t || closest.t == 0)) {
            closest = intersection;
        }
    }
    return closest;
}

Color lighting(Material& material, PointLight& light, Vector4f& position, Vector4f& eye, Vector4f& normal) {
    Color effective_color = material.color * light.intensity();
    Vector4f lightv = (light.position() - position).normalized();
    float light_dot_normal = lightv.dot(normal);
    Color ambient = effective_color * material.ambient;
    Color diffuse;
    Color specular;
    if (light_dot_normal < 0) {
        diffuse = Color(0.0f, 0.0f, 0.0f);
        specular = Color(0.0f, 0.0f, 0.0f);
    } else {
        diffuse = effective_color * material.diffuse * light_dot_normal;
        Vector4f inv_light_vector = -lightv;
        Vector4f reflect_vector = reflect(inv_light_vector, normal);
        float reflect_dot_eye = reflect_vector.dot(eye);
        if (reflect_dot_eye <= 0) {
            specular = Color(0.0f, 0.0f, 0.0f);
        } else {
            float factor = pow(reflect_dot_eye, material.shininess);
            specular = light.intensity() * material.specular * factor;
        }
    }
    return ambient + diffuse + specular;
}



#endif //RAYCASTER_RAYCASTER_H
