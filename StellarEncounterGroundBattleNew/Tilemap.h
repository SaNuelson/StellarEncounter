#pragma once
#include "stdlib.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "GameObject.h"
#include "Unit.h"
#include "Item.h"
#include "Tile.h"

class GroundBattleScene;

class TileMap
{
public:

	TileMap(GroundBattleScene*scene) : scene(scene) {};

	~TileMap() {};

	// set up tilemap from source
	void Init(std::string source, int x, int y);
	void PutOnTile(GameObject* obj, Tile* tile);
	void PutOnTile(GameObject* obj, int x, int y);
	
	void ResolveInput(SDL_Event &e);
	void OnUpdate(double delta);
	void OnRender();

	Tile* GetTile(int x, int y) { return &tiles[y][x]; }

	//int GetDistance(SDL_Point &p1, SDL_Point &p2);
	//int GetDistance(int &tx1, int &tx2, int &ty1, int &ty2);
	int GetDistance(Tile* t1, Tile* t2);

	bool CanMove(Tile* tile);
	bool CanAttack(Unit* unit, Tile* tile);

	bool CanMoveHere(Tile* tile);

	GroundBattleScene * scene;

private:

	// for now tile textures will be held in resourcemanager, tilemap will ask on render for these tiles, later they should be loaded once, then blitted on a uniform surface

	std::vector<std::vector<Tile>> tiles;

	SDL_Point start_pt;

};

/* TileMap

class TileMap
{
public:

	TileMap(GroundBattleScene*scene) : scene(scene) {};

	~TileMap() {};

	// set up tilemap from source
	void Init(std::string source, int x, int y);

	void ResolveInput(SDL_Event &e);
	void OnUpdate(double delta);
	void OnRender();

	Tile* GetTile(int x, int y) { return &tiles[y][x]; }

	//int GetDistance(SDL_Point &p1, SDL_Point &p2);
	//int GetDistance(int &tx1, int &tx2, int &ty1, int &ty2);
	int GetDistance(Tile* t1, Tile* t2);

	bool CanMove(Unit* unit, Tile* tile);
	bool CanAttack(Unit* unit, Tile* tile);

	bool CanMoveHere(Tile* tile);

	GroundBattleScene * scene;

private:

	// for now tile textures will be held in resourcemanager, tilemap will ask on render for these tiles, later they should be loaded once, then blitted on a uniform surface

	std::vector<std::vector<Tile>> tiles;

	SDL_Point start_pt;

	SDL_Texture* hoverTileTex;
	bool hover;
	int xt = -1;
	int yt = -1;
	int oxt = -1;
	int oyt = -1;

	SDL_Texture* moveTileTex;
	SDL_Texture* runTileTex;

};
*/