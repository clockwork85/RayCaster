//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/23/22.
//

#ifndef RAYCASTER_PLANE_H
#define RAYCASTER_PLANE_H

#include "Shape.h"
#include <memory>

struct Plane : public Shape
{
    inline Vector4f local_normal_at(const Vector4f& local_point, const Intersection& i={}) const override
    {
        return create_vector(0, 1, 0);
    }
    inline std::vector<Intersection> local_intersect(const Ray& local_ray) const override
    {
        if (std::abs(local_ray.direction.y()) < EPSILON) {
            return {};
        }
        const auto t = -local_ray.origin.y() / local_ray.direction.y();
        return {Intersection(t, this)};
    }
};
#endif //RAYCASTER_PLANE_H
