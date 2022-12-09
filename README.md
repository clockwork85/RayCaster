
# Assignment 5: Ray casting
## Building 

### Requirements
I built this in Clion with cmake. You will need to install cmake to build this project. 
I used the FetchContent module to pull in the dependencies. You will need to have cmake 3.14 or higher to build this project.
It relies on google test for unit testing, and Eigen as the linear algebra library.

## Explaining the Project

### Material.h

This is the class that contains the material information for the objects. It contains everything that is needed for the Phong shading model, as well as the reflection and refraction coefficients.  You can also provide a texture to the material, which will be procedurally generated and used to color the object.

    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    float reflective;
    float transparency;
    float refractive_index;
    std::shared_ptr<Pattern> pattern = nullptr;

### Pattern.h
This contains different types of patterns that can be used to procedurally generate textures for the shapes.  

### Canvas
This is the class that contains the canvas image data. It is a 1D array of Color objects that is referenced as a 2D array. It also contains the functions to write the image to a ppm file that can be viewed natively on a Mac in Preview.

### Ray.h
This is the class that contains the ray information. It contains the origin and direction of the ray, as well as a method to get the position give a t value. There is also a method to transform the Ray by a Transformation matrix.

### Shape.h

This is the base class for all the shapes. It contains the material information for the shape, as well as the transformation matrix. It also contains the virtual method for intersecting a ray with the shape that all the shapes inherit and must implement.

#### Shapes: Cube.h, Cylinder.h, Plane.h, Sphere.h, Triangle.h, SmoothTriangle.h

### Intersection.h

This is the class that contains the intersection information. It contains the t value, the object that was intersected, and the normal at the point of intersection. It also contains a method to transform the intersection by a Transformation matrix.

### Lights.h

This is the class that contains the light information. It contains the position of the light, the color of the light, and the intensity of the light. It also contains a method to transform the light by a Transformation matrix.

The lights that are implemented are the Area Light and Point Light.  The Area Light is an infinitely thin rectangular light that creates soft shadows as part of distributed ray tracing. The Point Light is a single point light that creates hard shadows.

### World.h

This is the class that contains the world information. It contains a vector of the shapes and the lights.  It also contains methods for creating the default world for testing and another for creating the famous Cornell Box scene. 

### Camera.h

This is the class that contains the camera information. It contains the field of view, the transformation matrix, and the half width and height of the view plane. It calculates the aspect ratio from the canvas width and height,. 

### MathUtils.h 

This class contains some convenience functions to wrap about the Eigen linear algebra library such as creating a point or vector. It also contains a function to compare floating point values for equality given an epsilon value.

### Mesh.h

This is just a container class for the vertices and faces of a mesh. It is used to load the mesh from an obj file.  It also iterates over Triangles to provide things such as setting materials or transforming the mesh.

### Pattern.h

This is the base class for all the patterns. It contains convenience functions to procedurally generate different patterns.

#### Patterns: Checkers, Gradient, Ring, Stripe

### Transform.h

This is a namespace that contains functions to create Transformation matrices.  It also contains a function to create a view transformation matrix.

``` 
namespace Transform {
Matrix4f identity();
Matrix4f translate(float x, float y, float z);
Matrix4f translate(const Vector4f& v);
Matrix4f rotate(float angle, float x, float y, float z);
Matrix4f rotate_x(float angle);
Matrix4f rotate_y(float angle);
Matrix4f rotate_z(float angle);
Matrix4f scale(float x, float y, float z);
Matrix4f scale(const Vector4f& v);
Matrix4f shear(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y);
Matrix4f view_transform(const Vector4f& from, const Vector4f& to, const Vector4f& up);
}
```

### RayTracer.h

This is the header that contains the ray tracer functions.  It contains the function to trace a ray, the function to shade a point, and the function to color a ray.  It also contains the function to render the world to a canvas. This is also where all of the distributed ray tracing features are implemented.

## RayTracer.cpp

### Soft Shadows

Soft shadows are implemented by casting multiple rays from the point of intersection to the light source.  The number of rays is determined by the number of samples in the light.  The color of the point is then averaged over the number of rays.  This is done in the shade_hit function.

