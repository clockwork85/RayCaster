//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/26/22.
//

#include "Lights.h"


float PointLight::intensity_at(const Vector4f& point, const World& world) const {
    const bool in_shadow = is_shadowed(world, position(), point);
    if (in_shadow) {
        return 0.0f;
    }
    return 1.0f;
}
