#pragma once
#include "stdlibs.h"

namespace Constants {

	enum WindowState { Initializing, Menu, Battle, Quitting};
	enum BattleState { Starting, PlayerTurn, EnemyTurn, PlayerWin, EnemyWin };

	static int xTileSize = 80;
	static int yTileSize = 64;

}