```c++
Color shade_hit(const World& world, const Computation& comps, const int remaining) {
Color color = Colors::BLACK;
Color surface = Colors::BLACK;
for (const auto& light : world.lights) {
       auto intensity = 0.0f;
       try {
           const auto &point_light = dynamic_cast<const PointLight &>(*light);
           intensity = intensity_at_pointlight(point_light, comps.over_point, world);
           } catch (std::bad_cast& e) {
       try {
               auto &area_light = dynamic_cast<AreaLight &>(*light);
               intensity = intensity_at_arealight(area_light, comps.over_point, world);
           } catch (std::bad_cast& e) {
                std::cout << "Error: Light type not supported" << std::endl;
           }
        }
        surface =  lighting(comps.object->material, comps.object, *light, comps.over_point, comps.eyev, comps.normalv, intensity);

        const Color reflected = reflected_color(world, comps, remaining);
        const Color refracted = refracted_color(world, comps, remaining);

        if(comps.object->material.reflective > 0 && comps.object->material.transparency > 0) {
            const float reflectance = schlick(comps);
            color = color + surface + reflected * reflectance + refracted * (1 - reflectance);
        } else {
            color = color + surface + reflected + refracted;
        }
    }
    return color;
}
```
```c++
float intensity_at_arealight(const AreaLight& light, const Vector4f& point, const World& world) {
    float total_intensity = 0.0f;
    for (int v = 0; v < light.vsteps; v++) {
        for (int u = 0; u < light.usteps; u++) {
            const Vector4f p = point_on_light(light, u, v);
            if(!is_shadowed(world, p, point)) {
                total_intensity += 1.0f;
            }
        }
    }
    return total_intensity / static_cast<float>(light.samples);
}
```
```c++
Vector4f point_on_light(const AreaLight& light, const float u, const float v) {
    return light.corner + light.uvec * (u + light.jitter_by()) + light.vvec * (v + light.jitter_by());
}
```
```c++
class AreaLight : public Light {
public:
    AreaLight(const Vector4f &corner,
              const Vector4f &full_uvec,
              const unsigned int usteps,
              const Vector4f &full_vvec,
              const unsigned int vsteps,
              const Color &intensity) : Light(create_point(0, 0.9, -2), intensity),
                                        corner(corner),
                                        uvec(full_uvec / static_cast<float>(usteps)),
                                        usteps(usteps),
                                        vvec(full_vvec / static_cast<float>(vsteps)),
                                        vsteps(vsteps),
                                        samples(usteps * vsteps) {
    }

    const Vector4f corner;
    const Vector4f uvec;
    const unsigned int usteps;
    const Vector4f vvec;
    const unsigned int vsteps;
    const unsigned int samples;
    const LightType type = LightType::AREA;
    NumberGenerator *generator = nullptr;
    std::vector<Vector4f> positions;

    void set_jitter(NumberGenerator *generator) {
        this->generator = generator;
    }

    float jitter_by() const {
        if (generator == nullptr) {
            return 0.5f;
        }
        return generator->next();
    }
    void create_positions() {
        positions.clear();
        for (int i = 0; i < usteps; i++) {
            for (int j = 0; j < vsteps; j++) {
                Vector4f pt = corner + uvec * (i + 0.5f) + vvec * (j + 0.5f);
                positions.push_back(pt);
            }
        }
    }
};
```

### Anti-Aliasing

Anti-aliasing is implemented by casting multiple rays per pixel using different sampling techniques. The color of the pixel is then averaged over the number of rays.  

#### Monte Carlo Sampling (Random)

This is a technique that just randomly samples the pixel.  It is very easy to implement, but a lot of rays must be used to characterize the pixel color.   

```c++
Canvas render_aa(const Camera& camera, const World& world) {
    Canvas image = Canvas(camera.hsize, camera.vsize);
    const int samples = 10;
    RandomGenerator gen = RandomGenerator();
    for (int y = 0; y < camera.vsize; y++) {
        std::cerr << "\rScanlines remaining: " << camera.vsize - y <<  " " << std::flush;
        for (int x = 0; x < camera.hsize; x++) {
            Color color = Colors::BLACK;
            for (int i = 0; i < samples; i++) {
                const float x_offset = gen.next(); // value between 0 - 1
                const float y_offset = gen.next();
                Ray ray = ray_for_pixel(camera, x, y, x_offset, y_offset);
                color = color + color_at(world, ray, 4);
            }
            color = color / samples;
            image.write_pixel(x, y, color);
        }
    }
    return image;
}
```


#### Whitted Sampling with no jitter or recursion

This is a technique that samples the corners of a pixel and the center of a pixel.  More advanced techniques use the color difference here to determine to recurse or not.  

```c++
Canvas render_whitted_norecurs(const Camera& camera, const World& world) {
    Canvas image = Canvas(camera.hsize, camera.vsize);
    for (int y = 0; y < camera.vsize; y++) {
        std::cerr << "\rScanlines remaining: " << camera.vsize - y <<  " " << std::flush;
        for (int x = 0; x < camera.hsize; x++) {
            // 4 corners of pixel for antialiasing sum of 5 ray
            Color sum = Colors::BLACK;
            for (int i = 0; i < 5; i++) {
                const float px = x + 0.25f + 0.5f * (i % 2);
                const float py = y + 0.25f + 0.5f * (i / 2);
                Ray ray = ray_for_pixel(camera, px, py);
                Color color = color_at(world, ray, 4);
                sum = sum + color;
            }
            Color color = sum / 5.0f;
            image.write_pixel(x, y, color);
        }
    }
    return image;
}
```

#### Stratified Sampling (jittered)

This was the sampling that I found most useful.  I primary split the pixel into 9 sub-pixels and then jittered the rays within each sub-pixel.  The quality of the image is great using this technique, but shooting 9 rays can dramatically slow down the render.

```c++
Canvas render_stratified_jittering(const Camera& camera, const World& world, const bool multiprocessing) {
    Canvas image = Canvas(camera.hsize, camera.vsize);
    // Subdivide the pixel into subpixels
    const int subpixels = 9;
    const float subpixel_size = 1.0f / subpixels;
    const float subpixel_offset = subpixel_size / 2.0f;
    RandomGenerator gen = RandomGenerator();
//    std::cout << "Running on single processor" << std::endl;
    for (int y = 0; y < camera.vsize; y++) {
        std::cerr << "\rScanlines remaining: " << camera.vsize - y << " " << std::flush;
        for (int x = 0; x < camera.hsize; x++) {
            Color color = Colors::BLACK;
            for (int sub_y = 0; sub_y < subpixels; sub_y++) {
                for (int sub_x = 0; sub_x < subpixels; sub_x++) {
                    const float x_offset = (sub_x * subpixel_size) + subpixel_offset +
                                           gen.random_rng(-subpixel_offset, subpixel_offset);
                    const float y_offset = (sub_y * subpixel_size) + subpixel_offset +
                                           gen.random_rng(-subpixel_offset, subpixel_offset);
                    Ray ray = ray_for_pixel(camera, x, y, x_offset, y_offset);
                    color = color + color_at(world, ray, 4);
                }
            }
            color = color / (subpixels * subpixels);
            image.write_pixel(x, y, color);
        }
    }
    return image;
}
```
