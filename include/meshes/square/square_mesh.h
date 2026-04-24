#pragma once

#include <vector>
#include <cstddef>
#include <glad/glad.h>

#include "graphics/vao.h"
#include "graphics/vbo.h"
#include "graphics/ebo.h"

class SquareMesh
{
  public:
    SquareMesh();
    
    void bind() const;
    void unbind() const;
    GLsizei indexCount() const;

    float radius;

  private:
    std::size_t _sectors;
    std::size_t _stacks;

    std::vector<float> _vertices; // pos(3) + color(3)
    std::vector<unsigned int> _indices;

    VAO _vao;
    VBO _vbo;
    EBO _ebo;
};