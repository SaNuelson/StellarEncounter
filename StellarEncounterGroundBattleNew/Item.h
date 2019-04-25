#pragma once
#include "stdlib.h"
#include "GameObject.h"
#include "Tilemap.h"
#include "Tile.h"
#include "ResourceManager.h"

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