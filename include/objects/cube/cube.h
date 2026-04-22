#pragma once
#include "objects/cube/cube_mesh.h"

class Cube
{
  private:
    CubeMesh _mesh;

  public:
    Cube(const CubeMesh &mesh);
    // void update(float deltaTime);
    void draw() const;
};