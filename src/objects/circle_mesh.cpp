#include "objects/circle/circle_mesh.h"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

SphereMesh::SphereMesh(const float radius, const std::size_t sectors, const std::size_t stacks)
    : radius(radius), _sectors(sectors), _stacks(stacks)
{
    _vertices.reserve((_stacks + 1) * (_sectors + 1) * 6);
    _indices.reserve(_stacks * _sectors * 6);

    const float pi = glm::pi<float>();

    for (std::size_t i = 0; i <= _stacks; ++i)
    {
        const float stackPercent = static_cast<float>(i) / static_cast<float>(_stacks);
        const float stackAngle = pi / 2.0f - stackPercent * pi; // +90 até -90

        const float xy = radius * std::cos(stackAngle);
        const float y  = radius * std::sin(stackAngle);

        for (std::size_t j = 0; j <= _sectors; ++j)
        {
            const float sectorPercent = static_cast<float>(j) / static_cast<float>(_sectors);
            const float sectorAngle = sectorPercent * 2.0f * pi;

            const float x = xy * std::cos(sectorAngle);
            const float z = xy * std::sin(sectorAngle);

            _vertices.push_back(x);
            _vertices.push_back(y);
            _vertices.push_back(z);

            // cor simples baseada na posição normalizada
            _vertices.push_back((x / radius + 1.0f) * 0.5f);
            _vertices.push_back((y / radius + 1.0f) * 0.5f);
            _vertices.push_back((z / radius + 1.0f) * 0.5f);
        }
    }

    for (std::size_t i = 0; i < _stacks; ++i)
    {
        const std::size_t k1 = i * (_sectors + 1);
        const std::size_t k2 = k1 + _sectors + 1;

        for (std::size_t j = 0; j < _sectors; ++j)
        {
            if (i != 0)
            {
                _indices.push_back(static_cast<unsigned int>(k1 + j));
                _indices.push_back(static_cast<unsigned int>(k2 + j));
                _indices.push_back(static_cast<unsigned int>(k1 + j + 1));
            }

            if (i != (_stacks - 1))
            {
                _indices.push_back(static_cast<unsigned int>(k1 + j + 1));
                _indices.push_back(static_cast<unsigned int>(k2 + j));
                _indices.push_back(static_cast<unsigned int>(k2 + j + 1));
            }
        }
    }

    _vao.bind();
    _vbo.bind();
    _ebo.bind();

    _vbo.setData(
        static_cast<GLsizeiptr>(_vertices.size() * sizeof(float)),
        _vertices.data(),
        GL_STATIC_DRAW
    );

    _ebo.setData(
        static_cast<GLsizeiptr>(_indices.size() * sizeof(unsigned int)),
        _indices.data(),
        GL_STATIC_DRAW
    );

    _vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    _vao.setVertexAttributes(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    _vao.unbind();
    _vbo.unbind();
    _ebo.unbind();
}

void SphereMesh::apply_matrices(const int modelLoc, const int viewLoc, const int projectionLoc) const
{
    glm::mat4 model(1.0f);
    model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void SphereMesh::bind() const
{
    _vao.bind();
}

void SphereMesh::unbind() const
{
    _vao.unbind();
}

GLsizei SphereMesh::indexCount() const
{
    return static_cast<GLsizei>(_indices.size());
}