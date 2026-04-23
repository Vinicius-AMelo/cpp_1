#include "editorUI/debug_ui.h"

DebugUI::DebugUI() = default;

void DebugUI::setup()
{
    // Inicia o contexto Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
}
void DebugUI::setupRenderLibs(GLFWwindow *window)
{
    // Inicia os renders por plataforma
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}
void DebugUI::applyGUIStyles()
{
    // ImGui::StyleColorsLight();
    ImGuiStyle &style = ImGui::GetStyle();
    ImVec4 *colors = style.Colors;

    colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.5f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

    colors[ImGuiCol_Button] = ImVec4(0.2f, 0.4f, 0.8f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.5f, 0.9f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.1f, 0.3f, 0.7f, 1.0f);

    // style.WindowRounding = 8.0f;
    // style.FrameRounding = 5.0f;
    style.FrameBorderSize = 1.0f;
    style.WindowBorderSize = 1.0f;

    style.WindowPadding = ImVec2(8, 8);
    style.FramePadding = ImVec2(2, 2);
}

void DebugUI::init()
{
    // Inicia o frame Dear ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
void DebugUI::render()
{
    // Renderiza os painéis
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DebugUI::addPanel(std::unique_ptr<IDebugPanel> panel) { _panels.push_back(std::move(panel)); }

void DebugUI::drawPanels() const
{
    for (const auto &panel : _panels)
    {
        panel->draw();
    }
}