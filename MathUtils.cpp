//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/11/22.
//

#include "MathUtils.h"
#include <math.h>

bool is_equal(float a, float b, float epsilon) {
    return fabs(a - b) < epsilon;
}

Eigen::Transform<float, 3, Eigen::Affine> shear3d(float xy, float xz, float yx, float yz, float zx, float zy) {
    Eigen::Transform<float, 3, Eigen::Affine> shear;
    shear.matrix() << 1.0f, xy, xz, 0.0f,
            yx, 1.0f, yz, 0.0f,
            zx, zy, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f;
    return shear;
}

Tuple Tuple::translate(Eigen::Vector3f translation) const {
    Eigen::Transform<float, 3, Eigen::Affine> t = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    t.translate(translation);
    return t * (*this);
}

Tuple Tuple::translate_inv(Eigen::Vector3f translation) const {
    Eigen::Transform<float, 3, Eigen::Affine> t = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    t.translate(-translation);
    return t * (*this);
}

Tuple Tuple::scale(Eigen::Vector3f scale) const {
    Eigen::Transform<float, 3, Eigen::Affine> t = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    t.scale(scale);
    return t * (*this);
}

Tuple Tuple::scale_inv(Eigen::Vector3f scale) const {
    Eigen::Transform<float, 3, Eigen::Affine> t = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    t.scale(scale);
    return t.inverse() * (*this);
}

Tuple Tuple::rotate_x(float radians) const {
    Eigen::Transform<float, 3, Eigen::Affine> t = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    t.rotate(Eigen::AngleAxisf(radians, Eigen::Vector3f::UnitX()));
    return t * (*this);
}

Tuple Tuple::rotate_x_inv(float radians) const {
    Eigen::Transform<float, 3, Eigen::Affine> t = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    t.rotate(Eigen::AngleAxisf(-radians, Eigen::Vector3f::UnitX()));
    return t * (*this);
}

Tuple Tuple::rotate_y(float radians) const {
    Eigen::Transform<float, 3, Eigen::Affine> t = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    t.rotate(Eigen::AngleAxisf(radians, Eigen::Vector3f::UnitY()));
    return t * (*this);
}

Tuple Tuple::rotate_y_inv(float radians) const {
    Eigen::Transform<float, 3, Eigen::Affine> t = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    t.rotate(Eigen::AngleAxisf(-radians, Eigen::Vector3f::UnitY()));
    return t * (*this);
}

Tuple Tuple::rotate_z(float radians) const {
    Eigen::Transform<float, 3, Eigen::Affine> t = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    t.rotate(Eigen::AngleAxisf(radians, Eigen::Vector3f::UnitZ()));
    return t * (*this);
}

Tuple Tuple::rotate_z_inv(float radians) const {
    Eigen::Transform<float, 3, Eigen::Affine> t = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    t.rotate(Eigen::AngleAxisf(-radians, Eigen::Vector3f::UnitZ()));
    return t * (*this);
}