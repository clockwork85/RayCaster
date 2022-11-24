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

class World {
public:
    // Empty world contains no objects or lights
    World() : objects(), lights() {}

//    std::vector<Shape> objects{};
    std::vector<std::shared_ptr<Shape>> objects{};
    std::vector<PointLight> lights{};

    template<class ShapeType>
    void add_object(const ShapeType& object) {
        objects.emplace_back(std::make_unique<ShapeType>(object));
    }

    void add_light(const PointLight& light) { lights.push_back(light); }
};

World default_world();


#endif //RAYCASTER_WORLD_H
