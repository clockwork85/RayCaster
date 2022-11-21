//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/20/22.
//

#ifndef RAYCASTER_CAMERA_H
#define RAYCASTER_CAMERA_H

#include <Eigen/Core>
#include <Eigen/Geometry>
#include "Transform.h"
#include "MathUtils.h"

using Vector3f = Eigen::Vector3f;
using Vector4f = Eigen::Vector4f;
using Matrix4f = Eigen::Matrix4f;

class Camera {
public:
    Camera() : hsize(0), vsize(0), field_of_view(0), transform(Matrix4f::Identity()) { set_pixel_size(); }
    Camera(int hsize, int vsize, float field_of_view) : hsize(hsize), vsize(vsize), field_of_view(field_of_view), transform(Matrix4f::Identity()) { set_pixel_size(); }

    int hsize;
    int vsize;
    float field_of_view;
    Matrix4f transform;
    float half_view = tan(field_of_view / 2);
    float aspect = static_cast<float>(hsize) / static_cast<float>(vsize);
    float half_width;
    float half_height;
    float pixel_size;

    void set_pixel_size() {
        if (aspect >= 1) {
            half_width = half_view;
            half_height = half_view / aspect;
        } else {
            half_width = half_view * aspect;
            half_height = half_view;
        }
        pixel_size = (half_width * 2) / hsize;
    }


    // Equality
    bool operator==(const Camera& rhs) const {
        return (hsize == rhs.hsize && vsize == rhs.vsize && is_equal(field_of_view, rhs.field_of_view) &&
                transform == rhs.transform);
    }
};

#endif //RAYCASTER_CAMERA_H
