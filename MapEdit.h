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
    std::vector<int> myMap_;//�}�b�v�̔z��
    Rect drawAreaRect_;//�`��̈�̋�`
    Rect mapEditRect_;//�}�b�v�̈�̋�`
    bool isInMapEditArea_;//�}�b�v�G�f�B�^�̗̈�ɂ��邩
};

