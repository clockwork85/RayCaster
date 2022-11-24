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

    auto floor = Plane();
    floor.material.pattern = stripe_pattern(WHITE, BLACK);
    floor.material.pattern->set_transform(Transform::scale(3, 3, 3));
    floor.material.pattern->set_transform(Transform::rotate_y(-M_PI_2));

    auto middle = Sphere();
    middle.material.pattern = stripe_pattern(RED, GREEN);
    middle.material.pattern->set_transform(Transform::scale(0.25, 0.25, 0.25));
    middle.material.pattern->set_transform(Transform::rotate_y(M_PI / 4));
    middle.material.color = Color(0.1f, 1.0f, 0.5f);
    middle.material.diffuse = 0.7f;
    middle.material.specular = 0.3f;
    middle.set_transform(Transform::translate(-0.5f, 1.0f, 0.5f));

    auto right = Sphere();
    right.material.pattern = gradient_pattern(BLUE, BLACK);
    right.material.pattern->set_transform(Transform::scale(3, 3, 3));
    right.material.pattern->set_transform(Transform::rotate_y(-M_PI / 4));
    right.material.color = Color(0.5f, 1.0f, 0.1f);
    right.material.diffuse = 0.7f;
    right.material.specular = 0.3f;
    right.set_transform(Transform::translate(1.5f, 0.5f, -0.5f) * Transform::scale(0.5f, 0.5f, 0.5f));

    auto left = Sphere();
    left.material.pattern = ring_pattern(GREEN, BLUE);
    left.material.pattern->set_transform(Transform::scale(0.1, 0.1, 0.1));
    left.material.color = Color(1.0f, 0.8f, 0.1f);
    left.material.diffuse = 0.7f;
    left.material.specular = 0.3f;
    left.set_transform(Transform::translate(-1.5f, 0.33f, -0.75f) * Transform::scale(0.33f, 0.33f, 0.33f));

    World world;

    world.add_object(middle);
    world.add_object(right);
    world.add_object(left);
    world.add_object(floor);

    world.add_light(PointLight(create_point(-10.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f)));

    Camera camera(1000, 500, M_PI / 3.0f);
    camera.transform = Transform::view_transform(create_point(0.0f, 1.5f, -5.0f), create_point(0.0f, 1.0f, 0.0f), create_vector(0.0f, 1.0f, 0.0f));

    Canvas canvas = render(camera, world);
    canvas.save_to_file("testv.ppm");

    return 0;
}
