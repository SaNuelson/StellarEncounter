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

	// used to move units (either when building map or when using console) and avoiding triggering methods or events that happen during in-game movement
	void PutOnTile(GameObject* obj, Tile* tile);
	void PutOnTile(GameObject* obj, int x, int y);
	
	void ResolveInput(SDL_Event& e) {} // for now no logic, later tiles could... well... do something on their own
	void OnUpdate(double delta);
	void OnRender();

	Tile* GetTile(int x, int y);

	// because currently units can move only 1 tile in any direction, this method returns fixed value. Could be expanded later for different tile types or movement over long distances
	int GetDistance(Tile* t1, Tile* t2);

	// return pixel vector between tiles, used in awfully complicated unit movement
	SDL_Point GetMoveVec(Tile* t1, Tile* t2);

	bool CanMove(Tile* tile);
	bool CanAttack(Unit* unit, Tile* tile);

private:

	std::vector<std::vector<Tile>> tiles;

	// left-top point of tilemap, important because of offset in window
	SDL_Point start_pt;

	GroundBattleScene* scene;

};