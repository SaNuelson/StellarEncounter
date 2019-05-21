#ifndef SE_CONSTANTS
#define SE_CONSTANTS

#include "stdlib.h"

using big = int16_t;
using small = int8_t;

// RETCODES

const Sint32 RC_NEW_GAME = 1;
const Sint32 RC_OPTIONS = 2;
const Sint32 RC_QUIT_GAME = 3;

const Sint32 RC_UNIT_STAT_CHANGE = 4;
const Sint32 RC_UNIT_DEATH = 5;

// RENDER CODES

const small UNIT_ACTION_IDLE = 0;
const small UNIT_ACTION_MOVE = 1;
const small UNIT_ACTION_ATTACK = 2;
const small UNIT_ACTION_HIT = 3;
const small UNIT_ACTION_REACT = 4;
const small UNIT_ACTION_DYING = 5;
const small UNIT_ACTION_DEAD = 6;

const int ActionsSize = 7;
const std::string Actions[ActionsSize] = { "Idle","Move","Attack","Hit","React","Dying","Dead" };

// DEMO UNITS

const std::string skeleton_source = "HP=100,MaxSP=30,CurSP=15,AP=6,Name=Lord Farquad,Weapon=50,TextureSpeed=200,Textures=Graphics/GameObjects/Skeleton";
const std::string hero_source = "HP=80,SP=20,AP=8,Name=A Little Humble Hero,Weapon=100,TextureSpeed=200,Textures=Graphics/GameObjects/Hero";

// CUSTOM DATA TYPES

enum Direction {
	UpRight = 0,
	Right = 1,
	DownRight = 2,
	DownLeft = 3,
	Left = 4,
	UpLeft = 5
};

// WINDOW INFO

const int scr_height = 768;
const int scr_width = 1280;

const int xTileSize = 80;
const int yTileSize = 64;
const int yTileBoxSize = 32;
const int yTileTopSize = 16;
const int TileSize = 64;

const int xMargin = 50;
const int yMargin = 50;

// TILE RENDERING OPTIONS

typedef std::bitset<8> TileRenderFlag;
const TileRenderFlag TILE_DEFAULT = 1;
const TileRenderFlag TILE_HOVER =	2;
const TileRenderFlag TILE_MOVE =	4;
const TileRenderFlag TILE_RUN =		8;
const TileRenderFlag TILE_ATTACK =	16;

#pragma region CONST LAYOUT

// EDITABLE SECTION
const int SET_STACK_BLOCK_WIDTH = 400;
const int SET_STACK_BLOCK_BLOCK_HEIGHT = 200;
const int SET_STACK_BLOCK_X_MARGIN = 20;
const int SET_STACK_BLOCK_Y_MARGIN = 20;
const int SET_STACK_BLOCK_BLOCK_X_MARGIN = 10;
const int SET_STACK_BLOCK_BLOCK_Y_MARGIN = 10;
const int SET_STACK_BLOCK_INTERBAR_Y_MARGIN = 0;

// SEMI-EDITABLE SECTION
const int SET_STACK_BLOCK_BLOCK_ROW_COUNT = 4;

// CALCULATED SECTION
const int STACK_BLOCK_W = SET_STACK_BLOCK_WIDTH;
const int STACK_BLOCK_X = scr_width - STACK_BLOCK_W;
const int STACK_BLOCK_Y = 0;
const int STACK_BLOCK_H = scr_height;

const int STACK_BLOCK_MARGIN_X = SET_STACK_BLOCK_X_MARGIN;
const int STACK_BLOCK_MARGIN_Y = SET_STACK_BLOCK_Y_MARGIN;

const int STACK_BLOCK_BLOCK_MARGIN_X = SET_STACK_BLOCK_BLOCK_X_MARGIN;
const int STACK_BLOCK_BLOCK_MARGIN_Y = SET_STACK_BLOCK_BLOCK_Y_MARGIN;

