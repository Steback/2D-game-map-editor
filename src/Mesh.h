#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include "glm/glm.hpp"

struct Shape {
    glm::vec3 pos;
    glm::vec3 color;
    Shape(float _x, float _y, float _z, float _red, float _green, float _blue) : pos(glm::vec3(_x, _y, _z)), color(_red, _green, _blue) {  }
};

class Mesh {
    public:
        Mesh(const std::vector<Shape>& _vertices, const std::vector<GLuint>& _indices);
        ~Mesh();
        void RenderMesh() const;
        void ClearMesh();

    private:
        GLuint VAO{}, VBO{}, IBO{};
        GLsizei indexCount{};

        void CreateMesh(const std::vector<Shape>& _vertices, const std::vector<GLuint>& _indices);
};

#endif
