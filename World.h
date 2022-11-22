//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/20/22.
//

#ifndef RAYCASTER_WORLD_H
#define RAYCASTER_WORLD_H

#include <vector>
#include "Lights.h"
#include "Sphere.h"

class World {
public:
    // Empty world contains no objects or lights
    World() : objects(), lights() {}

    std::vector<Sphere> objects{};
    std::vector<PointLight> lights{};

    void add_object(const Sphere& object) { objects.push_back(object); }
    void add_light(const PointLight& light) { lights.push_back(light); }
};

World default_world();


#endif //RAYCASTER_WORLD_H
