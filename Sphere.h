//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/19/22.
//

#ifndef RAYCASTER_SPHERE_H
#define RAYCASTER_SPHERE_H

#include "Shape.h"
#include <vector>

using Vector4f = Eigen::Vector4f;
using Matrix4f = Eigen::Matrix4f;


struct Sphere : public Shape {
    Vector4f local_normal_at(const Vector4f& local_point) const override;
    std::vector<Intersection> local_intersect(const Ray& local_ray) const override;
};

//class Sphere {
//public:
//    Sphere() : center(0.0f, 0.0f, 0.0f, 1.0f), material(Material()) {}
//
//    float id = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//    // Center of the sphere is the translation of the transform
//    Vector4f center = get_center();
//    Material material;
//
//    Vector4f get_center() {
//        return Vector4f(m_transform(0, 3), m_transform(1, 3), m_transform(2, 3), 1.0f);
//    }
//
//    void transform(Matrix4f transform) {
//        m_transform = transform.matrix() * m_transform;
//        m_inverse = m_transform.inverse();
//        center = get_center();
//    }
//
//    void set_transform(Matrix4f t) {
//        m_transform = t.matrix();
//        m_inverse = m_transform.inverse();
//        center = get_center();
//    }
//
//    Matrix4f matrix() const {
//        return m_transform;
//    }
//
//    Matrix4f inverse() const {
//        return m_inverse;
//    }
//
//    bool operator==(const Sphere& rhs) const {
//        return (center == rhs.center && m_transform == rhs.matrix());
//    }
//private:
//    Matrix4f m_transform { Matrix4f::Identity() };
//    Matrix4f m_inverse { Matrix4f::Identity() };
//
//};



#endif //RAYCASTER_SPHERE_H
