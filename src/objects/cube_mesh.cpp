#include "objects/circle/cube_mesh.h"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

CubeMesh::CubeMesh()
{
    // clang-format off
    _vertices = {
        // Frente
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,

        // Trás
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,   0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   0.3f, 0.3f, 0.3f,   1.0f, 1.0f,

        // Esquerda
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,

        // Direita
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,   0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   0.3f, 0.3f, 0.3f,   1.0f, 1.0f,

        // Baixo
        -0.5f, -0.5f, -0.5f,   1.0f, 0.5f, 0.0f,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.5f, 1.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 0.5f, 1.0f,   1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.5f,   0.0f, 0.0f,

        // Cima
        -0.5f,  0.5f, -0.5f,   1.0f, 0.5f, 0.0f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   0.5f, 1.0f, 0.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   0.0f, 0.5f, 1.0f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.5f,   0.0f, 0.0f
    };

    _indices = {
        0,  1,  2,   2,  3,  0,   // Frente
        4,  5,  6,   6,  7,  4,   // Trás
        8,  9, 10,  10, 11,  8,   // Esquerda
       12, 13, 14,  14, 15, 12,   // Direita
       16, 17, 18,  18, 19, 16,   // Baixo
       20, 21, 22,  22, 23, 20    // Cima
   };
    // clang-format on

    _vao.bind();
    _vbo.bind();
    _ebo.bind();

    _vbo.setData(static_cast<GLsizeiptr>(_vertices.size() * sizeof(float)), _vertices.data(), GL_STATIC_DRAW);

    _ebo.setData(static_cast<GLsizeiptr>(_indices.size() * sizeof(unsigned int)), _indices.data(), GL_STATIC_DRAW);

    _vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    _vao.setVertexAttributes(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    _vao.setVertexAttributes(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));

    _vao.unbind();
    _vbo.unbind();
    _ebo.unbind();
}

void CubeMesh::apply_matrices(const int modelLoc, const int viewLoc, const int projectionLoc) const
{
    glm::mat4 model(1.0f);
    model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // model = glm::rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    const float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;

    view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void CubeMesh::bind() const { _vao.bind(); }

void CubeMesh::unbind() const { _vao.unbind(); }

GLsizei CubeMesh::indexCount() const { return static_cast<GLsizei>(_indices.size()); }