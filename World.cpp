//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/20/22.
//

#include "Sphere.h"
#include "World.h"

World default_world() {
    World world;
    Sphere s1;
    s1.material.color = Color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;
    world.objects.emplace_back(std::make_unique<Sphere>(s1));
    Sphere s2;
    s2.set_transform(Transform::scale(0.5, 0.5, 0.5));
    world.objects.emplace_back(std::make_unique<Sphere>(s2));
    // world.add_object(s2);
    PointLight light {create_point(-10, 10, -10), Color(1, 1, 1)};
    world.lights.emplace_back(std::make_unique<PointLight>(light));
    return world;
}


