#pragma once
#include "Library/GameObject.h"
#include "globals.h"
#include <vector>

namespace
{
    const int MAP_WIDTH = { 20 };
    const int MAP_HEIGHT = { 20 };
    const int MAP_IMAGE_SIZE = { 32 };//画像サイズ
    const int LEFT_MARGIN = { 100 };
    const int TOP_MARGIN = { 40 };
}

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
private:
    std::vector<int> myMap_;//マップの配列
    Rect drawAreaRect_;//描画領域の矩形
    Rect mapEditRect_;//マップ領域の矩形
    bool isInMapEditArea_;//マップエディタの領域にあるか
};

