#include "objects/square/square.h"

#include "settings/input.h"

#include <iostream>
#include <ostream>
#include <glm/gtc/matrix_transform.hpp>

Square::Square(const SquareMesh &mesh) : _mesh(mesh) {}

void Square::start() { model = _model; }

void Square::update(const float deltaTime)
{
    const float x = InputControls::getAxisX();
    const float y = InputControls::getAxisY();
    const float velocity = 1.0f;
    const float posX = x * velocity * deltaTime;
    const float posY = y * velocity * deltaTime;
    _model = glm::translate(_model, glm::vec3(posX, posY, 0.0f));
    model = _model;
}

void Square::rebuildModelMatrix()
{
    _model = glm::mat4(1.0f);
    _model = glm::translate(_model, glm::vec3(_position, 0.0f));
    _model = glm::rotate(_model, _rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    _model = glm::scale(_model, glm::vec3(_scale, 1.0f));
}

void Square::draw() const
{
    _mesh.bind();
    glDrawElements(GL_TRIANGLES, _mesh.indexCount(), GL_UNSIGNED_INT, nullptr);
    _mesh.unbind();
}

glm::vec2 Square::getPosition() const { return _position; }
glm::vec2 Square::getScale() const { return _scale; }
float Square::getRotation() const { return _rotation; }
void Square::setPosition(const glm::vec2 position) { _position = position; }
void Square::setScale(const glm::vec2 scale) { _scale = scale; }
void Square::setRotation(const float rotation) { _rotation = rotation; }
