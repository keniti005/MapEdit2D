#pragma once
#include "Library\\GameObject.h"
#include <vector>
#include "MapChip.h"
#include "MapEdit.h"

class Stage :
    public GameObject
{
    //int *bgHandle;//拝啓画像のバンドルの配列へのポインタ
     
    //std::vector<int> bgHandle_;
    MapChip* mapChip_;//マップチップのポインタ
    MapEdit* mapEdit_;//マップエディタのポインタ
    bool isMouseDown_;//マウスの座標
    bool isOldMouseDown_;//マウスの状態
    bool isDragging_;//１フレ前のマウスの状態
public:
    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;
};


