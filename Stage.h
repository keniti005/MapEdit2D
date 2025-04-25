#pragma once
#include "Library\\GameObject.h"
class Stage :
    public GameObject
{
public:
    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;
    int bgHandle;
};


