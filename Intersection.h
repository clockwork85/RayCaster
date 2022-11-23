//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/23/22.
//

#ifndef RAYCASTER_INTERSECTION_H
#define RAYCASTER_INTERSECTION_H

#include "MathUtils.h"
#include "Sphere.h"

struct Intersection {
    Intersection() = delete;
    Intersection(float _t, const Sphere* _object) : t(_t), object(_object) {}

    inline bool operator==(const Intersection& other) const {
        if (!(is_equal(t, other.t))) {
            return false;
        }
        return object == other.object;
    }

    float t;
    const Sphere* object;
};
#endif //RAYCASTER_INTERSECTION_H
