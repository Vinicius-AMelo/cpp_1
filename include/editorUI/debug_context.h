#pragma once

#include "objects/gameObject.h"

#include <vector>
struct DebugContext
{
    std::vector<GameObject *> *gameObjects = nullptr;
    int selectedGameObjectIndex = -1;
};
