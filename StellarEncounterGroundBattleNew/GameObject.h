#pragma once
#include "stdlib.h"

using big = uint16_t;
using small = uint8_t;
// speed - in milliseconds

class BoxTileMap;
class BoxTile;

class GameObject {
public:
	~GameObject() {}

	virtual bool isEnemy();

	virtual void OnRender() {};

	virtual std::string toString();

	virtual GameObject* getPtr();
};

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

class Item : public GameObject {

public:

	Item() {};
	Item(std::string texSrc, BoxTile* tile, BoxTileMap* tilemap, bool usable);

	bool isEnemy() override;

	void OnRender() override;

	std::string toString() override;

	Item* getPtr() override;

private:

	BoxTileMap * tilemap;
	BoxTile * tile;
	bool isUsable;

	SDL_Renderer* ren;
	SDL_Texture * tex;
	SDL_Rect position;

	// render
	big currentTexture = 0;
	big textureSpeed = 300;
	std::vector<SDL_Texture*> textures;

};