#pragma once
#include "Library\\GameObject.h"
#include <vector>
#include "MapChip.h"

class Stage :
    public GameObject
{
    //int *bgHandle;//�q�[�摜�̃o���h���̔z��ւ̃|�C���^
    std::vector<int> bgHandle_;
    MapChip* mapChip_;//�}�b�v�`�b�v�̃|�C���^
public:
    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;
};


