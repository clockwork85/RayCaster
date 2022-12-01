//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/11/22.
//

#include "Canvas.h"

// Get the color at a given pixel
Color Canvas::pixel_at(int x, int y) const {
    return pixels[y * width + x];
}

// Write a pixel to the canvas
void Canvas::write_pixel(int x, int y, Color color) {
    pixels[y * width + x] = color;
}

    // Get a pixel from the canvas
Color Canvas::get_pixel(int x, int y) const {
    return pixels[y * width + x];
}

std::string Canvas::canvas_to_ppm() {
    // Build the header
    std::string header = "P3\n" + std::to_string(width) + " " + std::to_string(height) + "\n255\n";
    // Keep track of the current line length
    int line_length = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Color color = get_pixel(x, y);
            // std::cout << "Final color from get_pixel is: " << color << " at " << x << ", " << y << std::endl;
            // Colors are stored as ints between 0 and 255
            // Negative numbers are clamped to 0
            // Numbers greater than 255 are clamped to 255
            // Round to the nearest higher integer
//            std::cout << "Color.r: " << color.r << std::endl;
//            std::cout << "Color.g: " << color.g << std::endl;
//            std::cout << "Color.b: " << color.b << std::endl;

            int r = (int) round(color.r * 255);
            int g = (int) round(color.g * 255);
            int b = (int) round(color.b * 255);
            if (r < 0) r = 0;
            if (r > 255) r = 255;
            if (g < 0) g = 0;
            if (g > 255) g = 255;
            if (b < 0) b = 0;
            if (b > 255) b = 255;
            // Check if adding the next red color value will exceed 70 characters
            // If so, start a new line
            if (line_length + std::to_string(r).length() > 70) {
                header.pop_back();
                header += "\n";
                line_length = 0;
            }
            // Add the red color value
            header += std::to_string(r) + " ";
            line_length += std::to_string(r).length() + 1;
            // Check if adding the next green color value will exceed 70 characters
            // If so, start a new line
            if (line_length + std::to_string(g).length() > 70) {
                header.pop_back();
                header += "\n";
                line_length = 0;
            }
            // Add the green color value
            header += std::to_string(g) + " ";
            line_length += std::to_string(g).length() + 1;
            // Check if adding the next blue color value will exceed 70 characters
            // If so, start a new line
            if (line_length + std::to_string(b).length() > 70) {
                header.pop_back();
                header += "\n";
                line_length = 0;
            }
            // Add the blue color value
            header += std::to_string(b) + " ";
            line_length += std::to_string(b).length() + 1;
        }
        // Chop off the trailing space
        header.pop_back();
        // Add a newline to the header string
        header += "\n";
        // Reset the line length
        line_length = 0;
    }
    return header;
}

// Write the canvas to a ppm file
void Canvas::save_to_file(std::string filename) {
    std::ofstream ppm_file;
    ppm_file.open(filename);
    ppm_file << canvas_to_ppm();
    ppm_file.close();
}