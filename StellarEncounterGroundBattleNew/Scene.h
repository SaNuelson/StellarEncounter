#pragma once
#include "stdlib.h"
#include "ResourceManager.h"
#include "Tilemap.h"
#include "UnitActionBlock.h"
#include "UnitInfoBlock.h"
#include "GameObject.h"
#include "Unit.h"
#include "Item.h"

class Scene {
public:

	Scene();
	~Scene() {};

	void StartDemo1();

	void ResolveInput(SDL_Event& e);
	void OnUpdate(double delta);
	void OnRender();

	bool IsPlayerTurn();

	Unit * GetCurrentUnit();

	std::vector<Unit*> units;
	int currentUnit = 0;

	std::vector<Item*> items;

	BoxTileMap tilemap;

	UnitInfoBlock infoblock;
	UnitActionBlock actionblock;


};

class GroundBattleScene : Scene {



};