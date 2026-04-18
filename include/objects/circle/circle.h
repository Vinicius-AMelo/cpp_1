#pragma once
#include "objects/circle/circle_mesh.h"
#include <glm/glm.hpp>
#include <glad/glad.h>

class Circle
{
  private:
    float _ay;
    float _ax;
    CircleMesh _mesh;
    bool _touchBorder = false;

    void check_border_collision(float deltaTime);
    std::pair<float, float>
    bounce_force(float deltaTime, float border, float pos, float velocity, float a, float restitution);

  public:
    float x;
    float y;
    float velocityX;
    float velocityY;
    float lastVelocityY;

    Circle(const CircleMesh &mesh, float startX, float startY);

    void update(float deltaTime);
    void draw(GLint uOffsetLocation) const;
};