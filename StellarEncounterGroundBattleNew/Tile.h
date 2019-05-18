#pragma once
#include "stdlib.h"
#include "ResourceManager.h"
#include "Constants.h"

class TileMap;
class GameObject;

class Tile {

public:

	Tile(std::string source, SDL_Point position, SDL_Point mappos, TileMap* tilemap);

	void SetNeighbors(Tile* up_left, Tile* up_right, Tile* right, Tile* down_right, Tile* down_left, Tile* left);

	GameObject* GetOccupant();
	void SetOccupant(GameObject* obj);

	void OnUpdate();
	void OnRender();
	void AfterRender(); // render units after OnRender to avoid overlapping

	SDL_Point GetCenter();

	TileMap* tilemap;

	Tile* tile_up_left = nullptr;
	Tile* tile_up_right = nullptr;
	Tile* tile_left = nullptr;
	Tile* tile_right = nullptr;
	Tile* tile_down_right = nullptr;
	Tile* tile_down_left = nullptr;

	SDL_Rect pos;
	SDL_Point mappos;
	GameObject * occ;
	SDL_Texture * tex;

};

/*
class Tile {

public:

	static void Init();

	Tile(std::string source, SDL_Point position, SDL_Point mappos, TileMap* tilemap);

	void SetNeighbors(Tile* left, Tile* up, Tile* right, Tile* down);

	GameObject* GetOccupant();
	void SetOccupant(GameObject* obj);

	void OnUpdate();
	void OnRender();

	void AddState(TileRenderFlag flag);
	void SetState(TileRenderFlag flag);
	void DelState(TileRenderFlag flag);
	bool GetState(TileRenderFlag flag);

	SDL_Point GetCenter();

	TileMap* tilemap;

	// keeping current state of tile (hovered, moveable, adjacent_to_enemy... all updated it Tilemap::OnUpdate
	TileRenderFlag state;

	SDL_Texture* tex_default;
	static SDL_Texture* tex_move;
	static SDL_Texture* tex_run;
	static SDL_Texture* tex_hover;
	static SDL_Texture* tex_attack;

	Tile* tile_up = nullptr;
	Tile* tile_left = nullptr;
	Tile* tile_right = nullptr;
	Tile* tile_down = nullptr;

	SDL_Rect pos;
	SDL_Point mappos;
	GameObject * occ;

	// static for debug
	const std::string src_move = "Graphics/txmove.png";
	const std::string src_run = "Graphics/txrun.png";
	const std::string src_hover = "Graphics/txhover.png";

};
*/