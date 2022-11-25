#include <iostream>

#include "Canvas.h"
#include "Color.h"
#include "MathUtils.h"
#include "Plane.h"
#include "Patterns.h"
#include "RayCaster.h"
#include "Sphere.h"
#include "Lights.h"

using Vector3f = Eigen::Vector3f;
using Vector4f = Eigen::Vector4f;
using Matrix4f = Eigen::Matrix4f;

int main() {

    int height = 500;
    int width = 250;

    auto floor = Plane();
//    floor.material.color = Color(1, 0.9, 0.9);
    floor.material.pattern = checker_pattern(Colors::WHITE, Colors::BLACK);
    floor.material.pattern->set_transform(Transform::scale(1, 1, 1));
    floor.material.pattern->set_transform(Transform::rotate_y(-M_PI_2));
    floor.material.reflective = 0.5;

    auto middle = Sphere();
    middle.material.pattern = stripe_pattern(Colors::RED, Colors::GREEN);
    middle.material.pattern->set_transform(Transform::scale(0.25, 0.25, 0.25));
    middle.material.pattern->set_transform(Transform::rotate_y(M_PI / 4));
    middle.material.color = Color(0.1f, 1.0f, 0.5f);
    middle.material.diffuse = 0.7f;
    middle.material.specular = 0.3f;
    middle.material.reflective = 0.1;
    middle.set_transform(Transform::translate(-0.5f, 1.0f, 0.5f));

    auto right = Sphere();
    right.material.pattern = gradient_pattern(Colors::BLUE, Colors::BLACK);
    right.material.pattern->set_transform(Transform::scale(3, 3, 3));
    right.material.pattern->set_transform(Transform::rotate_y(-M_PI / 4));
    right.material.color = Color(0.5f, 1.0f, 0.1f);
    right.material.diffuse = 0.7f;
    right.material.specular = 0.3f;
    right.material.reflective = 0.75;
    right.material.transparency = 0.75;
    right.material.refractive_index = 1.5;
    right.set_transform(Transform::translate(1.5f, 0.5f, -0.5f) * Transform::scale(0.5f, 0.5f, 0.5f));

    auto left = Sphere();
//    left.material.pattern = ring_pattern(GREEN, BLUE);
//    left.material.pattern->set_transform(Transform::scale(0.2, 0.2, 0.2));
//    left.material.color = Color(0.1647f, 0.0039f, 0.2039f);
//    left.material.diffuse = 0.7f;
//    left.material.specular = 0.9f;
//    left.material.reflective = 0.5;
    left.set_transform(Transform::translate(-1.5f, 0.33f, -0.75f) * Transform::scale(0.33f, 0.33f, 0.33f));
    left.set_material(glass());
    left.material.transparency = 0.1;
    left.material.reflective = 1.0;
    World world;

    world.add_object(middle);
    world.add_object(right);
    world.add_object(left);
    world.add_object(floor);

    world.add_light(PointLight(create_point(-10.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f)));

    Camera camera(height, width, M_PI / 3.0f);
    camera.transform = Transform::view_transform(create_point(0.0f, 1.5f, -5.0f), create_point(0.0f, 1.0f, 0.0f), create_vector(0.0f, 1.0f, 0.0f));

    Canvas canvas = render(camera, world);
    canvas.save_to_file("test.ppm");

    return 0;
}
