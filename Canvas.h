//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/11/22.
//

#ifndef RAYCASTER_CANVAS_H
#define RAYCASTER_CANVAS_H

#include "MathUtils.h"
#include <iostream>
#include <fstream>

class Color {
public:
    float r, g, b;
    Color(float r, float g, float b) : r(r), g(g), b(b) {}
    Color() : r(0.0f), g(0.0f), b(0.0f) {}
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
        return Color(r + rhs.r, g + rhs.g, b + rhs.b);
    }
    // Subtracting
    Color operator-(const Color& rhs) const {
        return Color(r - rhs.r, g - rhs.g, b - rhs.b);
    }
    // Multiplying by a scalar
    Color operator*(const float& scalar) const {
        return Color(r * scalar, g * scalar, b * scalar);
    }
    // Multiplication
    Color operator*(const Color& rhs) const {
        return Color(r * rhs.r, g * rhs.g, b * rhs.b);
    }
};

class Canvas {
public:
    int width, height;
    // smart pointer to a 2D array of colors
    std::unique_ptr<Color[]> pixels;

    // Declare Canvas
    Canvas(int width, int height) : width(width), height(height) {
        pixels = std::make_unique<Color[]>(width * height);
    }
    // Declare pixel_at
    Color pixel_at(int x, int y) const;

    // Declare write pixel
    void write_pixel(int x, int y, Color color);

    // Get a pixel from the canvas
    Color get_pixel(int x, int y) const;
    // Save the canvas to a PPM file
    // Declare canvas_to_ppm
    std::string canvas_to_ppm();
};

#endif //RAYCASTER_CANVAS_H
