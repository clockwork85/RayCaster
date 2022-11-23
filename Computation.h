//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/23/22.
//

#ifndef RAYCASTER_COMPUTATION_H
#define RAYCASTER_COMPUTATION_H

#include <Eigen/Core>
#include "MathUtils.h"
#include "Sphere.h"

using Vector4f = Eigen::Vector4f;

struct Computation {
        float t{-1 };
        const Sphere* object{nullptr};
        Vector4f point{0, 0, 0, 1};
        Vector4f eyev{0, 0, 0, 0};
        Vector4f normalv{0, 0, 0, 0};
        bool inside{false};
        Vector4f over_point{point + normalv * EPSILON};
};

#endif //RAYCASTER_COMPUTATION_H
