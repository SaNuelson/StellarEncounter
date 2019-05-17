#ifndef SE_CONSTANTS
#define SE_CONSTANTS

#include "stdlib.h"

// RETCODES

Sint32 RC_NEW_GAME = 1;
Sint32 RC_OPTIONS = 2;
Sint32 RC_QUIT_GAME = 3;

// CUSTOM DATA TYPES

enum Attribute {

};

enum Direction {
	UpRight = 0,
	Right = 1,
	DownRight = 2,
	DownLeft = 3,
	Left = 4,
	UpLeft = 5
};

using big = int16_t;
using small = int8_t;

// WINDOW INFO

int scr_height = 768;
int scr_width = 1280;

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

static std::string level1 = "a,HP=100,AP=5,ATTACK=10;b,HP=70,AP=3,ATTACK=25;300000003,02112220,0211111a20,01111110,021111120,022211b20,300000003;";

static std::string level1tilemap = "00000000,300000003,02112220,021111120,01111110,021111120,02221120,300000003,00000000";
static std::string level1BoxTilemap = "300000003,021112220,021111120,011111110,021111120,022221120,300000003";

static std::string GetLevelInfo(int level) {
	switch (level) {
	case 1:
		return level1;
	default:
		return "";
	}
}

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

#endif