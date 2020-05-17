#include <vector>

#include "Mesh.h"

Mesh::Mesh(const std::vector<Shape>& _vertices, const std::vector<GLuint>& _indices) : indexCount(_indices.size()) {
    CreateMesh(_vertices, _indices);
}

Mesh::~Mesh() { ClearMesh(); };

void Mesh::CreateMesh(const std::vector<Shape>& _vertices, const std::vector<GLuint>& _indices) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0]) * _indices.size(), &_indices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices[0]) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(_vertices[0]), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(_vertices[0]), (void*)(sizeof(_vertices[0].pos)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::RenderMesh() const {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::ClearMesh() {
    if ( IBO != 0 ) {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }

    if ( VBO != 0 ) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if ( VAO != 0 ) {
        glDeleteBuffers(1, &VAO);
        VAO = 0;
    }

    indexCount = 0;
}