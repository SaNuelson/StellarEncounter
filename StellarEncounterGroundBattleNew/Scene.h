#pragma once
#include "stdlib.h"

#include "ResourceManager.h"

#include "Tilemap.h"
#include "Unit.h"
#include "Item.h"

#include "UnitInfoBlock.h"
#include "UnitActionBlock.h"

class Scene {
public:

	Scene() {

		infoblock = UnitInfoBlock();
		actionblock = UnitActionBlock();

	}

	void StartDemo1() {

		tilemap.Init(level1boxtilemap, xTileSize, xTileSize); //debug

		units.push_back(ResourceManager::CreateUnit(100, 100, 5, &tilemap.tiles[1][2], "Graphics/Hero/idle1.png", &tilemap, true));
		units.push_back(ResourceManager::CreateUnit(100, 100, 5, &tilemap.tiles[4][3], "Graphics/Enemy1/idle1.png", &tilemap, false));
		units.push_back(ResourceManager::CreateUnit(100, 100, 5, &tilemap.tiles[4][4], "Graphics/Enemy2/idle1.png", &tilemap, false));
		units.push_back(ResourceManager::CreateUnit(100, 100, 5, &tilemap.tiles[4][2], "Graphics/Enemy3/idle1.png", &tilemap, false));

		items.push_back(ResourceManager::CreateItem("Graphics/box.png", &tilemap.tiles[3][4], &tilemap, false));
		items.push_back(ResourceManager::CreateItem("Graphics/box.png", &tilemap.tiles[5][2], &tilemap, false));

	}

	void ResolveInput(SDL_Event& e) {

		if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEMOTION) {
			if (infoblock.IsMouseInBounds())
				infoblock.ResolveInput(e);
			else if (actionblock.IsMouseInBounds())
				actionblock.ResolveInput(e);
			else if(tilemap.IsMouseInBounds())
				tilemap.ResolveInput(e);
		}
		else if (e.type == SDL_USEREVENT) {
			// TODO
		}
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
			// not implemented yet
		}

		// if user_event send where needed
		// else if mouse_event, send where positioned
		// else if keyboard_event, send where needed
		// else unknown event?

	};
	
	void OnUpdate(double delta) {
		
		infoblock.OnUpdate(delta);
		actionblock.OnUpdate(delta);
	
	};

	void OnRender() {
		
		infoblock.OnRender();
		actionblock.OnRender();

		tilemap.OnRender();
		for (auto unit : units)
			unit->OnRender();
		for (auto item : items)
			item->OnRender();
	};


private:

	UnitInfoBlock infoblock;
	UnitActionBlock actionblock;


	BoxTileMap tilemap;

	int activeUnit;
	std::vector<Unit*> units;
	std::vector<Item*> items;

};