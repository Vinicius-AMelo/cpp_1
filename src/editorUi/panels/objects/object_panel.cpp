#include "editorUI/panels/objects/objects_panel.h"

#include "imgui.h"
#include <string>

ObjectsPanel::ObjectsPanel(DebugContext &context) : IDebugPanel(context) {}

void ObjectsPanel::draw()
{
    ImVec2 viewport = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(216, 200));
    ImGui::Begin("Objects");

    for (int i = 0; i < static_cast<int>(_context.gameObjects->size()); i++)
    {
        const bool selected = (_context.selectedGameObjectIndex == i);
        std::string label = "Object " + std::to_string(i);

        if (ImGui::Selectable(label.c_str(), selected))
            _context.selectedGameObjectIndex = i;
    }
    ImGui::End();
}