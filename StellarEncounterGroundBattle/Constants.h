#pragma once
#include "stdlibs.h"

namespace Constants {

	enum WindowState { Initializing, Menu, Battle, Quitting};
	enum BattleState { Starting, PlayerTurn, EnemyTurn, PlayerWin, EnemyWin };

	static int xTileSize = 80;
	static int yTileSize = 64;

	static int xMargin = 50;
	static int yMargin = 50;

	static std::string level1 = "111101111_10111101_001111100_10111101_111101111";
	
	static std::vector<std::string> GetTileTextures() {

		std::vector<std::string> ret;
		ret.push_back("Graphics/Tile1.png");
		ret.push_back("Graphics/Tile2.png");

		return ret;

	}

	static std::vector<std::string> GetCharacterTextures() {

		std::vector<std::string> ret;
		ret.push_back("Graphics/Char1.png");
		ret.push_back("Graphics/Char2.png");

		return ret;
	}

}
