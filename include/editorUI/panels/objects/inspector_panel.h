#pragma once

#include "editorUI/i_debug_panel.h"

class InspectorPanel : public IDebugPanel
{
  public:
    explicit InspectorPanel(DebugContext &context);
    void draw() override;
};
