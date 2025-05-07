#pragma once
#include "Library/GameObject.h"
#include <vector>

namespace
{
    const int MAP_WIDTH = { 32 };
    const int MAP_HEIGHT = { 22 };
}

class MapEdit :
    public GameObject
{
    std::vector<int> myMap;
public:
    MapEdit();
    ~MapEdit();
    void Update()override;
    void Draw()override;
};

