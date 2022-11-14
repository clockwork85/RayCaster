//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/11/22.
//
#pragma once
#include <Eigen/Dense>
#include <math.h>

#ifndef RAYCASTER_MATHUTILS_H
#define RAYCASTER_MATHUTILS_H

using Vector = Eigen::Vector3f;

bool is_equal(float a, float b, float epsilon = 0.00001f);

class Point : public Eigen::Vector3f {
public:
    Point() : Eigen::Vector3f(0.0f, 0.0f, 0.0f) {}
    Point(float x, float y, float z) : Eigen::Vector3f(x, y, z) {}
    Point(const Eigen::Vector3f& v) : Eigen::Vector3f(v) {}
};

class Tuple : public Eigen::Vector4f {
public:
    Tuple() : Eigen::Vector4f(0.0f, 0.0f, 0.0f, 0.0f) {}
    Tuple(float x, float y, float z, float w) : Eigen::Vector4f(x, y, z, w) {}
    Tuple(const Eigen::Vector4f& v) : Eigen::Vector4f(v) {}
    Tuple(Point p) : Eigen::Vector4f(p.x(), p.y(), p.z(), 1.0f) {}
    Tuple(Vector v) : Eigen::Vector4f(v.x(), v.y(), v.z(), 0.0f) {}

    bool isPoint() const { return w() == 1.0f; }
    bool isVector() const { return w() == 0.0f; }

    // Equality
    bool operator==(const Tuple& rhs) const {
        return (is_equal(x(), rhs.x()) && is_equal(y(), rhs.y()) && is_equal(z(), rhs.z()) && is_equal(w(), rhs.w()));
    }
    // Inequality
    bool operator!=(const Tuple& rhs) const {
        return !(*this == rhs);
    }
    // Adding
    Tuple operator+(const Tuple& rhs) const {
        return Tuple(x() + rhs.x(), y() + rhs.y(), z() + rhs.z(), w() + rhs.w());
    }
    // Subtracting
    Tuple operator-(const Tuple& rhs) const {
        return Tuple(x() - rhs.x(), y() - rhs.y(), z() - rhs.z(), w() - rhs.w());
    }
    // Negation
    Tuple operator-() const {
        return Tuple(-x(), -y(), -z(), -w());
    }
    // Scalar Multiplication
    Tuple operator*(float scalar) const {
        return Tuple(x() * scalar, y() * scalar, z() * scalar, w() * scalar);
    }
    // Scalar Division
    Tuple operator/(float scalar) const {
        return Tuple(x() / scalar, y() / scalar, z() / scalar, w() / scalar);
    }
    // Magnitude
    float magnitude() const {
        // Use sqrt from math.h and not
        return this->magnitude();
    }
    Tuple translate(Eigen::Vector3f) const;
    Tuple translate_inv(Eigen::Vector3f) const;
    Tuple scale(Eigen::Vector3f) const;
    Tuple scale_inv(Eigen::Vector3f) const;
    Tuple rotate_x(float) const;
    Tuple rotate_x_inv(float) const;
    Tuple rotate_y(float) const;
    Tuple rotate_y_inv(float) const;
    Tuple rotate_z(float) const;
    Tuple rotate_z_inv(float) const;
    };

Eigen::Transform<float, 3, Eigen::Affine> shear3d(float xy, float xz, float yx, float yz, float zx, float zy);



//bool isPoint(const Eigen::Vector4f& v);
//bool isVector(const Eigen::Vector4f& v);
//
//Eigen::Vector4f tupleFromPoint(Point p, float w = 1.0f);
//Eigen::Vector4f tupleFromVector(Vector v, float w = 0.0f);

#endif //RAYCASTER_MATHUTILS_H
