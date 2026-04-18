#pragma once

#include <cstddef>
#include <vector>
#include <graphics/vao.h>
#include <graphics/vbo.h>

class CircleMesh
{
  private:
    std::size_t _segments;
    std::vector<float> _vertices;
    VAO _vao;
    VBO _vbo;

  public:
    explicit CircleMesh(float radius, std::size_t segments = 100);
    float radius;

    void bind() const;
    void unbind() const;
    GLsizei vertexCount() const;
};
