#ifndef SE_CONSTANTS
#define SE_CONSTANTS

#include "stdlibs.h"

namespace Constants {

	enum WindowState { Initializing, MainMenu, NewGameMenu, LoadGameMenu, OptionsMenu, WorldMap, Battle, Quitting};
	enum BattleState { Starting, PlayerTurn, EnemyTurn, PlayerWin, EnemyWin };
	enum ButtonState { Idle, Focused, Clicked };
	enum EVENT_TYPE {
		None = 0,
		HealEntity = 1, 
		DamageEntity = 2 
	};
	enum ButtonType { NewGame, LoadGame, Options, Quit };

	static int WinWidth = 1024;
	static int WinHeight = 768;

	static int BtnWidth = 200;
	static int BtnHeight = 50;
	static int BtnOffset = 20;

	static int xTileSize = 80;
	static int yTileSize = 64;
	static int yTileBoxSize = 32;
	static int yTileTopSize = 16;

	static int xMargin = 50;
	static int yMargin = 50;
	
	static std::vector<std::string> GetTileTextures() {

		std::vector<std::string> ret;
		ret.push_back("Graphics/Tile1.png");
		ret.push_back("Graphics/Tile2.png");
		// ...
		return ret;

	}

	static std::vector<std::string> GetCharacterTextures() {

		std::vector<std::string> ret;
		ret.push_back("Graphics/Char1.png");
		ret.push_back("Graphics/Char2.png");
		// ...
		return ret;
	}

	static std::vector<std::string> GetFontTextures() {
		std::vector<std::string> ret;
		ret.push_back("Resources/Raleway_Medium.ttf");
		// ...
		return ret;
	}

	/*
	level string composition:
	- units:
		- indicated with letter after the tile on which they stand. at the start of file, letter is defined after it by all components with needed values
		unit format:
			<LETTER>,<COMPONENT>(<VALUE>,<VALUE>, ... ) + <LETTER> ... delimiter(,) end of section(;)
	- terrain:
		0 - water/canyon (unpassable, passable with flying, standable with flying)
		1 - solid land (passable, standable)
		2 - hill/mountain (passable with flying, unstandable)
		3 - void (unpassable,unstandable,no tile)
		, - end of line in tilemap
		; - end of section
	- flags:
		- for now no flags, in future enviromental flags such as storm, enviromental hazard (falling rocks, apocalypse...)
		- indicated after unit specification section:
			<FLAG_NAME>+ or <FLAG_NAME>- delimiter(,) end of section(;)
	- ps
		- all levels are indicated only by the composition above. Any additional settings will be later implemented. Currently only terrain basis is set, EntityManager afterwards assembles the terrain
		using biome specific terrain cells.
	*/

	static std::string level1 = "a,HP=100,AP=5,ATTACK=10;b,HP=70,AP=3,ATTACK=25;300000003,02112220,0211111a20,01111110,021111120,022211b20,300000003;";

	static std::string GetLevelInfo(int level) {
		switch (level) {
		case 1:
			return level1;
		default:
			return "";
		}
	}
}

#endif