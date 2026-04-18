#include "objects/circle/cube.h"

Cube::Cube(const CubeMesh &mesh) : _mesh(mesh) {}

// void Cube::update(const float deltaTime) {}

void Cube::draw() const
{
    _mesh.bind();
    glDrawElements(GL_TRIANGLES, _mesh.indexCount(), GL_UNSIGNED_INT, nullptr);
    _mesh.unbind();
}
