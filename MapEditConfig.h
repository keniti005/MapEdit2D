#pragma once
struct MapEditConfig
{
	int TITLE_PIX_SIZE;
	int MAPEDIT_WIDTH;
	int MAPEDIT_HEIGHT;
	int MARGIN_TOP;
	int MARGIN_LEFT;
};

const MapEditConfig& GetMapEditConfig();
