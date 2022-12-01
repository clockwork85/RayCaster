//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/17/22.
//
#ifndef RAYCASTER_COLOR_H
#define RAYCASTER_COLOR_H

#include <Eigen/Core>
#include "MathUtils.h"


class Color {
public:
    Color() : r(0.0f), g(0.0f), b(0.0f) {}
    Color(float r, float g, float b) : r(r), g(g), b(b) {}
    Color(const Eigen::Vector3f& v) : r(v.x()), g(v.y()), b(v.z()) {}

    float r, g, b;
    // Equality
    bool operator==(const Color& rhs) const {
        return (is_equal(r, rhs.r) && is_equal(g, rhs.g) && is_equal(b, rhs.b));
    }
    // Inequality
    bool operator!=(const Color& rhs) const {
        return !(*this == rhs);
    }
    // Adding
    Color operator+(const Color& rhs) const {
        return {r + rhs.r, g + rhs.g, b + rhs.b};
    }
    // Subtracting
    Color operator-(const Color& rhs) const {
        return {r - rhs.r, g - rhs.g, b - rhs.b};
    }
    // Multiplying by a scalar
    Color operator*(const float& scalar) const {
        return {r * scalar, g * scalar, b * scalar};
    }
    // Multiplication
    Color operator*(const Color& rhs) const {
        return {r * rhs.r, g * rhs.g, b * rhs.b};
    }
    // std::cout
    friend std::ostream& operator<<(std::ostream& os, const Color& c) {
        os << "Color(" << c.r << ", " << c.g << ", " << c.b << ")";
        return os;
    }
};

// Color constants
namespace Colors {
    const Color BLACK(0.0f, 0.0f, 0.0f);
    const Color WHITE(1.0f, 1.0f, 1.0f);
    const Color RED(1.0f, 0.0f, 0.0f);
    const Color GREEN(0.0f, 1.0f, 0.0f);
    const Color BLUE(0.0f, 0.0f, 1.0f);
    const Color YELLOW(1.0f, 1.0f, 0.0f);
    const Color GREY(0.5f, 0.5f, 0.5f);
}





#endif //RAYCASTER_COLOR_H
