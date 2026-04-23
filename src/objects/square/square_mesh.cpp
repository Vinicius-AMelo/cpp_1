#include "objects/square/square_mesh.h"

#include <cmath>

#include <GLFW/glfw3.h>

SquareMesh::SquareMesh()
{
    // clang-format off
    _vertices = {
        // Frente
        -0.1f, -0.1f,  0.0f,   1.0f, 0.0f, 0.0f, // 0 = bottom_left
         0.1f, -0.1f,  0.0f,   0.0f, 1.0f, 0.0f, // 1 = bottom_right
         0.1f,  0.1f,  0.0f,   0.0f, 0.0f, 1.0f, // 2 = top_right
        -0.1f,  0.1f,  0.0f,   1.0f, 1.0f, 0.0f, // 3 = top_left
    };

    _indices = {
        0, 1, 2, // [3, 2]
        2, 3, 0, // [0, 1]
   };
    // clang-format on

    _vao.bind();
    _vbo.bind();
    _ebo.bind();

    _vbo.setData(static_cast<GLsizeiptr>(_vertices.size() * sizeof(float)), _vertices.data(), GL_STATIC_DRAW);
    _ebo.setData(static_cast<GLsizeiptr>(_indices.size() * sizeof(unsigned int)), _indices.data(), GL_STATIC_DRAW);

    _vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    _vao.setVertexAttributes(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));

    _vao.unbind();
    _vbo.unbind();
    _ebo.unbind();
}

void SquareMesh::bind() const { _vao.bind(); }

void SquareMesh::unbind() const { _vao.unbind(); }

GLsizei SquareMesh::indexCount() const { return static_cast<GLsizei>(_indices.size()); }