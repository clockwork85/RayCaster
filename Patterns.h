//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/24/22.
//

#ifndef RAYCASTER_PATTERNS_H
#define RAYCASTER_PATTERNS_H

#include "MathUtils.h"
#include "Pattern.h"

class StripedPattern : public Pattern {
public:
    StripedPattern(const Color& a, const Color& b) : a(a), b(b) {}

    Color pattern_at(const Vector4f& point) const override {
        if((static_cast<int>(floor(point.x())) % 2) == 0) {
            return a;
        } else {
            return b;
        }
    }

    Color a, b;
};

inline std::shared_ptr<Pattern> stripe_pattern(const Color& a, const Color& b) {
    return std::make_shared<StripedPattern>(a, b);
}

class GradientPattern : public Pattern {
public:
    GradientPattern(const Color& a, const Color& b) : a(a), b(b) {}

    Color pattern_at(const Vector4f& point) const override {
        auto distance = b - a;
        auto fraction = point.x() - floor(point.x());
        return a + distance * fraction;
    }
    Color a, b;
};

inline std::shared_ptr<Pattern> gradient_pattern(const Color& a, const Color& b) {
    return std::make_shared<GradientPattern>(a, b);
}

class RingPattern : public Pattern {
public:
    RingPattern(const Color& a, const Color& b) : a(a), b(b) {}

    Color pattern_at(const Vector4f& point) const override {
        float distance = sqrt(point.x() * point.x() + point.z() * point.z());
        if(is_equal((int)floor(distance) % 2, 0)) {
            return a;
        } else {
            return b;
        }
    }
    Color a, b;
};

inline std::shared_ptr<Pattern> ring_pattern(const Color& a, const Color& b) {
    return std::make_shared<RingPattern>(a, b);
}

class CheckerPattern : public Pattern {
public:
    CheckerPattern(const Color& a, const Color& b) : a(a), b(b) {}

    Color pattern_at(const Vector4f& point) const override {
        if(((int)floor(point[0]) + (int)floor(point[1]) + (int)floor(point[2])) % 2 == 0) {
            return a;
        } else {
            return b;
        }
    }
    Color a, b;
};

inline std::shared_ptr<Pattern> checker_pattern(const Color& a, const Color& b) {
    return std::make_shared<CheckerPattern>(a, b);
}


#endif //RAYCASTER_PATTERNS_H
