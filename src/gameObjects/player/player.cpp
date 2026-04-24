#include "gameObjects/player/player.h"

#include "settings/input.h"

#include <glm/gtc/matrix_transform.hpp>

Player::Player(const SquareMesh &mesh) : _mesh(mesh) {}

void Player::start() { model = _model; }

void Player::update(const float deltaTime)
{
    const float xAxis = InputControls::getAxisX();
    const float yAxis = InputControls::getAxisY();

    const float velocity = 1.0f;
    _position.x += xAxis * velocity * deltaTime;
    _position.y += yAxis * velocity * deltaTime;
    rebuildModelMatrix();
    model = _model;
}

void Player::rebuildModelMatrix()
{
    _model = glm::mat4(1.0f);
    _model = glm::translate(_model, glm::vec3(_position, 0.0f));
    _model = glm::rotate(_model, _rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    _model = glm::scale(_model, glm::vec3(_scale, 1.0f));
}

void Player::draw() const
{
    _mesh.bind();
    glDrawElements(GL_TRIANGLES, _mesh.indexCount(), GL_UNSIGNED_INT, nullptr);
    _mesh.unbind();
}

glm::vec2 Player::getPosition() const { return _position; }
glm::vec2 Player::getScale() const { return _scale; }
float Player::getRotation() const { return _rotation; }
void Player::setPosition(const glm::vec2 position) { _position = position; }
void Player::setScale(const glm::vec2 scale) { _scale = scale; }
void Player::setRotation(const float rotation) { _rotation = rotation; }
