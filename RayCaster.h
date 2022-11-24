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

std::vector<Intersection> intersect_world(const World& world, const Ray& ray) {
    std::vector<Intersection> totintersections;
    for (const Sphere& sphere : world.objects) {
        std::vector<Intersection> intersections = sphere.intersect(ray);
        // Put all intersections into one vector
        for ( const Intersection& intersection : intersections) {
            totintersections.push_back(intersection);
        }
    }

    // Sort intersections by t
    std::sort(totintersections.begin(), totintersections.end(), [](const Intersection& a, const Intersection& b) {
        return a.t < b.t;
    });

    // Print out all intersections
//    for (const Intersection& intersection : intersections) {
//        std::cout << "Intersection: " << intersection.t << std::endl;
//    }

    return totintersections;
}

Vector4f normal_at(const Sphere* sphere, const Vector4f& world_point) {
    Vector4f object_point = sphere->inverse() * world_point;
    Vector4f object_normal = object_point - create_point(0.0f, 0.0f, 0.0f);
    Vector4f world_normal = sphere->inverse().transpose() * object_normal;
    world_normal(3) = 0.0f;
    return world_normal.normalized();
}

Vector4f reflect(const Vector4f& in, const Vector4f& normal) {
    return in - (normal * 2 * in.dot(normal));
}

Intersection hit(std::vector<Intersection> intersections) {
//    for (Intersection intersection : intersections) {
//        if (intersection.t > 0 && (intersection.t < closest.t || closest.t == 0)) {
//            closest = intersection;
//        }
//    }
//    return closest;
    std::sort(intersections.begin(), intersections.end(), [](const Intersection& a, const Intersection& b) {
        return a.t < b.t;
    });
    // Print out all intersections
    for (const Intersection& intersection : intersections) {
        if (intersection.t > 0) {
            return intersection;
        }
    }

//    for (Intersection intersection : intersections) {
//        if (intersection.t >= 0) {
//            return {intersection};
//        }
//    }
//    std::cout << "No hit" << std::endl;
    return Intersection();
}

Color lighting(const Material& material, const PointLight& light, const Vector4f& position, const Vector4f& eye, const Vector4f& normal, const bool in_shadow) {
    Color effective_color = material.color * light.intensity();
    Vector4f light_vector = (light.position() - position).normalized();
    const float light_dot_normal = light_vector.dot(normal);
    Color ambient = effective_color * material.ambient;
    Color diffuse;
    Color specular;
    if (light_dot_normal < 0 || in_shadow) {
        diffuse = Color(0.0f, 0.0f, 0.0f);
        specular = Color(0.0f, 0.0f, 0.0f);
    } else {
        diffuse = effective_color * material.diffuse * light_dot_normal;
        Vector4f inv_light_vector = -light_vector;
        Vector4f reflect_vector = reflect(inv_light_vector, normal);
        float reflect_dot_eye = reflect_vector.dot(eye);
        if (reflect_dot_eye <= 0) {
            specular = Color(0.0f, 0.0f, 0.0f);
        } else {
            float factor = pow(reflect_dot_eye, material.shininess);
            specular = light.intensity() * material.specular * factor;
        }
    }
//    std::cout << "Ambient: " << ambient << std::endl;
//    std::cout << "Diffuse: " << diffuse << std::endl;
//    std::cout << "Specular: " << specular << std::endl;
    return ambient + diffuse + specular;
}


bool is_shadowed(const World& world, const Vector4f& light_position, const Vector4f& point) {
//    std::cout << "Point: " << point << std::endl;
    const Vector4f v = light_position - point;
//    std::cout << "v: " << v << std::endl;
    const float distance = v.norm();
    const Vector4f direction = v.normalized();
    const Ray r = Ray(point, direction);
    const std::vector<Intersection> intersections = intersect_world(world, r);
    const auto h = hit(intersections);
//    std::cout << "Hit: " << h.t << std::endl;
//    std::cout << "Object is nullptr: " << (h.object == nullptr) << std::endl;
//    std::cout << "Distance: " << distance << std::endl;

    return (h.t > 0) && (h.t < distance);
}


Computation prepare_computations(const Intersection& intersection, const Ray& ray) {
    Computation comps;
    comps.t = intersection.t;
    comps.point = ray.position(comps.t);
    comps.object = intersection.object;
    comps.eyev = -ray.direction;
    comps.normalv = comps.object->normal_at(comps.point);
    if (comps.normalv.dot(comps.eyev) < 0) {
        comps.inside = true;
        comps.normalv = -comps.normalv;
    } else {
        comps.inside = false;
    }
    comps.over_point = comps.point + comps.normalv * EPSILON;
    return comps;
}

Color shade_hit(const World& world, const Computation& comps) {
    Color surface = Color(0.0f, 0.0f, 0.0f);
    bool shadowed = is_shadowed(world, world.lights[0].position(), comps.over_point);
//    std::cout << "Shadowed: " << shadowed << std::endl;
//    std::cout << "Point: " << comps.point << std::endl;
//    std::cout << "Over point: " << comps.over_point << std::endl;

//    for (PointLight& light : world.lights) {
    surface = surface + lighting(comps.object->material, world.lights[0], comps.point, comps.eyev, comps.normalv, shadowed);
 //   }
    return surface;
}

Color color_at(const World& world, const Ray& ray) {
    std::vector<Intersection> intersections = intersect_world(world, ray);
    const auto intersection = hit(intersections);
    if(intersection.object == nullptr)  {
        return Color(0.0f, 0.0f, 0.0f);
    }
    const auto comps = prepare_computations(intersection, ray);
    return shade_hit(world, comps);
//    if (intersection.t == 0) {
//        return Color(0.0f, 0.0f, 0.0f);
//    }
//    Computation comps = prepare_computations(intersection, ray);
//    return shade_hit(world, comps);
}

Ray ray_for_pixel(Camera camera, int px, int py) {
    float xoffset = (px + 0.5f) * camera.pixel_size;
    float yoffset = (py + 0.5f) * camera.pixel_size;
    float world_x = camera.half_width - xoffset;
    float world_y = camera.half_height - yoffset;
    Vector4f pixel = camera.transform.inverse() * create_point(world_x, world_y, -1.0f);
    Vector4f origin = camera.transform.inverse() * create_point(0.0f, 0.0f, 0.0f);
    Vector4f direction = (pixel - origin).normalized();
    return Ray(origin, direction);
}

Canvas render(Camera camera, World world) {
    Canvas image = Canvas(camera.hsize, camera.vsize);
    for (int y = 0; y < camera.vsize; y++) {
        for (int x = 0; x < camera.hsize; x++) {
            Ray ray = ray_for_pixel(camera, x, y);
            Color color = color_at(world, ray);
            image.write_pixel(x, y, color);
        }
    }
    return image;
}



#endif //RAYCASTER_RAYCASTER_H
