#include "MapChipConfig.h"
#include <Windows.h>
#include <string>

MapChipConfig& LoadMapChipConfig(const std::string& iniPath)
{
	MapChipConfig cfg;
	cfg.TITLE_PIX_SIZE = GetPrivateProfileInt("MapChip", "TITLE_SIZE", 255,iniPath.c_str());
	cfg.TILES_X = GetPrivateProfileInt("MapChip", "TILES_X", 255, iniPath.c_str());
	cfg.TILES_Y = GetPrivateProfileInt("MapChip", "TILES_Y", 255, iniPath.c_str());
	cfg.MAPCHIP_VIEW_X = GetPrivateProfileInt("MapChip", "VIEW_X", 255, iniPath.c_str());
	cfg.MAPCHIP_VIEW_Y = GetPrivateProfileInt("MapChip", "VIEW_Y", 255, iniPath.c_str());
	cfg.MAPCHIP_WIN_WIDTH = cfg.TITLE_PIX_SIZE * cfg.MAPCHIP_VIEW_X;
	cfg.MAPCHIP_WIN_HEIGHT = cfg.TITLE_PIX_SIZE * cfg.MAPCHIP_VIEW_Y;
	return cfg;
}
const MapChipConfig& GetMapChipConfig()
{
	static MapChipConfig config = LoadMapChipConfig(".\\myChipSetup.ini");
	return config;
}