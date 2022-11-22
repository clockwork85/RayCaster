#include <iostream>

#include "Canvas.h"
#include "Color.h"
#include "Lights.h"
#include "MathUtils.h"
#include "RayCaster.h"
#include "Sphere.h"

using Vector3f = Eigen::Vector3f;
using Vector4f = Eigen::Vector4f;
using Matrix4f = Eigen::Matrix4f;

// Comment
int main() {
  Sphere floor = Sphere();
  floor.material.color = Color(1.0f, 0.9f, 0.9f);
  floor.material.specular = 0.0f;
  floor.transform(Transform::scale(10.0f, 0.01f, 10.0f));

  Sphere left_wall = Sphere();
  left_wall.material = floor.material;
  left_wall.transform(Transform::translate(0.0f, 0.0f, 5.0f) *
                      Transform::rotate_y(-M_PI / 4.0f) *
                      Transform::rotate_x(M_PI / 2.0f) *
                      Transform::scale(10.0f, 0.01f, 10.0f));

  Sphere right_wall = Sphere();
  right_wall.material = floor.material;
  right_wall.transform(Transform::translate(0.0f, 0.0f, 5.0f) *
                       Transform::rotate_y(M_PI / 4.0f) *
                       Transform::rotate_x(M_PI / 2.0f) *
                       Transform::scale(10.0f, 0.01f, 10.0f));

  Sphere middle = Sphere();
  middle.material.color = Color(0.1f, 1.0f, 0.5f);
  middle.material.diffuse = 0.7f;
  middle.material.specular = 0.3f;
  middle.transform(Transform::translate(-0.5f, 1.0f, 0.5f));

  Sphere right = Sphere();
  right.material.color = Color(0.5f, 1.0f, 0.1f);
  right.material.diffuse = 0.7f;
  right.material.specular = 0.3f;
  right.transform(Transform::translate(1.5f, 0.5f, -0.5f) *
                  Transform::scale(0.5f, 0.5f, 0.5f));

  Sphere left = Sphere();
  left.material.color = Color(1.0f, 0.8f, 0.1f);
  left.material.diffuse = 0.7f;
  left.material.specular = 0.3f;
  left.transform(Transform::translate(-1.5f, 0.33f, -0.75f) *
                 Transform::scale(0.33f, 0.33f, 0.33f));

  World world;
  world.add_object(floor);
  world.add_object(left_wall);
  world.add_object(right_wall);
  world.add_object(middle);
  world.add_object(right);
  world.add_object(left);
  world.add_light(
      PointLight(create_point(-10.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f)));
  std::cout << "World lights size: " << world.lights.size() << std::endl;

  Camera camera(1000, 500, M_PI / 3.0f);
  camera.transform = Transform::view_transform(create_point(0.0f, 1.5f, -5.0f),
                                               create_point(0.0f, 1.0f, 0.0f),
                                               create_vector(0.0f, 1.0f, 0.0f));

  Canvas canvas = render(camera, world);
  canvas.save_to_file("test.ppm");

  return 0;
}
