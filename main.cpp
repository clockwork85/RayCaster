#include <iostream>

#include "Canvas.h"
#include "Cylinder.h"
#include "Cube.h"
#include "Color.h"
#include "MathUtils.h"
#include "Mesh.h"
#include "MeshSmooth.h"
#include "Plane.h"
#include "Patterns.h"
#include "RayCaster.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Lights.h"

using Vector4f = Eigen::Vector4f;
using Matrix4f = Eigen::Matrix4f;

float random_float() {
    // random float from 0 to 1
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

//float random_float_negative_10_to_10() {
//    return random_float() * 20 - 10;
//}
//
//float random_float_negative_5_to_5() {
//    return random_float() * 10 - 5;
//}
//
//float random_float_1_5() {
//    return random_float() * 4 + 1;
//}
//
//float random_float_1_10() {
//    return random_float() * 9 + 1;
//}
//
//float random_float_negative_1_to_negative_10() {
//    return random_float() * 9 - 10;
//}
//
//float random_float_between_point_5_and_1() {
//    return random_float() * 0.5 + 0.5;
//}

int main() {

    int height = 1000;
    int width = 500;

//    auto floor = Plane();
//    floor.material.color = Color(1, 0.9, 0.9);
//    floor.material.pattern = checker_pattern(Colors::BLACK, Colors::WHITE);
//    floor.material.pattern->set_transform(Transform::scale(1, 1, 1));
//    floor.material.pattern->set_transform(Transform::rotate_y(-M_PI_4));
//    floor.material.color = Color(1, 0.9, 0.9);
//    floor.material.reflective = 0.2;
//    floor.material.refractive_index = 1.7;
//    floor.material.transparency = 0.25;
//
////     auto middle = Sphere();
//    auto middle = Cube();
//    middle.material.pattern = stripe_pattern(Colors::RED, Colors::GREEN);
//    middle.material.pattern->set_transform(Transform::scale(0.25, 0.25, 0.25));
//    middle.material.pattern->set_transform(Transform::rotate_y(M_PI / 4));
//    middle.material.color = Color(0.1f, 1.0f, 0.5f);
//    middle.material.diffuse = 0.7f;
//    middle.material.specular = 0.3f;
//    middle.material.reflective = 0.1;
//    middle.material.transparency = 0.0;
//    middle.material.shininess = 1000;
//    middle.set_transform(Transform::translate(0.0f, 1.0f, 1.0f) * Transform::rotate_y(M_PI / 6));
//
//    auto right = Sphere();
//    right.material.pattern = gradient_pattern(Colors::BLUE, Colors::BLACK);
////    right.material.pattern->set_transform(Transform::scale(3, 3, 3));
////   right.material.pattern->set_transform(Transform::rotate_y(-M_PI / 3));
//// Dark blue color
//    right.material.color = Color(0.0f, 0.2f, 0.9f);
////    right.material.color = Color(0.5f, 1.0f, 0.1f);
//    right.material.diffuse = 0.7f;
//    right.material.specular = 0.3f;
//    right.material.reflective = 0.75;
//
////    right.material.transparency = 0.75;
////    right.material.refractive_index = 1.5;
////    right.set_transform(Transform::translate(1.5f, 0.5f, -1.0f) * Transform::scale(0.5f, 0.5f, 0.5f) );
//    right.set_transform(Transform::translate(1.5f, 0.5f, -1.0f) *
//                        Transform::scale(0.6f, 0.6f, 0.6f) *
//                        Transform::rotate_y(M_PI / 4));
//
//    auto left = Cylinder();
//    //auto left = Cube();
////   left.material.pattern = ring_pattern(Colors::YELLOW, Colors::WHITE);
////   left.material.pattern->set_transform(Transform::scale(0.2, 0.2, 0.2));
//   left.material.color = Color(0.1647f, 0.0039f, 0.2039f); // dark purple
//    left.closed = true;
//    left.minimum = 0;
//    left.maximum = 1;
//
////    left.material.reflective = 0.5;
//
//    left.set_transform(Transform::translate(-1.7f, 0.0f, -0.5f) * Transform::scale(0.5f, 1.3f, 0.5f)); //  * Transform::rotate_x(-M_PI / 64.0f));
//    left.material.diffuse = 0.7f;
//    left.material.specular = 0.3f;
//    left.material.ambient = 0.1f;
////     left.material.transparency = 0.7;
////    left.material.color = Color(0.1647f, 0.0039f, 0.2039f); // dark purple
////    left.material.reflective = 0.05;
////    left.material.refractive_index = 2.2;
////    left.material.shininess = 500;
////    Sphere large_sphere;
////    large_sphere.set_transform(Transform::translate(1.0f, 1.0f, 1.0f) * Transform::rotate_y(M_PI / 6));
////    large_sphere.material.color = Color(0.1f, 0.1f, 0.8f);
    Mesh mesh;
    mesh.load_mesh("bunny_n.obj");
//    mesh.set_transform(Transform::translate(0.0f, -0.37f, 1.5f) * Transform::scale(15.0f, 15.0f, 15.0f));
    mesh.set_transform(Transform::translate(-0.1f, -1.20f, -2.55f) * Transform::scale(7.0f, 7.0f, 7.0f) * Transform::rotate_y(M_PI));

    Material m = Material();
//    m.color = Color(0.9961, 0.0039, 0.6039);
    // Color is opaque white
    m.color = Color(0.99, 0.99, 0.99);
    m.ambient = 0.1;
    m.diffuse = 0.9;
    m.specular = 0.9;
    m.reflective = 0.05;
    mesh.set_material(m);
//    World world;
////    for(int i = 0; i <= 20; i++) {
////        // Create a new sphere
////        auto sphere = Sphere();
////        // random color for the sphere
////        sphere.material.color = Color(random_float(), random_float(), random_float());
////        sphere.material.reflective = random_float();
////        sphere.material.transparency = random_float();
////        sphere.material.refractive_index = random_float() * 2;
////        sphere.material.diffuse = random_float();
////        sphere.material.specular = random_float();
////        // random position for the sphere
////        float radius = random_float_between_point_5_and_1();
////        sphere.set_transform(Transform::translate(random_float_negative_5_to_5(),
////                                                  random_float_1_5(),
////                                                  random_float_1_10()) * Transform::scale(radius, radius, radius));
////        //sphere.set_transform(Transform::scale(radius, radius, radius));
////        // add the sphere to the world
////        world.add_object(sphere);
////    }
//
//    float intensity = 1.0;
//    world.add_object(middle);
//    world.add_object(right);
//    world.add_object(left);
////     world.add_object(large_sphere);
////     time load bunny
////     start time
////    auto start = std::chrono::high_resolution_clock::now();
////    for(auto &triangle : mesh.triangles) {
////        world.add_object(triangle);
////    }
////    // end time
////    auto finish = std::chrono::high_resolution_clock::now();
////    std::chrono::duration<double> elapsed = finish - start;
////    std::cout << "Time to load bunny: " << elapsed.count() << " s\n";
//    world.add_object(floor);
//    std::cout << "World has " << world.objects.size() << " objects" << std::endl;
//    PointLight light = PointLight(create_point(-10.0f, 10.0f, -10.0f), Color(intensity, intensity, intensity));
////    world.add_light(light);
////    auto area = AreaLight(create_point(8.0f, 5.0f, -5.f), create_vector(1, 0, 0), 2, create_vector(0, 0, 1), 2, Color(1, 1, 1));
////    RandomGenerator rand;
////    area.set_jitter(&rand);
////    PointLight area = PointLight(create_point(8.0f, 5.0f, -5.f), Color(1, 1, 1));
//    //  PointLight light2 = PointLight(create_point(10.0f, 100.f, -10.f), Color(intensity, intensity, intensity));
//    world.add_light(light);
//    std::cout << "World has " << world.lights.size() << " lights" << std::endl;
//    std::cout << "World light type: " << world.lights[0]->type << std::endl;

    Camera camera(height, width, M_PI / 3.0f);
    camera.transform = Transform::view_transform(create_point(0.0f, 0.0f, -7.0f), create_point(0.0f, 0.05f, 0.0f), create_vector(0.0f, 1.0f, 0.0f));
//    camera.transform = Transform::view_transform(create_point(0.0f, 1.5f, -7.0f), create_point(0.0f, 1.0f, 0.0f), create_vector(0.0f, 1.0f, 0.0f));
//
////    Canvas canvas = render_stratified_jittering(camera, world);

    World cornell = cornell_box();
    for(auto& tri: mesh.triangles) {
        cornell.add_object(tri);
    }
//    const auto pointLight2 = PointLight(create_point(0.0, 1.0, 3.0), Color(0.2, 0.2, 0.2));
//    cornell.add_light(pointLight2);
//    Canvas canvas = render_stratified_jittering(camera, cornell);
    // Time render
    auto start = std::chrono::high_resolution_clock::now();
//    Canvas canvas = render(camera, cornell);
    Canvas canvas = render_stratified_jittering(camera, cornell);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Time to render: " << elapsed.count() << " s\n";
    canvas.save_to_file("bunny_hr_al_sj_500.ppm");

    return 0;
}
