#pragma once
#include "Library/GameObject.h"
#include "globals.h"
#include <vector>

namespace
{
    const int MAP_WIDTH = { 20 };
    const int MAP_HEIGHT = { 20 };
    const int MAP_IMAGE_SIZE = { 32 };//�摜�T�C�Y
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
    std::vector<int> myMap_;//�}�b�v�̔z��
    Rect drawAreaRect_;//�`��̈�̋�`
    Rect mapEditRect_;//�}�b�v�̈�̋�`
    bool isInMapEditArea_;//�}�b�v�G�f�B�^�̗̈�ɂ��邩
};

