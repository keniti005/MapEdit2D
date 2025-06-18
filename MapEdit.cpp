#include "MapEdit.h"
#include "MapChip.h"
#include "Input.h"
#include <assert.h>

MapEdit::MapEdit()
	:GameObject(), myMap_(MAP_WIDTH* MAP_HEIGHT, -1),//初期値を-1で20*20
	isInMapEditArea_(false)
{
	mapEditRect_ = { LEFT_MARGIN,TOP_MARGIN,MAP_WIDTH * MAP_IMAGE_SIZE,MAP_HEIGHT * MAP_IMAGE_SIZE };
}

MapEdit::~MapEdit()
{
}

void MapEdit::SetMap(Point p, int value)
{
	//マップの座標pにvalueをセットする
	//pが、配列の範囲外の時はassertに引っかかる
	assert(p.x >= 0 && p.x < MAP_WIDTH);
	assert(p.y >= 0 && p.y < MAP_HEIGHT);
	myMap_[p.y * MAP_WIDTH + p.x] = value;//y行x列にvalueをセットする
}

int MapEdit::GetMap(Point p) const
{
	//マップの座標pに値をセットする
	assert(p.x >= 0 && p.x < MAP_WIDTH);
	assert(p.y >= 0 && p.y < MAP_HEIGHT);
	return myMap_[p.y * MAP_WIDTH + p.x];
}

void MapEdit::Update()
{
	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
	{
		return;
	}
	isInMapEditArea_ = (mousePos.x >= mapEditRect_.x && mousePos.x <= mapEditRect_.x + mapEditRect_.w &&
		mousePos.y >= mapEditRect_.y && mousePos.y <= mapEditRect_.y + mapEditRect_.h);

	if (!isInMapEditArea_)//マップエディタ領域外は何もしない
	{
		return;
	}
	int gridX = (mousePos.x - LEFT_MARGIN) / MAP_IMAGE_SIZE;
	int gridY = (mousePos.y - TOP_MARGIN) / MAP_IMAGE_SIZE;

	drawAreaRect_ = {LEFT_MARGIN + gridX * MAP_IMAGE_SIZE,TOP_MARGIN + gridY * MAP_IMAGE_SIZE,
	MAP_IMAGE_SIZE,MAP_IMAGE_SIZE};

	//if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
	//{
	//	MapChip* mapChip = FindGameObject<MapChip>();

	//	if (mapChip && mapChip->IsHold())//マップチップを持っている
	//	{
	//		SetMap({ gridX,gridY }, mapChip->GetHoldImage());
	//	}
	//}
}

void MapEdit::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(LEFT_MARGIN, TOP_MARGIN, MAP_WIDTH * MAP_IMAGE_SIZE + LEFT_MARGIN, MAP_HEIGHT * MAP_IMAGE_SIZE + TOP_MARGIN, GetColor(255, 255, 255), FALSE,5);
	for (int i = 0; i < MAP_WIDTH;i ++)
	{
		for (int j = 0; j < MAP_HEIGHT; j ++)
		{
			DrawLine(MAP_IMAGE_SIZE * i + LEFT_MARGIN, TOP_MARGIN, MAP_IMAGE_SIZE * i + LEFT_MARGIN, MAP_HEIGHT * MAP_IMAGE_SIZE + TOP_MARGIN, GetColor(255, 255, 255), 1);
			DrawLine(LEFT_MARGIN, MAP_IMAGE_SIZE * j + TOP_MARGIN, MAP_WIDTH * MAP_IMAGE_SIZE + LEFT_MARGIN, MAP_IMAGE_SIZE * j + TOP_MARGIN, GetColor(255, 255, 255), 1);
		}
	}

	//for (int i = 0;i < MAP_WIDTH;i++)
	//{
	//	for (int j = 0;j < MAP_HEIGHT;j++)
	//	{

	//	}
	//}

	if (isInMapEditArea_)
	{
		DrawBox(mapEditRect_.x, mapEditRect_.y, mapEditRect_.x + mapEditRect_.w, mapEditRect_.y + mapEditRect_.h, GetColor(0, 255, 0), TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
