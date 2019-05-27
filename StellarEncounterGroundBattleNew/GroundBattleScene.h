#pragma once
#include "Scene.h"
#include "stdlib.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Unit.h"
#include "Item.h"
#include "UnitActionBlock.h"
#include "UnitStackBlock.h"
#include "Tilemap.h"

class GroundBattleScene : public Scene {
public:

	GroundBattleScene();

	// currently hardcoded demo with preset map and units
	void StartDemo1();

	void ResolveInput(SDL_Event& e) override;
	void OnUpdate(double delta) override;
	void OnRender() override;

	// check if both teams have living units, called after every unit death
	bool CheckEndGame();

	// getters/setters
	void AddUnit(Unit* unit);
	Unit* GetCurrentUnit();
	TileMap* GetTilemap() { return &tilemap; }

private:

	// used for moving diagonally... not left/right... because hexes...
	bool UpKey = false;
	bool DownKey = false;

	// tilemap is specific to GroundBattleScene and always at most one so I don't think it needs to be held in ResourceManager
	TileMap tilemap;

	std::vector<Unit*> units;
	int currentUnit = 0;

	// move to next unit, called only inside class
	void EndTurn();

	std::vector<Item*> items;

	// UnitActionBlock actionblock;	// unused because units don't have any special skills
	UnitStackBlock stackblock;

	// UnitStackBlock frequently loops through units, I don't know if this is the best solution...
	friend class UnitStackBlock;
};