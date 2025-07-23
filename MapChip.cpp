#define NOMINMAX
#include "MapChip.h"
#include "Source/screen.h"
#include "Input.h"
#include <algorithm>

namespace
{
	//const int IMAGE_SIZE = { 32 };//画像サイズ
	//const int MAP_CHIP_WIDTH = { 16 };//チップの横並び数
	//const int MAP_CHIP_HEIGHT = { 12 };//チップの縦並び数
	//const int MAP_CHIP_NUM_X = { 8 };//マップチップウィンドウの横並び数
	//const int MAP_CHIP_NUM_Y = { 24 };//マップチップウィンドウの縦並び数
	//const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_NUM_X };//ウィンドウの横幅
	//const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * MAP_CHIP_NUM_Y };//ウィンドウの縦幅
	
	////ドラッグ開始と判定する移動量
	//const int DRAG_THRESHOLD = 5;
}

//int cfg_.TITLE_PIX_SIZE
//int cfg_.TILES_X
//int cfg_.TILES_Y
//int cfg_.MAPCHIP_VIEW_X
//int cfg_.MAPCHIP_VIEW_Y
//int cfg_.MAPCHIP_WIN_WIDTH
//int cfg_.MAPCHIP_WIN_HEIGHT

MapChip::MapChip()
	:GameObject(),cfg_(GetMapChipConfig()),isHold_(false),isUpdate_(false),isInMapChipArea_(false)
	,selectedIndex_(-1),selected_({0,0})
	,bgHandle(cfg_.TILES_X* cfg_.TILES_Y, -1)
	,scrollOffset_({0,0})
{	
	LoadDivGraph("./bg.png", cfg_.TILES_X * cfg_.TILES_Y, cfg_.TILES_X, cfg_.TILES_Y, cfg_.TITLE_PIX_SIZE, cfg_.TITLE_PIX_SIZE, bgHandle.data());

	//char buff[128];
	//GetPrivateProfileStringA("MapChip", "Title", "MYGAME", buff, sizeof(buff), "./mySetup.ini");
	//int wsize = GetPrivateProfileInt("MapChip", "WINSIZE", 255, "./mySetup.ini");
	

	//モーダルダイアログボックス（ファイル選択から出られないもの）
	//モードレスダイアログボックス（小ウィンドウが付属されているもの）
	//LUT(Look Up Table)というもの
	for (int i = 0;i < bgHandle.size(); i++)
	{
		HandleToIndex[bgHandle[i]] = i;
	}
}

MapChip::~MapChip()
{
	for (int i = 0;i < cfg_.TILES_X * cfg_.TILES_Y;i++)
	{
		if (bgHandle[i] != -1)
		{
			DeleteGraph(bgHandle[i]);
			bgHandle[i] = -1;
		}
	}
}

Point MapChip::GetViewOrigin() const
{
	return { Screen::WIDTH - cfg_.MAPCHIP_WIN_WIDTH, 0 };
}

bool MapChip::IsInChipMapArea(const Point& mouse)const
{
	return { mouse.x > GetViewOrigin().x && mouse.x < Screen::WIDTH &&
		mouse.y > GetViewOrigin().y && mouse.y < Screen::HEIGHT };
}

Point MapChip::ScreenToChipIndex(const Point& mouse)const
{
	int localX = (mouse.x - GetViewOrigin().x) / cfg_.TITLE_PIX_SIZE;
	int localY = mouse.y / cfg_.TITLE_PIX_SIZE;
	return { localX,localY };
}

void MapChip::Update()
{
	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
	{
		return;
	}

	isInMapChipArea_ = IsInChipMapArea(mousePos);

	if (isInMapChipArea_)
	{
		if (Input::IsKeyDown(KEY_INPUT_LEFT))
		{
			scrollOffset_.x = std::min(std::max(0, cfg_.TILES_X - cfg_.MAPCHIP_VIEW_X), scrollOffset_.x + 1);
		}
		if (Input::IsKeyDown(KEY_INPUT_RIGHT))
		{
			scrollOffset_.x = std::max(0, scrollOffset_.x - 1);
		}

		if (Input::IsKeyDown(KEY_INPUT_UP))
		{
			scrollOffset_.y = std::max(0, scrollOffset_.y - 1);
		}
		if (Input::IsKeyDown(KEY_INPUT_DOWN))
		{
			scrollOffset_.y = std::min(std::max(0, cfg_.TILES_Y - cfg_.MAPCHIP_VIEW_Y), scrollOffset_.y + 1);
		}

		selected_ = ScreenToChipIndex(mousePos);

		int index = (selected_.y + scrollOffset_.y) * cfg_.TILES_X + selected_.x + scrollOffset_.x;

		//int index = ((selected_.y - scrollOffset_.y) + cfg_.MAPCHIP_VIEW_Y) * cfg_.TILES_X + selected_.x + scrollOffset_.x;

		if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
		{
			isHold_ = true;
			selectedIndex_ = bgHandle[index];
		}
	}
	else
	{
		isInMapChipArea_ = false;
	}
}

void MapChip::Draw()
{
	//マップチップ領域表示
	for (int i = 0;i < cfg_.TILES_X;i++)
	{
		for (int j = 0;j < cfg_.MAPCHIP_VIEW_Y;j++)
		{

			int index = i + scrollOffset_.x + (j + scrollOffset_.y) * cfg_.TILES_X;

			if (index < 0 || index >= bgHandle.size())
			{
				continue;
			}
			DrawGraph(GetViewOrigin().x + i * cfg_.TITLE_PIX_SIZE,
					  GetViewOrigin().y + j * cfg_.TITLE_PIX_SIZE, bgHandle[index], TRUE);

		}
	}


	//マップチップの選択範囲をハイライト
	if (isInMapChipArea_)
	{
		int px = GetViewOrigin().x + selected_.x * cfg_.TITLE_PIX_SIZE;
		int py = selected_.y * cfg_.TITLE_PIX_SIZE;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(px, py,
			px + cfg_.TITLE_PIX_SIZE, py + cfg_.TITLE_PIX_SIZE, GetColor(132, 255, 193), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawBox(px, py,
			px + cfg_.TITLE_PIX_SIZE,py + cfg_.TITLE_PIX_SIZE, GetColor(255, 0, 0), FALSE, 2);
	}

	if (isHold_)
	{
		Point mousePos;
		if (GetMousePoint(&mousePos.x, &mousePos.y) != -1)
		{
			DrawExtendGraph(mousePos.x, mousePos.y, mousePos.x + cfg_.TITLE_PIX_SIZE, mousePos.y + cfg_.TITLE_PIX_SIZE, selectedIndex_, TRUE);
		}

		if (Input::IsButtonUP(MOUSE_INPUT_RIGHT))
		{
			isHold_ = false;
			selectedIndex_ = -1;
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

bool MapChip::IsHold()
{
	return isHold_;
}

int MapChip::GetHoldImage()
{
	if (isHold_)
	{
		return selectedIndex_;
	}
	else
	{
		return -1;//持っていない場合は-1を返す
	}
}

int MapChip::GetChipIndex(int handle)
{
	if (HandleToIndex[handle] != -1)
	{
		return HandleToIndex[handle];
	}
	else
	{
		return -1;
	}
	//for (int i = 0; i < bgHandle.size(); i++)
	//{
	//	if (handle == bgHandle[i])
	//	{
	//		return i;
	//	}
	//}
}
