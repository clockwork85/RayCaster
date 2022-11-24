//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/24/22.
//

#ifndef RAYCASTER_PATTERN_H
#define RAYCASTER_PATTERN_H

#include "Color.h"

using Matrix4f = Eigen::Matrix4f;

struct Pattern {
    virtual ~Pattern() = default;
//    Pattern(const Color a, const Color b) : a(a), b(b) {}

//    Color stripe_at(const Vector4f& point) const {
//        if((static_cast<int>(floor(point.x())) % 2) == 0) {
//            return a;
//        } else {
//            return b;
//        }
//    }
    virtual Color pattern_at(const Vector4f& point) const = 0;


    Matrix4f matrix() const {
        return m_transform;
    }

    Matrix4f inverse() const {
        return m_inverse;
    }

    inline void set_transform(const Matrix4f& transform) {
        m_transform = m_transform * transform;
        m_inverse = m_transform.inverse();
    }

private:
    Matrix4f m_transform = Matrix4f::Identity();
    Matrix4f m_inverse = m_transform.inverse();
};

#endif //RAYCASTER_PATTERN_H
