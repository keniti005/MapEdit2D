#include "MapChip.h"
#include "Source/screen.h"
#include "Input.h"

namespace
{
	const int IMAGE_SIZE = { 32 };//画像サイズ
	const int MAP_CHIP_WIDTH = { 16 };//チップの横並び数
	const int MAP_CHIP_HEIGHT = { 12 };//チップの縦並び数
	const int MAP_CHIP_NUM_X = { 8 };//マップチップウィンドウの横並び数
	const int MAP_CHIP_NUM_Y = { 24 };//マップチップウィンドウの縦並び数
	const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_NUM_X };//ウィンドウの横幅
	const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * MAP_CHIP_NUM_Y };//ウィンドウの縦幅

	//ドラッグ開始と判定する移動量
	const int DRAG_THRESHOLD = 5;
}

MapChip::MapChip()
	:GameObject()
	,bgHandle(MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, -1)
{	
	LoadDivGraph("./bg.png", MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, MAP_CHIP_WIDTH , MAP_CHIP_HEIGHT, IMAGE_SIZE, IMAGE_SIZE, bgHandle.data());
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
	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
	{
		return;
	}

	isInMapChipArea_ = (mousePos.x > Screen::WIDTH - MAP_CHIP_WIN_WIDTH && mousePos.x < Screen::WIDTH &&
		mousePos.y > 0 && mousePos.y < MAP_CHIP_WIN_HEIGHT);

	if (isInMapChipArea_)
	{
		selected_.x = (mousePos.x - (Screen::WIDTH - MAP_CHIP_WIN_WIDTH)) / IMAGE_SIZE;
		selected_.y = mousePos.y / IMAGE_SIZE;
		if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
		{
			isHold_ = true;
			selectedIndex_ = bgHandle[selected_.y * MAP_CHIP_NUM_X + selected_.x];
		}
	}
	else
	{
		isInMapChipArea_ = false;
	}
}

void MapChip::Draw()
{
	int TOPLEFT_X = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
	int TOPLEFT_Y = 0;
	int RIGHTBOTTOM_X = Screen::WIDTH;
	int RIGHTBOTTOM_Y = MAP_CHIP_WIN_HEIGHT;
	for (int i = 0;i < MAP_CHIP_NUM_X;i++)
	{
		for (int j = 0;j < MAP_CHIP_NUM_Y;j++)
		{
			DrawGraph(TOPLEFT_X + i * IMAGE_SIZE, TOPLEFT_Y + j * IMAGE_SIZE, bgHandle[i + j * MAP_CHIP_NUM_X], TRUE);
		}
	}



	if (isInMapChipArea_)
	{

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(TOPLEFT_X + selected_.x * IMAGE_SIZE, selected_.y * IMAGE_SIZE,
			TOPLEFT_X + selected_.x * IMAGE_SIZE + IMAGE_SIZE, selected_.y * IMAGE_SIZE + IMAGE_SIZE, GetColor(132, 255, 193), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawBox(TOPLEFT_X + selected_.x * IMAGE_SIZE, selected_.y * IMAGE_SIZE,
			TOPLEFT_X + selected_.x * IMAGE_SIZE + IMAGE_SIZE, selected_.y * IMAGE_SIZE + IMAGE_SIZE, GetColor(255, 0, 0), FALSE, 2);
	}
	if (isHold_)
	{
		Point mousePos;
		if (GetMousePoint(&mousePos.x, &mousePos.y) != -1)
		{
			DrawExtendGraph(mousePos.x, mousePos.y, mousePos.x + IMAGE_SIZE, mousePos.y + IMAGE_SIZE, selectedIndex_, TRUE);
		}

	}

	//for (int i = 0;i < MAP_CHIP_WIDTH;i++)
	//{
	//	for (int j = 0;j < MAP_CHIP_HEIGHT;j++)
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

bool MapChip::isHold()
{
	return isHold_;
}

int MapChip::GetHoldImage()
{
	return 0;
}
