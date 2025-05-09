#include "MapEdit.h"

MapEdit::MapEdit()
	:GameObject(), myMap_(MAP_WIDTH* MAP_HEIGHT, -1)
{
}

MapEdit::~MapEdit()
{
}

void MapEdit::Update()
{
}

void MapEdit::Draw()
{
	DrawBox(LEFT_MARGIN, TOP_MARGIN, MAP_WIDTH * MAP_IMAGE_SIZE + LEFT_MARGIN, MAP_HEIGHT * MAP_IMAGE_SIZE + TOP_MARGIN, GetColor(255, 255, 255), FALSE,5);
	for (int i = 0; i < MAP_WIDTH;i ++)
	{
		for (int j = 0; j < MAP_HEIGHT; j ++)
		{
			DrawLine(MAP_IMAGE_SIZE * i + LEFT_MARGIN, TOP_MARGIN, MAP_IMAGE_SIZE * i + LEFT_MARGIN, MAP_HEIGHT * MAP_IMAGE_SIZE + TOP_MARGIN, GetColor(255, 255, 255));
			DrawLine(LEFT_MARGIN, MAP_IMAGE_SIZE * j + TOP_MARGIN, MAP_WIDTH * MAP_IMAGE_SIZE + LEFT_MARGIN, MAP_IMAGE_SIZE * j + TOP_MARGIN, GetColor(255, 255, 255));
		}
	}
}
