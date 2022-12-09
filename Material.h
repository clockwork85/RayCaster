//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/19/22.
//

#ifndef RAYCASTER_MATERIAL_H
#define RAYCASTER_MATERIAL_H

#include "Color.h"
#include "Pattern.h"

class Material {
public:
    Material() : color(Color(1, 1, 1)),
                ambient(0.1), diffuse(0.9), specular(0.9), shininess(200.0),
                reflective(0.0), transparency(0.0), refractive_index(1.0),
                pattern(nullptr) {};
    Material(const Color& color, float ambient, float diffuse, float specular, float shininess, float reflective, float transparency, float refractive_index, std::shared_ptr<Pattern> pattern) :
            color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), reflective(reflective), transparency(transparency), refractive_index(refractive_index), pattern(nullptr) {};

    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    float reflective;
    float transparency;
    float refractive_index;
    std::shared_ptr<Pattern> pattern = nullptr;

    // Equality
    bool operator==(const Material& rhs) const {
        return (color == rhs.color && is_equal(ambient, rhs.ambient) && is_equal(diffuse, rhs.diffuse) && is_equal(specular, rhs.specular) && is_equal(shininess, rhs.shininess));
    }
};

// Glass material
//inline Material glass() {
//    return Material(Color(1.0, 1.0, 1.0), 0.0, 0.5, 0.5, 200.0, 0.0, 1.0, 1.5, nullptr);
//}

const Material glass
        {
                Colors::BLACK,  // color
                0,      // ambient
                0,      // diffuse
                1,      // specular
                300,    // shininess
                0.9,    // reflective
                1,      // transparency
                1.5,     // refractive index
                nullptr // pattern
        };

#endif //RAYCASTER_MATERIAL_H
