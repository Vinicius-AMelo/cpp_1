#pragma once
#include "objects/circle/circle_mesh.h"
#include <glad/glad.h>

class Circle
{
  private:
    float _ay;
    float _ax;
    SphereMesh _mesh;
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

    Circle(const SphereMesh &mesh, float startX, float startY);
    void sphere(int modelLoc, int viewLoc, int projectionLoc) const;
    void update(float deltaTime);
    void draw(GLint uOffsetLocation) const;
};