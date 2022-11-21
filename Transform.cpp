//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/17/22.
//

#include "Transform.h"
#include <Eigen/Geometry>

const Matrix4f& Transformation::matrix() const { return m_transform; }

Transformation Transformation::identity() {
    return Transformation{};
}
Transformation& Transformation::translate(float x, float y, float z) {
    m_transform = Transform::translate(x, y, z) * m_transform;
    return *this;
}

Transformation& Transformation::rotate(float angle, float x, float y, float z) {
    m_transform = Transform::rotate(angle, x, y, z) * m_transform;
    return *this;
}

Transformation& Transformation::rotate_x(float angle) {
    m_transform = Transform::rotate_x(angle) * m_transform;
    return *this;
}

Transformation& Transformation::rotate_y(float angle) {
    m_transform = Transform::rotate_y(angle) * m_transform;
    return *this;
}

Transformation& Transformation::rotate_z(float angle) {
    m_transform = Transform::rotate_z(angle) * m_transform;
    return *this;
}

Transformation& Transformation::scale(float x, float y, float z) {
    m_transform = Transform::scale(x, y, z) * m_transform;
    return *this;
}

Transformation& Transformation::shear(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y) {
    m_transform = Transform::shear(x_y, x_z, y_x, y_z, z_x, z_y) * m_transform;
    return *this;
}

namespace Transform {
    Matrix4f identity() {
        return Matrix4f::Identity();
    }
    Matrix4f translate(float x, float y, float z) {
        Matrix4f translate = Matrix4f::Identity();
        translate(0, 3) = x;
        translate(1, 3) = y;
        translate(2, 3) = z;
        return translate;
    }
    Matrix4f rotate(float angle, float x, float y, float z) {
        Eigen::Affine3f transform = Eigen::Affine3f::Identity();
        transform.rotate(Eigen::AngleAxisf(angle, Eigen::Vector3f(x, y, z)));
        return transform.matrix();
    }
    Matrix4f rotate_x(float angle) {
        Eigen::Affine3f transform = Eigen::Affine3f::Identity();
        transform.rotate(Eigen::AngleAxisf(angle, Eigen::Vector3f(1.0f, 0.0f, 0.0f)));
        return transform.matrix();
    }
    Matrix4f rotate_y(float angle) {
        Eigen::Affine3f transform = Eigen::Affine3f::Identity();
        transform.rotate(Eigen::AngleAxisf(angle, Eigen::Vector3f(0.0f, 1.0f, 0.0f)));
        return transform.matrix();
    }
    Matrix4f rotate_z(float angle) {
        Eigen::Affine3f transform = Eigen::Affine3f::Identity();
        transform.rotate(Eigen::AngleAxisf(angle, Eigen::Vector3f(0.0f, 0.0f, 1.0f)));
        return transform.matrix();
    }
    Matrix4f scale(float x, float y, float z) {
        Matrix4f scale = Matrix4f::Identity();
        scale(0, 0) = x;
        scale(1, 1) = y;
        scale(2, 2) = z;
        return scale;
    }
    Matrix4f shear(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y) {
        Matrix4f shear = Matrix4f::Identity();
        shear(0, 1) = x_y;
        shear(0, 2) = x_z;
        shear(1, 0) = y_x;
        shear(1, 2) = y_z;
        shear(2, 0) = z_x;
        shear(2, 1) = z_y;
        return shear;
    }
    Matrix4f view_transform(const Vector4f& from, const Vector4f& to, const Vector4f& up) {
        Vector4f forward = (to - from).normalized();
        Vector4f upn = up.normalized();
        Vector4f left = forward.cross3(upn);
        Vector4f true_up = left.cross3(forward);
        Matrix4f orientation = Matrix4f::Identity();
        orientation(0, 0) = left.x();
        orientation(0, 1) = left.y();
        orientation(0, 2) = left.z();
        orientation(1, 0) = true_up.x();
        orientation(1, 1) = true_up.y();
        orientation(1, 2) = true_up.z();
        orientation(2, 0) = -forward.x();
        orientation(2, 1) = -forward.y();
        orientation(2, 2) = -forward.z();
        Matrix4f translation = Matrix4f::Identity();
        translation(0, 3) = -from.x();
        translation(1, 3) = -from.y();
        translation(2, 3) = -from.z();
        return orientation * translation;
    }
}


