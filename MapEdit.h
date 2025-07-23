#pragma once
#include "Library/GameObject.h"
#include "globals.h"
#include <vector>
#include "MapEditConfig.h"


class MapEdit :
    public GameObject
{
public:
    MapEdit();
    ~MapEdit();
    void SetMap(Point p, int value);
    int GetMap(Point p) const;
    bool IsInMapEditArea() const { return isInMapEditArea_; }

    void Update()override;
    void Draw()override;
    void SaveMapData();
    void LoadMapData();
private:
    MapEditConfig cfg_;
    std::vector<int> myMap_;//マップの配列
    Rect drawAreaRect_;//描画領域の矩形
    Rect mapEditRect_;//マップ領域の矩形
    bool isInMapEditArea_;//マップエディタの領域にあるか
};

