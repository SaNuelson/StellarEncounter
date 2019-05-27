#pragma once
#include "stdlib.h"
#include "ResourceManager.h"
#include "Constants.h"

class TileMap;
class GameObject;

// part of tilemap. Is struct by itself for easier interaction
struct Tile {

public:

	Tile(std::string source, SDL_Point position, SDL_Point mappos, TileMap* tilemap);

	// an unfortunate solution to hold so many pointers in each tile, but it works well and IMHO enables much less messy code
	void SetNeighbors(Tile* up_left, Tile* up_right, Tile* right, Tile* down_right, Tile* down_left, Tile* left);

	GameObject* GetOccupant();
	void SetOccupant(GameObject* obj);

	void OnUpdate();
	void OnRender();

	// render units after OnRender to avoid overlapping
	void AfterRender(); 

	// called by units to render standing in the middle of their tile
	SDL_Point GetCenter();

	TileMap* tilemap;

	Tile* tile_up_left = nullptr;
	Tile* tile_up_right = nullptr;
	Tile* tile_left = nullptr;
	Tile* tile_right = nullptr;
	Tile* tile_down_right = nullptr;
	Tile* tile_down_left = nullptr;

	// exact pixel position for rendering
	SDL_Rect pos;

	// indexes in tilemap for easy access
	SDL_Point mappos;

	GameObject * occ;
	SDL_Texture * tex;

};