#pragma once
#include "Library/GameObject.h"
#include "globals.h"
#include <vector>
#include <map>
#include "MapChipConfig.h"



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
    Point GetViewOrigin() const;//マップチップの左上の座標
    bool IsInChipMapArea(const Point& mouse)const;
    Point ScreenToChipIndex(const Point& mouse)const;
private:
    MapChipConfig cfg_;//マップチップの設定を保有する
    std::vector<int> bgHandle;
    std::map<int, int>HandleToIndex;
    

    //std::vector<Rect>bgRects_;
    bool isUpdate_;
    bool isInMapChipArea_;
    Point selected_;//選択肢したマップチップの座標
    int selectedIndex_;//選択したマップチップのインデックス
    bool isHold_;
    Point scrollOffset_;
};

