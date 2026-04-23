#pragma once
#include "objects/gameObject.h"
#include "objects/square/square_mesh.h"

class Square : public GameObject
{
  private:
    SquareMesh _mesh;

  protected:
  public:
    Square(const SquareMesh &mesh);
    void update(float deltaTime) override;
    void start() override;
    void draw() const override;
    void rebuildModelMatrix() override;

    glm::vec2 getPosition() const override;
    glm::vec2 getScale() const override;
    float getRotation() const override;
    void setPosition(glm::vec2 position) override;
    void setScale(glm::vec2 scale) override;
    void setRotation(float rotation) override;
};