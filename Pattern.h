//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/24/22.
//

#ifndef RAYCASTER_PATTERN_H
#define RAYCASTER_PATTERN_H

#include "Color.h"

struct Pattern {
    Pattern(const Color a, const Color b) : a(a), b(b) {}

    Color stripe_at(const Vector4f& point) const {
        if((static_cast<int>(floor(point.x())) % 2) == 0) {
            return a;
        } else {
            return b;
        }
    }

    const Color a;
    const Color b;
};

inline std::shared_ptr<Pattern> stripe_pattern(const Color a, const Color b) {
    return std::make_shared<Pattern>(a, b);
}

#endif //RAYCASTER_PATTERN_H
