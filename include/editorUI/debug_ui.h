#pragma once
#include <memory>
#include <vector>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "i_debug_panel.h"

class DebugUI
{
  public:
    DebugUI();

    static void setup();
    static void setupRenderLibs(GLFWwindow *window);
    static void applyGUIStyles();
    static void init();
    static void render();
    void drawPanels() const;

    void addPanel(std::unique_ptr<IDebugPanel> panel);

  private:
    std::vector<std::unique_ptr<IDebugPanel>> _panels;
};