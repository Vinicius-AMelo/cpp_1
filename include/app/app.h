#pragma once

class App
{
  private:
    int width;
    static int update(float deltaTime);

  public:
    static int run();
};