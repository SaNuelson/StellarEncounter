#pragma once
#include "stdlib.h"
#include "ResourceManager.h"
#include "Constants.h"

class GameObject;
class Item;
class Unit;
class BoxTileMap;

class UnitInfoBlock {
public:

	UnitInfoBlock() {};
	UnitInfoBlock(BoxTileMap* tilemap);
	~UnitInfoBlock() {};

	void OnUpdate(double delta);;

	void OnRender();

private:

	// logic
	BoxTileMap* tilemap;
	Unit* currentUnit;


	// render
	SDL_Renderer* ren;

	SDL_Texture* block_tex;
	SDL_Rect block_rect;

	SDL_Texture* portrait_tex;
	SDL_Rect portrait_rect;
	
	SDL_Texture* hp_tex;
	SDL_Rect hp_rect;
	SDL_Rect curr_hp_rect;

	SDL_Texture* sp_tex;
	SDL_Rect sp_rect;
	SDL_Rect curr_sp_rect;

	SDL_Texture* ap_tex;
	SDL_Rect ap_rect;
	SDL_Rect curr_ap_rect;

	SDL_Texture* emptybar_tex;
	int max_bar_w;

};