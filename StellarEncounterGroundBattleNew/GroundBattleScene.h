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

	void StartDemo1();

	void ResolveInput(SDL_Event& e) override;
	void OnUpdate(double delta) override;
	void OnRender() override;

	bool CheckEndGame();

	bool UpKey = false;
	bool DownKey = false;

	TileMap tilemap;

	std::vector<Unit*> units;
	int currentUnit = 0;
	Unit * GetCurrentUnit();
	void EndTurn();

	std::vector<Item*> items;


	UnitActionBlock actionblock;
	UnitStackBlock stackblock;
};