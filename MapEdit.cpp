#include <windows.h>
#include "MapEdit.h"
#include "MapChip.h"
#include "Input.h"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

namespace
{
	//const int MAP_IMAGE_SIZE = { 32 };//画像サイズ
	//const int MAP_WIDTH = { 20 };
	//const int MAP_HEIGHT = { 20 };
	//const int LEFT_MARGIN = { 100 };
	//const int TOP_MARGIN = { 40 };
}
//int TITLE_PIX_SIZE;
//int MAPEDIT_WIDTH;
//int MAPEDIT_HEIGHT;
//int MARGIN_TOP;
//int MARGIN_LEFT;


MapEdit::MapEdit()
	:GameObject(), myMap_(cfg_.MAPEDIT_WIDTH* cfg_.MAPEDIT_HEIGHT, -1),//初期値を-1で20*20
	isInMapEditArea_(false),
	cfg_(GetMapEditConfig())
{
	mapEditRect_ = { cfg_.MARGIN_LEFT,cfg_.MARGIN_TOP,cfg_.MAPEDIT_WIDTH * cfg_.TITLE_PIX_SIZE,cfg_.MAPEDIT_HEIGHT * cfg_.TITLE_PIX_SIZE };
}

MapEdit::~MapEdit()
{
}

void MapEdit::SetMap(Point p, int value)
{
	//マップの座標pにvalueをセットする
	//pが、配列の範囲外の時はassertに引っかかる
	assert(p.x >= 0 && p.x < cfg_.MAPEDIT_WIDTH);
	assert(p.y >= 0 && p.y < cfg_.MAPEDIT_HEIGHT);
	myMap_[p.y * cfg_.MAPEDIT_WIDTH + p.x] = value;//y行x列にvalueをセットする
}

int MapEdit::GetMap(Point p) const
{
	//マップの座標pに値をセットする
	assert(p.x >= 0 && p.x < cfg_.MAPEDIT_WIDTH);
	assert(p.y >= 0 && p.y < cfg_.MAPEDIT_HEIGHT);
	return myMap_[p.y * cfg_.MAPEDIT_WIDTH + p.x];
}

void MapEdit::Update()
{
	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
	{
		return;
	}
	//マウスの座標がマップエディタの領域内にいるか
	isInMapEditArea_ = (mousePos.x >= mapEditRect_.x && mousePos.x <= mapEditRect_.x + mapEditRect_.w &&
		mousePos.y >= mapEditRect_.y && mousePos.y <= mapEditRect_.y + mapEditRect_.h);

	if (!isInMapEditArea_)//マップエディタ領域外は何もしない
	{
		return;
	}
	int gridX = (mousePos.x - cfg_.MARGIN_LEFT) / cfg_.TITLE_PIX_SIZE;
	int gridY = (mousePos.y - cfg_.MARGIN_TOP) / cfg_.TITLE_PIX_SIZE;

	drawAreaRect_ = {cfg_.MARGIN_LEFT + gridX * cfg_.TITLE_PIX_SIZE,cfg_.MARGIN_TOP + gridY * cfg_.TITLE_PIX_SIZE,
	cfg_.TITLE_PIX_SIZE,cfg_.TITLE_PIX_SIZE};
	
	if (Input::IsButtonKeep(MOUSE_INPUT_LEFT))
	{
		MapChip* mapChip = FindGameObject<MapChip>();

		if (mapChip && mapChip->IsHold())//マップチップを持っている
		{
			SetMap({ gridX,gridY }, mapChip->GetHoldImage());
		}
		//左シフトを押している状態でマップチップを削除
		if (Input::IsKeepKeyDown(KEY_INPUT_LSHIFT))
		{
			SetMap({ gridX,gridY }, -1);
		}
	}

	if (Input::IsKeyDown(KEY_INPUT_S))
	{
		SaveMapData();
	}
	if (Input::IsKeyDown(KEY_INPUT_L))
	{
		LoadMapData();
	}
}

