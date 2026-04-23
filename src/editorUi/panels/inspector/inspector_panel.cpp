#include "editorUI/panels/objects/inspector_panel.h"
#include "imgui.h"

InspectorPanel::InspectorPanel(DebugContext &context) : IDebugPanel(context) {}

void InspectorPanel::draw()
{
    ImGui::SetNextWindowPos(ImVec2(0, 200));
    ImGui::SetNextWindowSize(ImVec2(216, 200));
    ImGui::Begin("Inspector");
    if (_context.selectedGameObjectIndex >= 0 &&
        _context.selectedGameObjectIndex < static_cast<int>(_context.gameObjects->size()))
    {
        GameObject *obj = (*_context.gameObjects)[_context.selectedGameObjectIndex];

        glm::vec2 pos = obj->getPosition();
        glm::vec2 scale = obj->getScale();

        ImGui::Text("Position");

        ImGui::Text("x");
        ImGui::SameLine();
        if (ImGui::DragFloat("##positionX", &pos.x, 0.01f, -1.0f, 1.0f))
            obj->setPosition(pos);

        ImGui::Text("y");
        ImGui::SameLine();
        if (ImGui::DragFloat("##positionY", &pos.y, 0.01f, -1.0f, 1.0f))
            obj->setPosition(pos);

        ImGui::Text("Scale");

        ImGui::Text("x");
        ImGui::SameLine();
        if (ImGui::DragFloat("##scaleX", &scale.x, 0.01f, -10.0f, 10.0f))
            obj->setScale(scale);

        ImGui::Text("y");
        ImGui::SameLine();
        if (ImGui::DragFloat("##scaleY", &scale.y, 0.01f, -10.0f, 10.0f))
            obj->setScale(scale);

        if (ImGui::Button("Aplicar"))
            obj->rebuildModelMatrix();
    }
    else
    {
        ImGui::Text("No object selected");
    }
    ImGui::End();
}