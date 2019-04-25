#pragma once
#include "stdlib.h"
#include "GameObject.h"
#include "Tilemap.h"
#include "Tile.h"
#include "ResourceManager.h"

class Unit : public GameObject {
public:
	Unit() {};
	Unit(big HP, big SP, small AP, BoxTile* tile, std::string texSrc, BoxTileMap* tilemap, bool playerTeam);

	void LoadTextures(std::string texSrc);

	void OnUpdate(double delta);

	void Move(BoxTile* tile);

	void OnRender() override;

	bool isEnemy() override;

	std::string toString() override;

	Unit* getPtr() override;

	//private:

		// GameLogic
	BoxTileMap* tilemap;
	bool isPlayer;

	// HitPoints
	big MaxHP = 100;
	big CurHP = 100;
	big MaxSP = 100;
	big CurSP = 100;

	// Movement
	small MaxAP = 5;
	small CurAP = 5;

	SDL_Rect position;
	BoxTile* tile;

	// Equip
	// Equipment equip;

	// Render
	big textureSpeed;
	big textureTimeLeft;
	small currentTexture = 0;
	std::vector<SDL_Texture*> textures;
	std::map<small, std::pair<small, small>> textureSets;

};
