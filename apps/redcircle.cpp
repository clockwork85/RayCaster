#include <iostream>

#include "Canvas.h"
#include "MathUtils.h"
#include "RayCaster.h"

using Vector = Eigen::Vector3f;

int main() {
    // Create a canvas
    Point ray_origin = Point(0.0f, 0.0f, -5.0f);
    float wall_z = 10.0f;
    float wall_size = 7.0f;
    int canvas_pixels = 1000;
    Canvas canvas(canvas_pixels, canvas_pixels);
    float pixel_size = wall_size / canvas_pixels;
    float half = wall_size / 2.0f;
    Color color = Color(1, 0, 0); // red
    Sphere sphere = Sphere();

    // For each row of pixels in the canvas
    for (int y = 0; y < canvas_pixels; y++) {
        // Compute the world y coordinate (top = +half, bottom = -half)
        float world_y = half - pixel_size * y;
        for (int x = 0; x < canvas_pixels; x++) {
            // Compute the world x coordinate (left = -half, right = half)
            float world_x = -half + pixel_size * x;
            // Describe the point on the wall that the ray will target
            Point position = Point(world_x, world_y, wall_z);
            // Create a ray from the origin to the wall point
            // Convert Point to Vector
            Vector ray_direction = (position - ray_origin).normalized();
            Ray r = Ray(ray_origin, ray_direction);
            // Compute the intersection between the ray and the sphere
            std::vector<Intersection> xs = intersect(&sphere, r);
            // If there was an intersection, color the pixel red
            if (xs.size() > 0) {
                canvas.write_pixel(x, y, color);
            }
        }
    }
    // Save the canvas to a PPM file
    canvas.save_to_file("ray_cast.ppm");
    return 0;
}
