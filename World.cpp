//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/20/22.
//

#include "Cube.h"
#include "Plane.h"
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

// https://github.com/tobiasmarciszko/qt_raytracer_challenge/blob/master/raytracer/main/worlds.h
World cornell_box() {

    Plane left_wall;
    Plane right_wall;
    Plane back_wall;
    Plane floor;
    Plane ceiling;

    Cube cube;
    Sphere sphere;
    sphere.set_material(glass);
    Sphere sphere2;
    sphere2.material.reflective = 1.0;

    Material wall_material;
    wall_material.ambient = 0.2;
    wall_material.specular = 0.0;
    wall_material.diffuse = 0.5;

    left_wall.set_material(wall_material);
    right_wall.set_material(wall_material);
    back_wall.set_material(wall_material);
    floor.set_material(wall_material);
    ceiling.set_material(wall_material);
    cube.set_material(wall_material);

    left_wall.material.color = Color(1.0, 0.0, 0.0);
    right_wall.material.color = Color(0.0, 1.0, 0.0);
    back_wall.material.color = Color(1.0, 1.0, 1.0);
    floor.material.color = Color(1.0, 1.0, 1.0);
    ceiling.material.color = Color(1.0, 1.0, 1.0);

    left_wall.set_transform(Transform::translate(-1, 0, 0) * Transform::rotate_z(M_PI_2));
    right_wall.set_transform(Transform::translate(1, 0, 0) * Transform::rotate_z(-M_PI_2));
    back_wall.set_transform(Transform::translate(0, 0, 1) * Transform::rotate_x(M_PI_2));
    floor.set_transform(Transform::translate(0, -1, 0));
    ceiling.set_transform(Transform::translate(0, 1, 0) * Transform::rotate_z(M_PI));
    cube.set_transform(Transform::translate(0.0, -0.5, -1.0) * Transform::scale(0.25, 0.5, 0.25) * Transform::rotate_y(M_PI / 3));
//    cube.set_transform(Transform::translate(-0.3, -0.5, -1.0) * Transform::scale(0.25, 0.5, 0.25) * Transform::rotate_y(M_PI / 3));
//    sphere.set_transform(Transform::translate(0.6, -0.75, -2.5) * Transform::scale(0.25, 0.25, 0.25));
//    sphere2.set_transform(Transform::translate(-0.6, -0.75, -2.5) * Transform::scale(0.25, 0.25, 0.25));


    const auto pointLight = PointLight(create_point(0.0, 0.8, -2), Color(1.0, 1.0, 1.0));
//    const auto areaLight = AreaLight{create_point(-0.1, 0.9, -2.1), create_vector(0.25, 0, 0), 8, create_vector(0, 0, 0.25), 8, Color{1.0, 1.0, 1.0}};

    World world;
    world.add_light(pointLight);

    world.add_object(left_wall);
    world.add_object(right_wall);
    world.add_object(back_wall);
    world.add_object(floor);
    world.add_object(ceiling);
    world.add_object(cube);
//    world.add_object(sphere);
//    world.add_object(sphere2);

    return world;
}
