
# Assignment 5: Ray casting
## Building 

### Requirements
I built this in Clion with cmake. You will need to install cmake to build this project. 
I used the FetchContent module to pull in the dependencies. You will need to have cmake 3.14 or higher to build this project.
It relies on google test for unit testing, and Eigen as the linear algebra library.

## Explaining the Project

Most of the important functions of the project are in the RayCaster.cpp file.

The two types of lights I use for the project are the Point Light and Area Light, which you can find in the Lights.h file, and implemented in the RayCaster.cpp in the shade_hit function.

Each Shape that is implemented is based on the Base class Shape.h, and each different shape is the Derived class from that all implementing their own intersection functions.  The shapes I used here are the sphere, the plane, the cube, and the cylinder (Sphere.h, Plane.h, Cube.h, Cylinder.h).  The intersection functions are implemented in the RayCaster.cpp file.

The Material.h file contains the Material class, which is used to store the lighting properties (color, ambient, diffuse, specular, and shininess of the object) for the Phong lighting model.  You can also control the object's reflectiveness, refractive index, and transparency.  The Material class is used in the Shape.h file to store the material of the object.

The main.cpp is the file I am running to create the world (lights/materials/objects) and the transformation of these objects for these screenshots.

My ray tracer is writing to ppm files, but I am including the converted png files as they are much smaller and I can embed them into the README.md file.

## Explaining the screenshots

### Spheres
I am including the unnecessary, but obligatory random bubbles ray tracer screenshot!

![Spheres](screenshots/random_bubbles.png)

Including a high resolution screenshot that has a plane, 2 spheres, and a cube.
The right hand sphere is high reflectivity, and each object has its own set of material properties and some with textures.
I used a point light, and a 2x2 area light in the scene which you can tell from the shadowing and the specular highlights on the spheres.

![A5_render](screenshots/A5_finalrender.png)

Including another image that includes a reflective cylinder as well with all the same properties as the above screenshot.

![A5_cyl](screenshots/A5_cyl.png)