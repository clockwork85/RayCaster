//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/11/22.
//
#pragma once
#include <math.h>
#include <Eigen/Dense>

#ifndef RAYCASTER_MATHUTILS_H
#define RAYCASTER_MATHUTILS_H

bool is_equal(float a, float b, float epsilon = 0.00001f);

class Point {
public:
    float x, y, z;
    Point(float x, float y, float z) : x(x), y(y), z(z) {}
};

class Vector {
public:
    float x, y, z;
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}

    // Equality
    bool operator==(const Vector& rhs) const {
        return is_equal(x, rhs.x) && is_equal(y, rhs.y) && is_equal(z, rhs.z);
    }
    // Inequality
    bool operator!=(const Vector& rhs) const {
        return !(*this == rhs);
    }
    // Magnitude
    float magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }
    // Normalize
    Vector normalize() const {
        float mag = this->magnitude();
        return Vector( x / mag, y / mag, z / mag);
    }
    // Dot product
    float dot(const Vector& rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }
    // Cross product
    Vector cross(const Vector& rhs) const {
        return Vector(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
    }
};

class Tuple {
public:
    float x, y, z, w;
    Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Tuple(Point p) : x(p.x), y(p.y), z(p.z), w(1.0f) {}
    Tuple(Vector v) : x(v.x), y(v.y), z(v.z), w(0.0f) {}

    // Equality
    bool operator==(const Tuple& other) const {
        return is_equal(x, other.x) && is_equal(y, other.y) && is_equal(z, other.z) && is_equal(w, other.w);
    }
    // Addition
    Tuple operator+(const Tuple& other) const {
        return Tuple(x + other.x, y + other.y, z + other.z, w + other.w);
    }
    //Subtraction
    Tuple operator-(const Tuple& other) const {
        return Tuple(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    // Negation
    Tuple operator-() const {
        return Tuple(-x, -y, -z, -w);
    }
    // Scalar Multiplication
    Tuple operator*(float scalar) const {
        return Tuple(x * scalar, y * scalar, z * scalar, w * scalar);
    }
    // Scalar Division
    Tuple operator/(float scalar) const {
        return Tuple(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    bool isPoint() const { return w == 1.0f; }
    bool isVector() const { return w == 0.0f; }
};

#endif //RAYCASTER_MATHUTILS_H
