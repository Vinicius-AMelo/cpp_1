#pragma once
#include "objects/square/square_mesh.h"

class Square
{
  private:
    SquareMesh _mesh;

  public:
    Square(const SquareMesh &mesh);
    // void update(float deltaTime);
    void draw() const;
};