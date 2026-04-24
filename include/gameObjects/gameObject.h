#pragma once

#include <glm/glm.hpp>

class GameObject
{
  protected:
    glm::mat4 _model = glm::mat4(1.0f);
    glm::vec2 _position = glm::vec2(0.0f, 0.0f);
    glm::vec2 _scale = glm::vec2(1.0f, 1.0f);
    float _rotation = 0.0f;

  public:
    int layer = 0;

    virtual ~GameObject() = default;
    virtual void update(float deltaTime) = 0;
    virtual void start() = 0;
    virtual void draw() const = 0;
    
    virtual glm::vec2 getPosition() const = 0;
    virtual glm::vec2 getScale() const = 0;
    virtual float getRotation() const = 0;
    virtual void setPosition(glm::vec2 position) = 0;
    virtual void setScale(glm::vec2 scale) = 0;
    virtual void setRotation(float rotation) = 0;

    virtual void rebuildModelMatrix() = 0;

  public:
    glm::mat4 model = _model;
};
