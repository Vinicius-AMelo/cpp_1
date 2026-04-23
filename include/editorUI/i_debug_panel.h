#pragma once
#include "debug_context.h"

class IDebugPanel
{
  public:
    explicit IDebugPanel(DebugContext &context) : _context(context) {};
    virtual ~IDebugPanel() = default;
    virtual void draw() = 0;

  protected:
    DebugContext &_context;
};