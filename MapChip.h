#pragma once
#include "Library/GameObject.h"
#include "globals.h"
#include <vector>



class MapChip :
    public GameObject
{
    std::vector<int> bgHandle;
    std::vector<Rect>bgRects_;
    bool isUpdate_;
    bool isInMapChipArea_;
    Point selected_;//選択肢したマップチップの座標
    int selectedIndex_;//選択したマップチップのインデックス
    bool isHold_;
public:
    MapChip();
    ~MapChip();
    void Update()override;
    void Draw()override;
    bool IsHold();//マップチップを持っているかどうか
    int GetHoldImage();//持ってるマップチップのハンドルの取得
};

