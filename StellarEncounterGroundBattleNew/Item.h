#pragma once
#include "stdlib.h"
#include "GameObject.h"
#include "Tilemap.h"
#include "Tile.h"
#include "ResourceManager.h"

// currently working, but doesn't do much except stand in the way, I was thinking about possible expansion for usable/destroyable items (chests, potions, portals...)
class Item : public GameObject {

public:

	// if reimplemented, constructor should take std::string, which will be parsed similarly to how units currently work
	Item() {};
	Item(std::string texSrc, Tile* tile, TileMap* tilemap, bool usable);

	void OnRender() override;

	void ReceiveAction(int amount) override;

	std::string toString() override;

private:

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