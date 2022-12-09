//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/23/22.
//

#ifndef RAYCASTER_INTERSECTION_H
#define RAYCASTER_INTERSECTION_H

#include "MathUtils.h"
#include "Shape.h"

struct Shape;

struct Intersection {
    Intersection() : t(-1), object(nullptr) {}
    Intersection(float _t, const Shape* _object) : t(_t), object(_object) {}
    Intersection(float _t, const Shape* _object, const float u, const float v) : t(_t), object(_object), u(u), v(v) {}

    inline bool operator==(const Intersection& other) const {
        if (!(is_equal(t, other.t))) {
            return false;
        }
        return object == other.object;
    }

    float t;
    float u, v;
    const Shape* object;
};
#endif //RAYCASTER_INTERSECTION_H
