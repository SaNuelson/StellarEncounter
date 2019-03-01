#pragma once
#include "stdlibs.h"

namespace Constants {

	enum WindowState { Initializing, Menu, Battle, Quitting};
	enum BattleState { Starting, PlayerTurn, EnemyTurn, PlayerWin, EnemyWin };

	static int xTileSize = 80;
	static int yTileSize = 64;

	static std::string level1 = "111101111_10111101_001111100_10111101_111101111";
	
	static SDL_Texture * GetTextureFromChar(char c);

}
