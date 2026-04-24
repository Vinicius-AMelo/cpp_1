#pragma once

#include <vector>
#include <cstddef>
#include <glad/glad.h>

#include "graphics/vao.h"
#include "graphics/vbo.h"
#include "graphics/ebo.h"

class SphereMesh
{
public:
    SphereMesh(float radius, std::size_t sectors = 36, std::size_t stacks = 18);

    void apply_matrices(int modelLoc, int viewLoc, int projectionLoc) const;
    void bind() const;
    void unbind() const;
    GLsizei indexCount() const;

    float radius;

private:
    std::size_t _sectors;
    std::size_t _stacks;

    std::vector<float> _vertices;          // pos(3) + color(3)
    std::vector<unsigned int> _indices;

    VAO _vao;
    VBO _vbo;
    EBO _ebo;
};