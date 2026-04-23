#pragma once

struct InputControls
{
    static float getAxisX() { return _x; };
    static float getAxisY() { return _y; };

  protected:
    void setInputAxisX(const float x) { _x = x; };
    void setInputAxisY(const float y) { _y = y; };

  private:
    inline static float _x = 0.0f;
    inline static float _y = 0.0f;
};