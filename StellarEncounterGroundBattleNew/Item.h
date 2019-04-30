#pragma once
#include "stdlib.h"
#include "GameObject.h"
#include "Tilemap.h"
#include "Tile.h"
#include "ResourceManager.h"

class Item : public GameObject {

public:

	Item() {};
	Item(std::string texSrc, Tile* tile, TileMap* tilemap, bool usable);

	bool isEnemy() override;

	void OnRender() override;

	void ReceiveAction(int amount) override;

	std::string toString() override;

	Item* getPtr() override;

private:

	TileMap * tilemap;
	Tile * tile;
	bool isUsable;

	SDL_Renderer* ren;
	SDL_Texture * tex;
	SDL_Rect position;

	int CurHP;
	int MaxHP;

	// render
	big currentTexture = 0;
	big textureSpeed = 300;
	std::vector<SDL_Texture*> textures;

};