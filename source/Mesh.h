#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include "glm/glm.hpp"

struct Shape {
    glm::vec2 position;
    glm::vec2 texCoord;
    Shape(const glm::vec2& _pos, const glm::vec2& _texCoord) : position(_pos), texCoord(_texCoord) {  }
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
