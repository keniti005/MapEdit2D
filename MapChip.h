#pragma once
#include "Library/GameObject.h"
#include "globals.h"
#include <vector>
#include <map>



class MapChip :
    public GameObject
{
public:
    MapChip();
    ~MapChip();
    void Update()override;
    void Draw()override;
    int GetHandle(int index) { return bgHandle[index]; }
    bool IsHold();//マップチップを持っているかどうか
    int GetHoldImage();//持ってるマップチップのハンドルの取得
    int GetChipIndex(int handle);
private:
    std::vector<int> bgHandle;
    std::map<int, int>HandleToIndex;

    std::vector<Rect>bgRects_;
    bool isUpdate_;
    bool isInMapChipArea_;
    Point selected_;//選択肢したマップチップの座標
    int selectedIndex_;//選択したマップチップのインデックス
    bool isHold_;
};