const int STACK_BLOCK_BLOCK_W = STACK_BLOCK_W - 2 * STACK_BLOCK_MARGIN_X;
const int STACK_BLOCK_BLOCK_H = SET_STACK_BLOCK_BLOCK_HEIGHT;
const int STACK_BLOCK_BLOCK_X = STACK_BLOCK_X + STACK_BLOCK_MARGIN_X;
const int STACK_BLOCK_BLOCK_Y = STACK_BLOCK_Y + STACK_BLOCK_MARGIN_Y;

const int STACK_BLOCK_PORTRAIT_X = STACK_BLOCK_BLOCK_X + STACK_BLOCK_BLOCK_MARGIN_X;
const int STACK_BLOCK_PORTRAIT_Y = STACK_BLOCK_BLOCK_Y + STACK_BLOCK_BLOCK_MARGIN_Y;
const int STACK_BLOCK_PORTRAIT_H = STACK_BLOCK_BLOCK_H - 2 * STACK_BLOCK_BLOCK_MARGIN_Y;
const int STACK_BLOCK_PORTRAIT_W = STACK_BLOCK_PORTRAIT_H;

const int STACK_BLOCK_NAME_X = STACK_BLOCK_PORTRAIT_X + STACK_BLOCK_PORTRAIT_W + STACK_BLOCK_BLOCK_MARGIN_X;
const int STACK_BLOCK_NAME_Y = STACK_BLOCK_BLOCK_Y + STACK_BLOCK_BLOCK_MARGIN_Y;
const int STACK_BLOCK_NAME_W = STACK_BLOCK_BLOCK_X + STACK_BLOCK_BLOCK_W - 2 * STACK_BLOCK_BLOCK_MARGIN_X - STACK_BLOCK_PORTRAIT_X - STACK_BLOCK_PORTRAIT_W;
const int STACK_BLOCK_NAME_H = ( STACK_BLOCK_BLOCK_H - ( SET_STACK_BLOCK_BLOCK_ROW_COUNT - 1 ) * SET_STACK_BLOCK_INTERBAR_Y_MARGIN - 2 * STACK_BLOCK_BLOCK_MARGIN_Y ) / SET_STACK_BLOCK_BLOCK_ROW_COUNT;

const int STACK_BLOCK_NAME_CENTER_X = STACK_BLOCK_NAME_X + STACK_BLOCK_NAME_W / 2;
const int STACK_BLOCK_NAME_CENTER_Y = STACK_BLOCK_NAME_Y + STACK_BLOCK_NAME_H / 2;

const int STACK_BLOCK_BAR_X = STACK_BLOCK_NAME_X;
const int STACK_BLOCK_HP_BAR_Y = STACK_BLOCK_NAME_Y + STACK_BLOCK_NAME_H + SET_STACK_BLOCK_INTERBAR_Y_MARGIN;
const int STACK_BLOCK_SP_BAR_Y = STACK_BLOCK_HP_BAR_Y + STACK_BLOCK_NAME_H + SET_STACK_BLOCK_INTERBAR_Y_MARGIN;
const int STACK_BLOCK_AP_BAR_Y = STACK_BLOCK_SP_BAR_Y + STACK_BLOCK_NAME_H + SET_STACK_BLOCK_INTERBAR_Y_MARGIN;
const int STACK_BLOCK_BAR_W = STACK_BLOCK_NAME_W;
const int STACK_BLOCK_BAR_H = STACK_BLOCK_NAME_H;

const int STACK_BLOCK_ATTACK_BAR_X = STACK_BLOCK_BAR_X;
const int STACK_BLOCK_ATTACK_BAR_Y = STACK_BLOCK_AP_BAR_Y + STACK_BLOCK_NAME_H + SET_STACK_BLOCK_INTERBAR_Y_MARGIN;
const int STACK_BLOCK_ATTACK_BAR_W = STACK_BLOCK_BAR_W;
const int STACK_BLOCK_ATTACK_BAR_H = STACK_BLOCK_BAR_H;

const int STACK_BLOCK_SHIFT_Y = STACK_BLOCK_BLOCK_H + STACK_BLOCK_MARGIN_Y;

#pragma endregion

