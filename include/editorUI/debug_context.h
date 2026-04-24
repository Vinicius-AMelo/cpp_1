#pragma once

#include "../gameObjects/gameObject.h"

#include <vector>
struct DebugContext
{
    std::vector<GameObject *> *gameObjects = nullptr;
    int selectedGameObjectIndex = -1;
};
