//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/25/22.
//

#ifndef RAYCASTER_CUBE_H
#define RAYCASTER_CUBE_H

#include "Shape.h"

struct Bounds {
    float t_min, t_max;
};

class Cube : public Shape {

public:
    Vector4f local_normal_at(const Vector4f& point) const override;
    std::vector<Intersection> local_intersect(const Ray& ray) const override;

    // Check axis
    Bounds check_axis(float origin, float direction) const;

};
#endif //RAYCASTER_CUBE_H