void MapEdit::Draw()
{
	for (int i = 0; i < cfg_.MAPEDIT_WIDTH; i++)
	{
		for (int j = 0; j < cfg_.MAPEDIT_HEIGHT; j++)
		{
			int value = GetMap({ i,j });
			if (value != -1)
			{
				DrawGraph(cfg_.MARGIN_LEFT + i * cfg_.TITLE_PIX_SIZE, cfg_.MARGIN_TOP + j * cfg_.TITLE_PIX_SIZE, value, TRUE);
			}
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(cfg_.MARGIN_LEFT, cfg_.MARGIN_TOP, cfg_.MAPEDIT_WIDTH * cfg_.TITLE_PIX_SIZE + cfg_.MARGIN_LEFT, cfg_.MAPEDIT_HEIGHT * cfg_.TITLE_PIX_SIZE + cfg_.MARGIN_TOP, GetColor(255, 255, 255), FALSE, 5);
	for (int i = 0; i < cfg_.MAPEDIT_WIDTH;i++)
	{
		for (int j = 0; j < cfg_.MAPEDIT_HEIGHT; j++)
		{
			DrawLine(cfg_.TITLE_PIX_SIZE * i + cfg_.MARGIN_LEFT, cfg_.MARGIN_TOP, cfg_.TITLE_PIX_SIZE * i + cfg_.MARGIN_LEFT, cfg_.MAPEDIT_HEIGHT * cfg_.TITLE_PIX_SIZE + cfg_.MARGIN_TOP, GetColor(255, 255, 255), 1);
			DrawLine(cfg_.MARGIN_LEFT, cfg_.TITLE_PIX_SIZE * j + cfg_.MARGIN_TOP, cfg_.MAPEDIT_WIDTH * cfg_.TITLE_PIX_SIZE + cfg_.MARGIN_LEFT, cfg_.TITLE_PIX_SIZE * j + cfg_.MARGIN_TOP, GetColor(255, 255, 255), 1);
		}
	}
	if (isInMapEditArea_)
	{
		//DrawBox(mapEditRect_.x, mapEditRect_.y, mapEditRect_.x + mapEditRect_.w, mapEditRect_.y + mapEditRect_.h, GetColor(0, 255, 0), TRUE);
		DrawBox(drawAreaRect_.x, drawAreaRect_.y, drawAreaRect_.x + drawAreaRect_.w, drawAreaRect_.y + drawAreaRect_.h, GetColor(255, 255, 0), TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MapEdit::SaveMapData()
{
	//ファイル選択ダイアログ
	TCHAR filename[255] = "";
	OPENFILENAME ofn = {0};

	ofn.lStructSize = sizeof(ofn);
	//ウィンドウのオーナー＝親ウィンドウのハンドル
	ofn.hwndOwner = GetMainWindowHandle();
	ofn.lpstrFilter = "全てのファイル (*.*)\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 255;
	ofn.Flags = OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn))
	{
		printfDx("ファイルが選択された\n");
		//ファイルを開いて、セーブ
		std::ofstream openfile(filename);
		//openfile << "#header" << std::endl
			//<< "WIDTH " << MAP_WIDTH << std::endl
			//<< "HEIGHT " << MAP_HEIGHT << std::endl << std::endl;
		openfile << "#TinyMapData" << std::endl;
		MapChip* mc = FindGameObject<MapChip>();

		//for (auto& itr : myMap_)
		//{
		//	file << itr << std::endl;
		//}
		for (int j = 0;j < cfg_.MAPEDIT_HEIGHT;j++)
		{
			for (int i = 0;i < cfg_.MAPEDIT_WIDTH;i++)
			{
				int index;
				if (myMap_[j * cfg_.MAPEDIT_WIDTH + i] != -1)
				{
					index = mc->GetChipIndex(myMap_[j * cfg_.MAPEDIT_WIDTH + i]);
				}
				else
				{
					index = -1;
				}

				if (i == cfg_.MAPEDIT_WIDTH - 1)
				{
					openfile << index;
				}
				else
				{
					openfile << index << ',';
				}
			}
			openfile << std::endl;
		}
		printfDx("file Save\n");
		openfile.close();

	}
	else
	{
		//ファイルの選択がキャンセル
		printfDx("セーブがキャンセル\n");
	}

	//std::ofstream file("data.dat");

}

void MapEdit::LoadMapData()
{
	//ファイル選択ダイアロoグ
	TCHAR filename[255] = "";
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(ofn);
	//ウィンドウのオーナー＝親ウィンドウのハンドル
	ofn.hwndOwner = GetMainWindowHandle();
	ofn.lpstrFilter = "全てのファイル (*.*)\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 255;
	//ofn.Flags = OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn))
	{
		printfDx("ファイルが選択された\n");
		//ファイルを開いて、ロード
		std::ifstream inputfile(filename);
		std::string line;

		MapChip* mc = FindGameObject<MapChip>();
		myMap_.clear();
		while (std::getline(inputfile, line))
		{
			//空欄をスキップ
			if (line.empty())
			{
				continue;
			}

			//printfDx("%s\n", line.c_str());
			//読み込み処理
			if (line[0] != '#')
			{
				std::istringstream iss(line);
				std::string tmp;//これに1個ずつ読み込む
				while (std::getline(iss, tmp, ','))
				{
					//if (tmp == -1)
					//{
					//	myMap_.push_back(-1);
					//}
					//else
					//{
					//	myMap_.push_back(mc->GetHandle(tmp));//マップにハンドルにセット
					//}
					printfDx("%s ", tmp.c_str());
					if (tmp == "-1")
					{
						myMap_.push_back(-1);
					}
					else
					{
						int index = std::stoi(tmp);
						int handle = mc->GetHandle(index);
						myMap_.push_back(handle);
					}
				}
				printfDx("\n");
			}
			//{
			//	MessageBox(nullptr, "ファイル形式が違います", "読み込みエラー", MB_OK | MB_ICONWARNING);
			//}

		}
		printfDx("file Load\n");

	}
	else
	{
		//ファイルの選択がキャンセル
		printfDx("ロードがキャンセル\n");
	}

	//std::ofstream file("data.dat");

}
