//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/20/22.
//

#include "World.h"

World default_world() {
    World world;
    Sphere s1 = Sphere();
    s1.material.color = Color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;
    world.add_object(s1);
    Sphere s2 = Sphere();
    Matrix4f scale = Transform::scale(0.5, 0.5, 0.5);
    s2.transform(scale);
    world.add_object(s2);
    world.add_light(PointLight(create_point(-10, 10, -10), Color(1, 1, 1)));
    return world;

}