//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 12/4/22.
//

#ifndef RAYCASTER_MESH_H
#define RAYCASTER_MESH_H

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>
#include <iostream>
#include "Triangle.h"

class Mesh {
public:
    Mesh() {}

    void load_mesh(const std::string& filename);
    void set_transform(const Matrix4f& transform);
    void set_material(const Material& material);

    const aiMesh* mesh;
    std::vector<Triangle> triangles;


};

#endif //RAYCASTER_MESH_H
