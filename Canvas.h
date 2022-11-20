//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/11/22.
//

#ifndef RAYCASTER_CANVAS_H
#define RAYCASTER_CANVAS_H

#include "Color.h"
#include "MathUtils.h"
#include <iostream>
#include <fstream>



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
    void save_to_file(std::string filename);
};

#endif //RAYCASTER_CANVAS_H
