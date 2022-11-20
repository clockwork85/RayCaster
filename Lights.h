//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/19/22.
//

#ifndef RAYCASTER_LIGHTS_H
#define RAYCASTER_LIGHTS_H

#include <Eigen/Core>
#include "Color.h"
#include "MathUtils.h"

using Vector3f = Eigen::Vector3f;

class PointLight {
public:
    PointLight() : m_position(create_point(0.0f, 0.0f, 0.0f)), m_intensity(Color(1.0f, 1.0f, 1.0f)) {}
    PointLight(const Vector4f& position, const Color& intensity) : m_position(position), m_intensity(intensity) {}
    PointLight(const PointLight& other) : m_position(other.m_position), m_intensity(other.m_intensity) {}

    const Vector4f& position() const { return m_position; };
    const Color& intensity() const { return m_intensity; };

    // Equality
    bool operator==(const PointLight& rhs) const {
        return (m_position == rhs.m_position && m_intensity == rhs.m_intensity);
    }

private:
    Eigen::Vector4f m_position;
    Color m_intensity;
};


#endif //RAYCASTER_LIGHTS_H
