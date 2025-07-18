#pragma once
struct MapEditConfig
{
	int TITLE_PIX_SIZE;
	int MAPEDIT_WIDTH;
	int MAPEDIT_HEIGHT;
	int MARGIN_X;
	int MARGIN_Y;
};

const MapEditConfig& GetMapEditConfig();
