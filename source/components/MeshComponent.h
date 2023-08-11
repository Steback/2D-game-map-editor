#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include <vector>

#include "glm/glm.hpp"

#include "../Component.h"
#include "../Mesh.h"

class MeshComponent : public Component {
    public:
        MeshComponent(const std::vector<Shape>& _vertices, const std::vector<GLuint>& _indices) {
            mesh = std::make_unique<Mesh>(_vertices, _indices);
        }

        void initialize() override {

        }

        void update(float deltaTime) override {

        }

        void render() override {
            mesh->RenderMesh();
        }

        std::unique_ptr<Mesh> mesh;
};

#endif
