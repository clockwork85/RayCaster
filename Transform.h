//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/17/22.
//

#ifndef RAYCASTER_TRANSFORMS_H
#define RAYCASTER_TRANSFORMS_H

#include <Eigen/Core>
#include <Eigen/Geometry>

using Vector3f = Eigen::Vector3f;
using Vector4f = Eigen::Vector4f;
using Matrix4f = Eigen::Matrix4f;

class Transformation {
public:
    Transformation() : m_transform(Matrix4f::Identity()) {}
    Transformation(const Matrix4f& transform) : m_transform(transform) {}
    Transformation(const Transformation& other) : m_transform(other.m_transform) {}

    const Matrix4f& matrix() const;

    static Transformation identity();
    Transformation& translate(float x, float y, float z);
    Transformation& rotate(float angle, float x, float y, float z);
    Transformation& rotate_x(float angle);
    Transformation& rotate_y(float angle);
    Transformation& rotate_z(float angle);
    Transformation& scale(float x, float y, float z);
    Transformation& shear(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y);
private:
    Matrix4f m_transform;
};

namespace Transform {
    Matrix4f identity();
    Matrix4f translate(float x, float y, float z);
    Matrix4f translate(const Vector4f& v);
    Matrix4f rotate(float angle, float x, float y, float z);
    Matrix4f rotate_x(float angle);
    Matrix4f rotate_y(float angle);
    Matrix4f rotate_z(float angle);
    Matrix4f scale(float x, float y, float z);
    Matrix4f scale(const Vector4f& v);
    Matrix4f shear(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y);
}


#endif //RAYCASTER_TRANSFORMS_H
