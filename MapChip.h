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
    Point selected_;//�I���������}�b�v�`�b�v�̍��W
    int selectedIndex_;//�I�������}�b�v�`�b�v�̃C���f�b�N�X
    bool isHold_;
public:
    MapChip();
    ~MapChip();
    void Update()override;
    void Draw()override;
    bool IsHold();//�}�b�v�`�b�v�������Ă��邩�ǂ���
    int GetHoldImage();//�����Ă�}�b�v�`�b�v�̃n���h���̎擾
};

