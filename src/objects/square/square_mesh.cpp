#include "objects/square/square_mesh.h"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

SquareMesh::SquareMesh()
{
    // clang-format off
    _vertices = {
        // Frente
        -0.5f, -0.5f,  0.0f,   1.0f, 0.0f, 0.0f, // 0 = bottom_left
         0.5f, -0.5f,  0.0f,   0.0f, 1.0f, 0.0f, // 1 = bottom_right
         0.5f,  0.5f,  0.0f,   0.0f, 0.0f, 1.0f, // 2 = top_right
        -0.5f,  0.5f,  0.0f,   1.0f, 1.0f, 0.0f, // 3 = top_left
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

void SquareMesh::apply_matrices(const int modelLoc, const int viewLoc, const int projectionLoc) const
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

void SquareMesh::bind() const { _vao.bind(); }

void SquareMesh::unbind() const { _vao.unbind(); }

GLsizei SquareMesh::indexCount() const { return static_cast<GLsizei>(_indices.size()); }