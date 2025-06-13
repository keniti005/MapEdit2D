#pragma once
#include "Library\\GameObject.h"
#include <vector>
#include "MapChip.h"
#include "MapEdit.h"

class Stage :
    public GameObject
{
    //int *bgHandle;//�q�[�摜�̃o���h���̔z��ւ̃|�C���^
     
    //std::vector<int> bgHandle_;
    MapChip* mapChip_;//�}�b�v�`�b�v�̃|�C���^
    MapEdit* mapEdit_;//�}�b�v�G�f�B�^�̃|�C���^
    bool isMouseDown_;//�}�E�X�̍��W
    bool isOldMouseDown_;//�}�E�X�̏��
    bool isDragging_;//�P�t���O�̃}�E�X�̏��
public:
    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;
};