// SDL_Color Generator
static SDL_Color GetColor(std::string color_name) {
	// Red, Green, Blue, Purple, Yellow, Cyan, Grey, White, Brown, Pink, Black
	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	if (color_name == "Red") {
		color.r = 255;
		return color;
	}
	else if (color_name == "Green") {
		color.g = 255;
		return color;
	}
	else if (color_name == "Blue") {
		color.b = 255;
		return color;
	}
	else if (color_name == "Purple") {
		color.r = 255;
		color.b = 255;
		return color;
	}
	else if (color_name == "Yellow") {
		color.r = 255;
		color.g = 255;
		return color;
	}
	else if (color_name == "Cyan") {
		color.g = 255;
		color.b = 255;
		return color;
	}
	else if (color_name == "Grey") {
		color.r = 128;
		color.g = 128;
		color.b = 128;
		return color;
	}
	else if (color_name == "White") {
		color.r = 255;
		color.g = 255;
		color.b = 255;
		return color;
	}
	else if (color_name == "Brown") {
		color.r = 128;
		color.g = 64;
		return color;
	}
	else if (color_name == "Pink") {
		color.r = 255;
		color.b = 128;
		return color;
	}
	return color;
}

// MAP DATA

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

static std::string level1tilemap = "00000000,300000003,02112220,021111120,01111110,021111120,02221120,300000003,00000000";
static std::string level1BoxTilemap = "300000003,021112220,021111120,011111110,021111120,022221120,300000003";

static std::string GetTileCodePath(int tileCode) {
	switch (tileCode) {
	case 0:
		return "Graphics/Tiles/t1.png";
	case 1:
		return "Graphics/Tiles/t5.png";
	case 2:
		return "Graphics/Tiles/t4.png";
	case 3:
		return "Graphics/Tiles/t8.png";
	default:
		return "";
	}
}


void ReadConsole() {
	// load line from console into vector of args
	std::string input;
	std::getline(std::cin, input);
	std::vector<std::string> args;
	std::stringstream ss(input);
	std::string data;
	while (std::getline(ss, data)) {
		args.push_back(data);
	}

	if (args[0] == "help" || args[0] == "h") {
		std::cout << "  CONSOLE COMMAND (FOR DEBUG) HELP" << std::endl;
		std::cout << "    ----    ----    ----    ----" << std::endl;
		std::cout << "make/create item/unit <tx> <ty> <src_string>" << std::endl;
		std::cout << "remove/delete item/unit <tx> <ty>" << std::endl;
		std::cout << "move item/unit <from_tx> <from_ty> <to_tx> <to_ty>" << std::endl;
		std::cout << "edit item/unit <tx> <ty> <src_string>" << std::endl;
		std::cout << "EXAMPLE: " << std::endl;
		std::cout << "make unit 3 3 HP=10,SP=5,Name=Big Little Joe";
		std::cout << "    ----    ----    ----    ----" << std::endl;
	}
	// new item/unit
	// "make/create item/unit <tx> <ty> <src_string>"
	else if (args[0] == "create" || args[0] == "make") {
		if (args[1] == "item") {

		}
		else if (args[1] == "unit") {

		}
		else {
			std::cout << "Invalid arguments for create at 1: " << args[1] << std::endl;
		}
	}
	// delete item/unit
	// "delete item/unit <tx> <ty>"
	else if (args[0] == "remove" || args[0] == "delete") {
		if (args[1] == "item") {

		}
		else if (args[1] == "unit") {

		}
		else {
			std::cout << "Invalid arguments for remove at 1: " << args[1] << std::endl;
		}
	}
	// move item/unit
	// "move item/unit <from_tx> <from_ty> <to_tx> <to_ty>"
	else if (args[0] == "move") {
		if (args[1] == "item") {

		}
		else if (args[1] == "unit") {

		}
		else {
			std::cout << "Invalid arguments for move at 1: " << args[1] << std::endl;
		}
	}
	// edit item/unit
	// "edit item/unit <tx> <ty> <src_string>"
	else if (args[0] == "edit") {
		if (args[1] == "item") {

		}
		else if (args[1] == "unit") {

		}
		else {
			std::cout << "Invalid arguments for edit at 1: " << args[1] << std::endl;
		}
	}
	else {
		std::cout << "Invalid argument at 0: " << args[0] << std::endl;
	}
}

#endif