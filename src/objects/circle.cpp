#include "objects/circle/circle.h"
#include "settings/physics.h"

#include <iostream>
#include <cmath>

Circle::Circle(const SphereMesh &mesh, const float startX, const float startY)
    : _mesh(mesh), x(startX), y(startY), velocityX(0.0f), velocityY(0.0f), lastVelocityY(velocityY)
{
    constexpr Gravity gravity;
    float forceX = 1.0f;
    _ay = gravity.acceleration;
    _ax = forceX;
}

void Circle::update(const float deltaTime)
{
    check_border_collision(deltaTime);
}

void Circle::check_border_collision(const float deltaTime)
{
    const float top = 1.0f - _mesh.radius;
    const float right = 1.0f - _mesh.radius;
    const float bottom = -1.0f + _mesh.radius;
    const float left = -1.0f + _mesh.radius;
    const float y0 = y;
    const float vy0 = velocityY;
    const float x0 = x;
    const float vx0 = velocityX;
    bool hasCollision = false;
    const float restitutionY = 0.9f;
    const float restitutionX = 0.2f;

    const float nextPositionY = y0 + vy0 * deltaTime + 0.5f * _ay * deltaTime * deltaTime;
    const float nextPositionX = x0 + vx0 * deltaTime + 0.5f * _ax * deltaTime * deltaTime;

    if (nextPositionY < bottom)
    {
        auto [pos, velocity] = bounce_force(deltaTime, bottom, y0, vy0, _ay, restitutionY);
        y = pos;
        velocityY = velocity;
        hasCollision = true;
    }

    if (nextPositionY > top)
    {
        auto [pos, velocity] = bounce_force(deltaTime, top, y0, vy0, _ay, restitutionY);
        y = pos;
        velocityY = velocity;
        hasCollision = true;
    }

    if (nextPositionX > right)
    {
        auto [pos, velocity] = bounce_force(deltaTime, right, x0, vx0, _ax, restitutionX);
        _ax *= -1.0f;
        x = pos;
        velocityX = velocity;
        hasCollision = true;
    }
    if (nextPositionX < left)
    {
        auto [pos, velocity] = bounce_force(deltaTime, left, x0, vx0, _ax, restitutionX);
        x = pos;
        velocityX = velocity;
        _ax *= -1.0f;
        hasCollision = true;
    }

    if (!hasCollision)
    {
        y = nextPositionY;
        velocityY = vy0 + _ay * deltaTime;

        x = nextPositionX;
        velocityX = vx0 + _ax * deltaTime;
    }

    // check_collision(deltaTime, top);
}

std::pair<float, float> Circle::bounce_force(
    const float deltaTime, const float border, float pos, float velocity, const float a, const float restitution
)
{
    const float p0 = pos;
    const float v0 = velocity;

    // Se não bateu no chão, só integra normalmente

    // Resolver o tempo de impacto:
    // y0 + v0*t + 0.5*a*t² = floorY
    const float A = 0.5f * a;
    const float B = v0;
    const float C = p0 - border;

    const float discriminant = B * B - 4.0f * A * C;

    if (discriminant < 0.0f)
    {
        // fallback de segurança
        pos = border;
        velocity = -v0 * restitution;
        return {pos, velocity};
    }

    const float sqrtD = std::sqrt(discriminant);

    // Pegamos a raiz que cai dentro do frame
    float tHit = (-B - sqrtD) / (2.0f * A);
    if (tHit < 0.0f || tHit > deltaTime)
    {
        tHit = (-B + sqrtD) / (2.0f * A);
    }

    // Velocidade exata no impacto
    const float vHit = v0 + a * tHit;

    // Rebater
    const float vAfterBounce = -vHit * restitution;

    // Tempo restante após o impacto
    const float remainingTime = deltaTime - tHit;

    // Integrar o resto do frame corretamente
    pos = border + vAfterBounce * remainingTime + 0.5f * a * remainingTime * remainingTime;
    velocity = vAfterBounce + a * remainingTime;

    // Clamp de segurança
    if (pos < border)
    {
        pos = border;
    }

    return {pos, velocity};
}

void Circle::sphere(const int modelLoc, const int viewLoc, const int projectionLoc) const
{
    _mesh.bind();
    _mesh.apply_matrices(modelLoc, viewLoc, projectionLoc);
    _mesh.unbind();
}

void Circle::draw(const GLint uOffsetLocation) const
{
    (void)uOffsetLocation;
    _mesh.bind();
    glUniform2f(uOffsetLocation, x, y);
    glDrawElements(GL_TRIANGLES, _mesh.indexCount(), GL_UNSIGNED_INT, nullptr);
    _mesh.unbind();
}
