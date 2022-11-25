//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/19/22.
//

#ifndef RAYCASTER_MATERIAL_H
#define RAYCASTER_MATERIAL_H

#include "Color.h"
#include "Pattern.h"

class Material {
public:
    Material() : color(Color(1, 1, 1)), ambient(0.1), diffuse(0.9), specular(0.9), shininess(200.0), reflective(0.0), pattern(nullptr) {};

    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    float reflective;
    std::shared_ptr<Pattern> pattern = nullptr;

    // Equality
    bool operator==(const Material& rhs) const {
        return (color == rhs.color && is_equal(ambient, rhs.ambient) && is_equal(diffuse, rhs.diffuse) && is_equal(specular, rhs.specular) && is_equal(shininess, rhs.shininess));
    }
};

#endif //RAYCASTER_MATERIAL_H
