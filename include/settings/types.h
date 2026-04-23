#pragma once
#include "input.h"

#include <string>

#ifndef SHADER_DIR_PATH
#define SHADER_DIR_PATH "assets/shaders"
#endif

inline const std::string SHADER_DIR = SHADER_DIR_PATH;

struct Color
{
    float r;
    float g;
    float b;
    float a;
};

struct WindowSettings
{
    int windowWidth = 800;
    int windowHeight = 600;
    const char *windowTitle = "Learn OpenGl";

    Color backgroundColor = {0.0f, 0.0f, 0.0f, 1.0f};
};

struct InputSettings : protected InputControls
{
  public:
    void setAxisX(const float x) { setInputAxisX(x); };
    void setAxisY(const float y) { setInputAxisY(y); };
};