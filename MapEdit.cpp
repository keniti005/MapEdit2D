#include <windows.h>
#include "MapEdit.h"
#include "MapChip.h"
#include "Input.h"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>

MapEdit::MapEdit()
	:GameObject(), myMap_(MAP_WIDTH* MAP_HEIGHT, -1),//�����l��-1��20*20
	isInMapEditArea_(false)
{
	mapEditRect_ = { LEFT_MARGIN,TOP_MARGIN,MAP_WIDTH * MAP_IMAGE_SIZE,MAP_HEIGHT * MAP_IMAGE_SIZE };
}

MapEdit::~MapEdit()
{
}

void MapEdit::SetMap(Point p, int value)
{
	//�}�b�v�̍��Wp��value���Z�b�g����
	//p���A�z��͈̔͊O�̎���assert�Ɉ���������
	assert(p.x >= 0 && p.x < MAP_WIDTH);
	assert(p.y >= 0 && p.y < MAP_HEIGHT);
	myMap_[p.y * MAP_WIDTH + p.x] = value;//y�sx���value���Z�b�g����
}

int MapEdit::GetMap(Point p) const
{
	//�}�b�v�̍��Wp�ɒl���Z�b�g����
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
	//�}�E�X�̍��W���}�b�v�G�f�B�^�̗̈���ɂ��邩
	isInMapEditArea_ = (mousePos.x >= mapEditRect_.x && mousePos.x <= mapEditRect_.x + mapEditRect_.w &&
		mousePos.y >= mapEditRect_.y && mousePos.y <= mapEditRect_.y + mapEditRect_.h);

	if (!isInMapEditArea_)//�}�b�v�G�f�B�^�̈�O�͉������Ȃ�
	{
		return;
	}
	int gridX = (mousePos.x - LEFT_MARGIN) / MAP_IMAGE_SIZE;
	int gridY = (mousePos.y - TOP_MARGIN) / MAP_IMAGE_SIZE;

	drawAreaRect_ = {LEFT_MARGIN + gridX * MAP_IMAGE_SIZE,TOP_MARGIN + gridY * MAP_IMAGE_SIZE,
	MAP_IMAGE_SIZE,MAP_IMAGE_SIZE};

	if (Input::IsButtonKeep(MOUSE_INPUT_LEFT))
	{
		MapChip* mapChip = FindGameObject<MapChip>();

		if (mapChip && mapChip->IsHold())//�}�b�v�`�b�v�������Ă���
		{
			SetMap({ gridX,gridY }, mapChip->GetHoldImage());
		}
		//���V�t�g�������Ă����ԂŃ}�b�v�`�b�v���폜
		//if (Input::IsKeepKeyDown(KEY_INPUT_LSHIFT))
		//{
		//	;
		//}
	}

	if (Input::IsKeyDown(KEY_INPUT_S))
	{
		SaveMapData();
	}
}

void MapEdit::Draw()
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			int value = GetMap({ i,j });
			if (value != -1)
			{
				DrawGraph(LEFT_MARGIN + i * MAP_IMAGE_SIZE, TOP_MARGIN + j * MAP_IMAGE_SIZE, value, TRUE);
			}
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(LEFT_MARGIN, TOP_MARGIN, MAP_WIDTH * MAP_IMAGE_SIZE + LEFT_MARGIN, MAP_HEIGHT * MAP_IMAGE_SIZE + TOP_MARGIN, GetColor(255, 255, 255), FALSE, 5);
	for (int i = 0; i < MAP_WIDTH;i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			DrawLine(MAP_IMAGE_SIZE * i + LEFT_MARGIN, TOP_MARGIN, MAP_IMAGE_SIZE * i + LEFT_MARGIN, MAP_HEIGHT * MAP_IMAGE_SIZE + TOP_MARGIN, GetColor(255, 255, 255), 1);
			DrawLine(LEFT_MARGIN, MAP_IMAGE_SIZE * j + TOP_MARGIN, MAP_WIDTH * MAP_IMAGE_SIZE + LEFT_MARGIN, MAP_IMAGE_SIZE * j + TOP_MARGIN, GetColor(255, 255, 255), 1);
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
	//�t�@�C���I���_�C�A���O
	TCHAR filename[255] = "";
	OPENFILENAME ofn = {0};

	ofn.lStructSize = sizeof(ofn);
	//�E�B���h�E�̃I�[�i�[���e�E�B���h�E�̃n���h��
	ofn.hwndOwner = GetMainWindowHandle();
	ofn.lpstrFilter = "�S�Ẵt�@�C�� (*.*)\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 255;
	ofn.Flags = OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn))
	{
		printfDx("�t�@�C�����I�����ꂽ\n");
		//�t�@�C�����J���āA�Z�[�u
		std::ofstream openfile(filename);
		openfile << "#header" << std::endl
			<< "WIDTH " << MAP_WIDTH << std::endl
			<< "HEIGHT " << MAP_HEIGHT << std::endl << std::endl;
		openfile << "#data" << std::endl;
		MapChip* mc = FindGameObject<MapChip>();

		//for (auto& itr : myMap_)
		//{
		//	file << itr << std::endl;
		//}
		for (int j = 0;j < MAP_HEIGHT;j++)
		{
			for (int i = 0;i < MAP_WIDTH;i++)
			{
				int index;
				if (myMap_[j * MAP_WIDTH + i] != -1)
				{
					index = mc->GetChipIndex(myMap_[j * MAP_WIDTH + i]);
				}
				else
				{
					index = -1;
				}
				openfile << index << " ";
			}
			openfile << std::endl;
		}
		printfDx("file Save\n");
		openfile.close();

	}
	else
	{
		//�t�@�C���̑I�����L�����Z��
		printfDx("�Z�[�u���L�����Z��\n");
	}

	//std::ofstream file("data.dat");

}

void MapEdit::LoadMapData()
{
	//�t�@�C���I���_�C�A���O
	TCHAR filename[255] = "";
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(ofn);
	//�E�B���h�E�̃I�[�i�[���e�E�B���h�E�̃n���h��
	ofn.hwndOwner = GetMainWindowHandle();
	ofn.lpstrFilter = "�S�Ẵt�@�C�� (*.*)\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 255;
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetSaveFileName(&ofn))
	{
		printfDx("�t�@�C�����I�����ꂽ\n");
		//�t�@�C�����J���āA���[�h
		std::ofstream openfile(filename);
		MapChip* mc = FindGameObject<MapChip>();

		//for (auto& itr : myMap_)
		//{
		//	file << itr << std::endl;
		//}
		for (int j = 0;j < MAP_HEIGHT;j++)
		{
			for (int i = 0;i < MAP_WIDTH;i++)
			{
				int index;
				if (myMap_[j * MAP_WIDTH + i] != -1)
				{
					index = mc->GetChipIndex(myMap_[j * MAP_WIDTH + i]);
				}
				else
				{
					index = -1;
				}
				openfile << index << " ";
			}
			openfile << std::endl;
		}
		printfDx("file Load\n");
		openfile.close();

	}
	else
	{
		//�t�@�C���̑I�����L�����Z��
		printfDx("���[�h���L�����Z��\n");
	}

	//std::ofstream file("data.dat");

}
