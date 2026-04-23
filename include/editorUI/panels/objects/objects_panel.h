#pragma once

#include "editorUI/i_debug_panel.h"

class ObjectsPanel : public IDebugPanel
{
  public:
    explicit ObjectsPanel(DebugContext &context);
    void draw() override;
};
