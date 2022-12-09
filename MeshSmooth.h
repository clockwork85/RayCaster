//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 12/6/22.
//

#ifndef RAYCASTER_MESHSMOOTH_H
#define RAYCASTER_MESHSMOOTH_H
#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>
#include <iostream>
#include "SmoothTriangle.h"

class MeshSmooth {
public:
    MeshSmooth() {}

    void load_mesh(const std::string& filename);
    void set_transform(const Matrix4f& transform);
    void set_material(const Material& material);

    const aiMesh* mesh;
    std::vector<SmoothTriangle> smooth_triangles;


};
#endif //RAYCASTER_MESHSMOOTH_H
