#ifndef SE_CONSTANTS
#define SE_CONSTANTS

#include "stdlib.h"

// Global variables, mostly for debugging etc.
bool Global_show_tilenums = false;

// Constants are just a big mess of constants and misc functions for easier readability and writing of code

// CUSTOM DATA ALIASES

using big = int16_t;
using small = int8_t; // both used in Unit HP/SP/AP... meant to save some space, but I doubt it really makes any considerable difference
enum Direction {
	UpRight = 0,
	Right = 1,
	DownRight = 2,
	DownLeft = 3,
	Left = 4,
	UpLeft = 5
};	// for easily passing directions when moving units

// RETCODES

// these are meant as retcodes for SDL_Events as well as different scene indicators
const Sint32 RC_NEW_GAME = 1;
const Sint32 RC_OPTIONS = 2;
const Sint32 RC_BACK = 3;
const Sint32 RC_MAIN_MENU = 6;
const Sint32 RC_QUIT = 7;

const Sint32 RC_TEAM_0_WIN = 8;
const Sint32 RC_TEAM_1_WIN = 9;

const Sint32 RC_INGAME_MENU_SHOW = 10;
const Sint32 RC_PAUSE_GAME = 11;
const Sint32 RC_RESUME_GAME = 12;

// I learned way too late how useful and suprisingly easy it is to implement custom events, these are used for communication between independent parts of program
// and they work really well
const Sint32 RC_UNIT_STAT_CHANGE = 4; // on change of HP/SP/AP of unit, this code is read by UnitStackBlock to update specific unit ((void*) e.user.data1 = changed_unit)
const Sint32 RC_UNIT_DEATH = 5; // similarly, it is also read by GrounBattleScene to check for EndGame


// UNIT STATE CODES

const small UNIT_ACTION_NONE = -1;
const small UNIT_ACTION_IDLE = 0;
const small UNIT_ACTION_MOVE = 1;
const small UNIT_ACTION_ATTACK = 2;
const small UNIT_ACTION_HIT = 3;
const small UNIT_ACTION_DYING = 4;
const small UNIT_ACTION_DEAD = 5;

// these are used in source_str parsing when creating/editing units
const int ActionsSize = 7;
const std::string Actions[ActionsSize] = { "Idle","Move","Attack","Hit","Dying","Dead" };

// Resource hardcoded paths
const std::string PATH_BTN_IDLE = "Graphics/UI/button.png";
const std::string PATH_BTN_HOVER = "Graphics/UI/button_idle.png";
const std::string PATH_BTN_CLICK = "Graphics/UI/button_click.png"; 
const std::string PATH_SHADE = "Graphics/UI/unitinfoblockrect.png";
const std::string PATH_INGAME_MENU_RECT = "Graphics/UI/buttonhover.png";

// DEMO UNIT SOURCE STRINGS
// more on their composition in Unit::ParseSource()
const std::string skeleton_source = "HP=100,MaxSP=30,CurSP=15,AP=6,Name=Lord Farquad,Weapon=50,TextureSpeed=200,Textures=Graphics/GameObjects/Skeleton";
const std::string hero_source = "HP=80,SP=20,AP=8,Name=A Little Humble Hero,Weapon=100,TextureSpeed=200,Textures=Graphics/GameObjects/Hero";
const std::string wizard_source = "HP=50,SP=50,AP=6,Flip=true,Name=Soldier o' Fortune,Weapon=65,TextureSpeed=200,Textures=Graphics/GameObjects/LightSoldier";


// WINDOW INFO

const int scr_offset_x = 50;
const int scr_offset_y = 50;

const int scr_height = 768;
const int scr_width = 1280;

// tile dimensions for rendering etc. (eg. with disproportional hex tiles,every successive tile row is yTileTopSize + yTileBoxSize below the previous row)
const int xTileSize = 80;
const int yTileSize = 64;
const int yTileBoxSize = 32;
const int yTileTopSize = 16;
const int TileSize = 64;

// offests for tilemap in window
const int xMargin = 50;
const int yMargin = 50;


// UNIT STACK BLOCK LAYOUT CONSTANTS

#pragma region CONST LAYOUT

const int INGAME_MENU_WIDTH = 400;
const int INGAME_MENU_HEIGHT = 400;
const int INGAME_MENU_BTN_WIDTH = 300;
const int INGAME_MENU_BTN_HEIGHT = 120;
const int INGAME_MENU_SBTN_WIDTH = 120;
const int INGAME_MENU_SBTN_HEIGHT = 50;

// EDITABLE SECTION - whole stack block layout uses exclusively these values, by changing these, whole stack block adapts
const int SET_STACK_BLOCK_WIDTH = 400;
const int SET_STACK_BLOCK_BLOCK_HEIGHT = 100;
const int SET_STACK_BLOCK_X_MARGIN = 20;
const int SET_STACK_BLOCK_Y_MARGIN = 20;
const int SET_STACK_BLOCK_BLOCK_X_MARGIN = 10;
const int SET_STACK_BLOCK_BLOCK_Y_MARGIN = 10;
const int SET_STACK_BLOCK_INTERBAR_Y_MARGIN = 0;

// SEMI-EDITABLE SECTION - changing these values requires making according changed ( changing row count means removing / adding new elements to the stack block )
const int SET_STACK_BLOCK_BLOCK_ROW_COUNT = 4;

// CALCULATED SECTION - these values are all calulated based on the EDITABLE SECTION.
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
const int STACK_BLOCK_UNITS_VISIBLE = scr_height / (SET_STACK_BLOCK_BLOCK_HEIGHT + STACK_BLOCK_MARGIN_Y);

#pragma endregion

// MAP DATA

/*
level string composition:
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
	- all levels are indicated only by the composition above. Any additional settings will be later implemented. 
	Currently only terrain basis is set. Unit sources can be easily added to the mix at later time.
*/

static std::string level1tilemap = "00000000,300000003,02112220,021111120,01111110,021111120,02221120,300000003,00000000";

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

// MONOTONY - used in unit movement to ensure the units doesn't "jump over" the destination tile, more on that in the function itself
template <typename T>
bool isMonotonic(T a, T b, T c) {
	return ((a <= b) && (b <= c)) || ((a >= b) && (b >= c));
}
template <typename T>
bool isStrictlyMonotonic(T a, T b, T c) {
	return ((a < b) && (b < c) || (a > b) && (b > c));
}




// OBSOLETE CONSTANTS / FUNCTIONS


// TILE RENDERING OPTIONS - this was previously used in tiles. In the distant past where one could move by clicking on a tile, the tiles showed color tints based on flags.
// Blue tint meant "can go here", red tint "can attack enemy standing here". Later, this feature was left out for the sake of its creator's sanity.
// Thus, here lie remnants of the former idea.

typedef std::bitset<8> TileRenderFlag;
const TileRenderFlag TILE_DEFAULT = 1;
const TileRenderFlag TILE_HOVER = 2;
const TileRenderFlag TILE_MOVE = 4;
const TileRenderFlag TILE_RUN = 8;
const TileRenderFlag TILE_ATTACK = 16;

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


#endif