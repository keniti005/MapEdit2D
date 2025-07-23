#include "MapEditConfig.h"
#include <Windows.h>
#include <string>

MapEditConfig& LoadMapEditConfig(const std::string& iniPath)
{
	MapEditConfig cfg;
	cfg.TITLE_PIX_SIZE = GetPrivateProfileInt("MapEdit", "TITLE_SIZE", 255, iniPath.c_str());
	cfg.MAPEDIT_WIDTH = GetPrivateProfileInt("MapEdit", "MAP_WIDTH", 255, iniPath.c_str());
	cfg.MAPEDIT_HEIGHT = GetPrivateProfileInt("MapEdit", "MAP_HEIGHT", 255, iniPath.c_str());
	cfg.MARGIN_TOP = GetPrivateProfileInt("MapEdit", "TOP_MARGIN", 255, iniPath.c_str());
	cfg.MARGIN_LEFT = GetPrivateProfileInt("MapEdit", "LEFT_MARGIN", 255, iniPath.c_str());
	return cfg;
}

const MapEditConfig& GetMapEditConfig()
{
	static MapEditConfig config = LoadMapEditConfig(".\\myEdtiSetup.ini");
	return config;
}