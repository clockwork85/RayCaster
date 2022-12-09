//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/20/22.
//

#ifndef RAYCASTER_WORLD_H
#define RAYCASTER_WORLD_H

#include <memory>
#include <vector>
#include "Lights.h"
#include "Shape.h"
#include "Transform.h"
#include "Patterns.h"
#include "Sphere.h"
#include "Plane.h"
#include "Cube.h"


// For reference to understand push_back and emplace_back
// https://stackoverflow.com/questions/4303513/push-back-vs-emplace-back

class World {
public:
//    std::vector<Shape> objects{};
    std::vector<std::unique_ptr<Shape>> objects{};
    std::vector<std::unique_ptr<Light>> lights{};

    template<class ShapeType>
    void add_object(const ShapeType& object) {
        objects.emplace_back(std::make_unique<ShapeType>(object));
    }

    template<class LightType>
    void add_light(const LightType& light) {
        lights.emplace_back(std::make_unique<LightType>(light));
    }
};

World default_world();
World cornell_box();


#endif //RAYCASTER_WORLD_H
