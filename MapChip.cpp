#include "MapChip.h"
#include "Source/screen.h"

namespace
{
	const int IMAGE_SIZE = { 32 };//�摜�T�C�Y
	const int MAP_CHIP_WIDTH = { 16 };//�`�b�v�̉����ѐ�
	const int MAP_CHIP_HEIGHT = { 12 };//�`�b�v�̏c���ѐ�
	const int MAP_CHIP_NUM_X = { 8 };//�}�b�v�`�b�v�E�B���h�E�̉����ѐ�
	const int MAP_CHIP_NUM_Y = { 24 };//�}�b�v�`�b�v�E�B���h�E�̏c���ѐ�
	const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_NUM_X };//�E�B���h�E�̉���
	const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * MAP_CHIP_NUM_Y };//�E�B���h�E�̏c��
}

MapChip::MapChip()
	:GameObject()
	,bgHandle(MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, -1)
{	
	LoadDivGraph("./bg.png", MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT, MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, IMAGE_SIZE, IMAGE_SIZE, bgHandle.data());
}

MapChip::~MapChip()
{
	for (int i = 0;i < MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT;i++)
	{
		if (bgHandle[i] != -1)
		{
			DeleteGraph(bgHandle[i]);
			bgHandle[i] = -1;
		}
	}
}

void MapChip::Update()
{
}

void MapChip::Draw()
{
	int TOPLEFT_X = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
	int TOPLEFT_Y = 0;
	int RIGHTBOTTOM_X = Screen::WIDTH;
	int RIGHTBOTTOM_Y = MAP_CHIP_WIN_HEIGHT;

	for (int j = 0;j < MAP_CHIP_NUM_Y;j++)
	{
		for (int i = 0;i < MAP_CHIP_NUM_X;i++)
		{
			DrawGraph(TOPLEFT_X + i * IMAGE_SIZE, TOPLEFT_Y + j * IMAGE_SIZE, bgHandle[i * j * MAP_CHIP_NUM_X], TRUE);
		}
	}


	DrawBox(TOPLEFT_X, TOPLEFT_Y,RIGHTBOTTOM_X , RIGHTBOTTOM_Y, GetColor(255, 0, 0), FALSE , 3);

	//for (int j = 0;j < MAP_CHIP_HEIGHT;j++)
	//{
	//	for (int i = 0;i < MAP_CHIP_WIDTH;i++)
	//	{
	//		DrawGraph(i * IMAGE_SIZE, j * IMAGE_SIZE, bgHandle[i * j * MAP_CHIP_WIDTH], TRUE);
	//	}
	//}
	//
	//int TOPLEFT_X = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
	//int TOPLEFT_Y = 0;
	//int RIGHTBOTTOM_X = Screen::WIDTH;
	//int RIGHTBOTTOM_Y = MAP_CHIP_WIN_HEIGHT;
	//
	//DrawBox(TOPLEFT_X, TOPLEFT_Y, RIGHTBOTTOM_X, RIGHTBOTTOM_Y, GetColor(255, 0, 0), FALSE, 3);

}
