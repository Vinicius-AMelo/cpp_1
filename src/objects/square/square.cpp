#include "objects/square/square.h"

Square::Square(const SquareMesh &mesh) : _mesh(mesh) {}

// void Square::update(const float deltaTime) {}

void Square::draw() const
{
    _mesh.bind();
    glDrawElements(GL_TRIANGLES, _mesh.indexCount(), GL_UNSIGNED_INT, nullptr);
    _mesh.unbind();
}
