//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/23/22.
//

#ifndef RAYCASTER_SHAPE_H
#define RAYCASTER_SHAPE_H

#include <cstdlib>
#include <vector>
#include <memory>
#include <Eigen/Core>
#include "Material.h"
#include "Ray.h"
#include "Intersection.h"

using Vector4f = Eigen::Vector4f;
using Matrix4f = Eigen::Matrix4f;

static int shape_count{0};

struct Shape
{
    virtual ~Shape() = default;
    Shape() = default;

    bool operator==(const Shape& object) const {
        return object.id == id;
    }

    inline void set_material(const Material& m) {
        material = m;
    }

    inline void set_transform(const Matrix4f& transform) {
        m_transform = transform;
        m_inverse_transform = m_transform.inverse();
    }

    [[nodiscard]] inline auto matrix() const {
        return m_transform;
    }

    [[nodiscard]] inline auto inverse() const {
        return m_inverse_transform;
    }

    [[nodiscard]] virtual Vector4f normal_at(const Vector4f& world_point) const {
        const Vector4f local_point = m_inverse_transform * world_point;
        const Vector4f local_normal = local_normal_at(local_point);
        Vector4f world_normal = m_inverse_transform.transpose() * local_normal;
        world_normal[3] = 0;
        return world_normal.normalized();
    }

    [[nodiscard]] virtual Vector4f local_normal_at(const Vector4f& world_point) const = 0;

    [[nodiscard]] std::vector<Intersection> intersect(const Ray& r) const {
        const auto local_ray = r.transform_ray(m_inverse_transform);
        return local_intersect(local_ray);
    }

    [[nodiscard]] virtual std::vector<Intersection> local_intersect(const Ray& r) const = 0;


    const int id{shape_count++};
    Material material;

private:
    Matrix4f m_transform{ Matrix4f::Identity() };
    Matrix4f m_inverse_transform{ Matrix4f::Identity() };
};


#endif //RAYCASTER_SHAPE_H
