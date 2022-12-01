//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/13/22.
//

#ifndef RAYCASTER_RAYCASTER_H
#define RAYCASTER_RAYCASTER_H

#include "Camera.h"
#include "Canvas.h"
#include "Computation.h"
#include "Intersection.h"
#include "MathUtils.h"
#include "Ray.h"
#include "Sphere.h"
#include "World.h"
#include <Eigen/Core>
// #include <Eigen/Geometry>
#include <vector>
#include <iostream>

using Vector4f = Eigen::Vector4f;

struct PointLight;
struct Light;

std::vector<Intersection> intersect_world(const World& world, const Ray& ray);
Vector4f normal_at(const Sphere* sphere, const Vector4f& world_point);
Vector4f reflect(const Vector4f& in, const Vector4f& normal);
Intersection hit(std::vector<Intersection> intersections);
Color lighting(const Material& material, const Shape* shape, const Light& light, const Vector4f& position, const Vector4f& eye, const Vector4f& normal, const float intensity);
bool is_shadowed(const World& world, const Vector4f& light_position, const Vector4f& point);
Computation prepare_computations(const Intersection& intersection, const Ray& ray, const std::vector<Intersection>& intersections = {});
Color shade_hit(const World& world, const Computation& comps, const int remaining=4);
Color color_at(const World& world, const Ray& ray, const int remaining=4);
Color reflected_color(const World& world, const Computation& comps, const int remaining=4);
Color refracted_color(const World& world, const Computation& comps, const int remaining=4);
float schlick(const Computation& comps);
Ray ray_for_pixel(const Camera& camera, const int px, const int py);
Canvas render(const Camera& camera, const World& world);

// float intensity_at(const Light* light,      const Vector4f& point, const World& world);
float intensity_at_pointlight(const PointLight& light, const Vector4f& point, const World& world);
float intensity_at_arealight(const AreaLight& light, const Vector4f& point, const World& world);
Vector4f point_on_light(const AreaLight& light, const float u, const float v);



#endif //RAYCASTER_RAYCASTER_H
