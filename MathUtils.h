//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/11/22.
//
#pragma once
#include <Eigen/Dense>
#include <math.h>

#ifndef RAYCASTER_MATHUTILS_H
#define RAYCASTER_MATHUTILS_H

using Vector3f = Eigen::Vector3f;
using Vector4f = Eigen::Vector4f;

constexpr float EPSILON = 0.001f;

bool is_equal(float a, float b, float epsilon = EPSILON);

Eigen::Transform<float, 3, Eigen::Affine> shear3d(float xy, float xz, float yx, float yz, float zx, float zy);

inline Vector4f create_point(float x, float y, float z) {
    return Vector4f(x, y, z, 1.0f);
}

inline Vector4f create_vector(float x, float y, float z) {
    return Vector4f(x, y, z, 0.0f);
}

inline Vector4f create_point(const Vector3f& v) {
    return Vector4f(v.x(), v.y(), v.z(), 1.0f);
}

inline Vector4f create_vector(const Vector3f& v) {
    return Vector4f(v.x(), v.y(), v.z(), 0.0f);
}

inline bool is_point(const Vector4f& v) {
    return v.w() == 1.0f;
}

inline bool is_vector(const Vector4f& v) {
    return v.w() == 0.0f;
}

#endif //RAYCASTER_MATHUTILS_H
