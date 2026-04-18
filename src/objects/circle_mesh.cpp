#include "objects/circle/circle_mesh.h"

#include <cmath>
#include <glm.hpp>

CircleMesh::CircleMesh(const float radius, const std::size_t segments)
    : _segments(segments), radius(radius)
{
    const float step = glm::radians(360.0f / static_cast<float>(_segments));

    _vertices.reserve(_segments * 9);

    for (int i = 0; i < static_cast<int>(_segments); i++)
    {
        const float currentAngle = static_cast<float>(i) * step;
        const float nextAngle = static_cast<float>(i + 1) * step;

        _vertices.push_back(0.0f);
        _vertices.push_back(0.0f);
        _vertices.push_back(0.0f);

        _vertices.push_back(std::cos(currentAngle) * radius);
        _vertices.push_back(std::sin(currentAngle) * radius);
        _vertices.push_back(0.0f);

        _vertices.push_back(std::cos(nextAngle) * radius);
        _vertices.push_back(std::sin(nextAngle) * radius);
        _vertices.push_back(0.0f);
    }

    _vao.bind();
    _vbo.bind();
    _vbo.setData(
        static_cast<GLsizeiptr>(_vertices.size()) * sizeof(float),
        _vertices.data(),
        GL_STATIC_DRAW
    );
    _vao.setVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    _vao.unbind();
    _vbo.unbind();
}

void CircleMesh::bind() const { _vao.bind(); }
void CircleMesh::unbind() const { _vao.unbind(); }
GLsizei CircleMesh::vertexCount() const { return static_cast<GLsizei>(_vertices.size()) / 3; }
