//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 12/4/22.
//

#include "Mesh.h"


void Mesh::load_mesh(const std::string& filename) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    mesh = scene->mMeshes[0];
    for(int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        Vector4f p1 = Vector4f(mesh->mVertices[face.mIndices[0]].x, mesh->mVertices[face.mIndices[0]].y, mesh->mVertices[face.mIndices[0]].z, 1.0f);
        Vector4f p2 = Vector4f(mesh->mVertices[face.mIndices[1]].x, mesh->mVertices[face.mIndices[1]].y, mesh->mVertices[face.mIndices[1]].z, 1.0f);
        Vector4f p3 = Vector4f(mesh->mVertices[face.mIndices[2]].x, mesh->mVertices[face.mIndices[2]].y, mesh->mVertices[face.mIndices[2]].z, 1.0f);
        triangles.emplace_back(p1, p2, p3);
    }
}

void Mesh::set_transform(const Matrix4f& transform) {
    for(auto& triangle : triangles) {
        triangle.p1 = transform * triangle.p1;
        triangle.p2 = transform * triangle.p2;
        triangle.p3 = transform * triangle.p3;
        triangle.e1 = triangle.p2 - triangle.p1;
        triangle.e2 = triangle.p3 - triangle.p1;
        triangle.normal = triangle.e2.cross3(triangle.e1).normalized();
    }
}

void Mesh::set_material(const Material& material) {
    for(auto& triangle : triangles) {
        triangle.material = material;
    }
}