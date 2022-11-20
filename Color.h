//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/17/22.
//
#ifndef RAYCASTER_COLOR_H
#define RAYCASTER_COLOR_H

#include <Eigen/Core>
#include "MathUtils.h"


class Color : public Eigen::Vector3f {
public:
    Color() : Eigen::Vector3f(0.0f, 0.0f, 0.0f) { this->r = this->x(); this->g = this->y(); this->b = this->z(); }
    Color(float r, float g, float b) : Eigen::Vector3f(r, g, b) { this->r = r; this->g = g; this->b = b; }
    Color(const Eigen::Vector3f& v) : Eigen::Vector3f(v) { this->r = v.x(); this->g = v.y(); this->b = v.z(); }

    float r, g, b;
    // Equality
    bool operator==(const Color& rhs) const {
        return (is_equal(x(), rhs.x()) && is_equal(y(), rhs.y()) && is_equal(z(), rhs.z()));
    }
    // Inequality
    bool operator!=(const Color& rhs) const {
        return !(*this == rhs);
    }
    // Adding
    Color operator+(const Color& rhs) const {
        return Color(x() + rhs.x(), y() + rhs.y(), z() + rhs.z());
    }
    // Subtracting
    Color operator-(const Color& rhs) const {
        return Color(x() - rhs.x(), y() - rhs.y(), z() - rhs.z());
    }
    // Multiplying by a scalar
    Color operator*(const float& scalar) const {
        return Color(x() * scalar, y() * scalar, z() * scalar);
    }
    // Multiplication
    Color operator*(const Color& rhs) const {
        return Color(x() * rhs.x(), y() * rhs.y(), z() * rhs.z());
    }
};



#endif //RAYCASTER_COLOR_H
