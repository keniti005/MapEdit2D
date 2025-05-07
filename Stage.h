#pragma once
#include "Library\\GameObject.h"
#include <vector>
#include "MapChip.h"

class Stage :
    public GameObject
{
    //int *bgHandle;//拝啓画像のバンドルの配列へのポインタ
    std::vector<int> bgHandle_;
    MapChip* mapChip_;//マップチップのポインタ
public:
    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;
};


