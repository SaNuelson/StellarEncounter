#pragma once
#include "stdlib.h"

using big = uint16_t;
using small = uint8_t;
// speed - in milliseconds

class BoxTileMap;

class GameObject {
public:
	~GameObject() {}
};

class Unit : GameObject {
public:
	Unit() {};
	Unit(big HP, big SP, small AP, SDL_Point tilePosition, std::string texSrc, BoxTileMap* tilemap, bool playerTeam);

	void LoadTextures(std::string texSrc);

	void OnUpdate(double delta);

	void Move(SDL_Point destTile);

	void OnRender();

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
	
	SDL_Point currTile;
	
	SDL_Rect position;

	// Equip
	// Equipment equip;

	// Render
	big textureSpeed;
	big textureTimeLeft;
	small currentTexture = 0;
	std::vector<SDL_Texture*> textures;
	std::map<small, std::pair<small, small>> textureSets;

};

class Item : GameObject {

public:



private:

	big currentTexture = 0;
	big textureSpeed = 300;
	std::vector<SDL_Texture*> textures;

};