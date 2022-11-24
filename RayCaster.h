//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/13/22.
//

#ifndef RAYCASTER_RAYCASTER_H
#define RAYCASTER_RAYCASTER_H

#include "Camera.h"
#include "Canvas.h"
#include "Computation.h"
#include "Lights.h"
#include "Intersection.h"
#include "MathUtils.h"
#include "Ray.h"
#include "Sphere.h"
#include "World.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <vector>
#include <iostream>

using Vector3f = Eigen::Vector3f;
using Vector4f = Eigen::Vector4f;
using Matrix4f = Eigen::Matrix4f;


//std::vector<Intersection> intersect(const Sphere* sphere, const Ray& ray) {
//    std::vector<Intersection> intersections;
//    Ray ray_local = ray.transform_ray(sphere->inverse());
//    Vector4f sphere_to_ray = ray_local.origin - create_point(0.0f, 0.0f, 0.0f);
//    float a = ray_local.direction.dot(ray_local.direction);
//    float b = 2 * ray_local.direction.dot(sphere_to_ray);
//    float c = sphere_to_ray.dot(sphere_to_ray) - 1.0f;
//    float discriminant = (b * b) - (4 * a * c);
//    if (discriminant < 0) {
//        return intersections;
//    }
//    float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
//    float t2 = (-b + sqrt(discriminant)) / (2.0f * a);
//    intersections.push_back(Intersection(t1, sphere));
//    intersections.push_back(Intersection(t2, sphere));
//    return intersections;
//}

std::vector<Intersection> intersect_world(const World& world, const Ray& ray);
Vector4f normal_at(const Sphere* sphere, const Vector4f& world_point);
Vector4f reflect(const Vector4f& in, const Vector4f& normal);
Intersection hit(std::vector<Intersection> intersections);
Color lighting(const Material& material, const PointLight& light, const Vector4f& position, const Vector4f& eye, const Vector4f& normal, const bool in_shadow);
bool is_shadowed(const World& world, const Vector4f& light_position, const Vector4f& point);
Computation prepare_computations(const Intersection& intersection, const Ray& ray);
Color shade_hit(const World& world, const Computation& comps);
Color color_at(const World& world, const Ray& ray);
Ray ray_for_pixel(const Camera& camera, const int px, const int py);
Canvas render(const Camera& camera, const World& world);



#endif //RAYCASTER_RAYCASTER_H
