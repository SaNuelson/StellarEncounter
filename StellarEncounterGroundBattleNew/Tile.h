#pragma once
#include "stdlib.h"
#include "ResourceManager.h"
#include "Constants.h"

class BoxTileMap;
class GameObject;

class BoxTile {

public:

	static void Init();

	BoxTile(std::string source, SDL_Point position, BoxTileMap* tilemap);

	GameObject* GetOccupant();
	void SetOccupant(GameObject* obj);

	void OnUpdate();
	void OnRender();

	void SetState(TileRenderFlag flag);

	SDL_Point GetCenter();

	BoxTileMap* tilemap;

	// keeping current state of tile (hovered, moveable, adjacent_to_enemy... all updated it Tilemap::OnUpdate
	TileRenderFlag state;

	SDL_Texture* tex_default;
	static SDL_Texture* tex_move;
	static SDL_Texture* tex_run;
	static SDL_Texture* tex_hover;
	static SDL_Texture* tex_attack;

	SDL_Rect pos;
	GameObject * occ;

	// static for debug
	const std::string src_move = "Graphics/txmove.png";
	const std::string src_run = "Graphics/txrun.png";
	const std::string src_hover = "Graphics/txhover.png";

};