#pragma once
struct MapChipConfig
{
	int TITLE_PIX_SIZE;
	int TILES_X;
	int TILES_Y;
	int MAPCHIP_VIEW_X;
	int MAPCHIP_VIEW_Y;
	int MAPCHIP_WIN_WIDTH;
	int MAPCHIP_WIN_HEIGHT;
};

const MapChipConfig& GetMapChipConfig();
