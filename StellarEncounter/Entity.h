#pragma once
#include "baselibs.h"
#include "ResourceManager.h"

class Entity {
public:
	SDL_Texture * tex;
};

class Tile : public Entity {

	Tile(int x, int y, SDL_Surface* srf) { rect->x = x; rect->y = y; surf = srf; };

	SDL_Surface * surf;
	SDL_Rect* rect;
	const int TILE_SIZE = 60;

};

class Character : public Entity {
public:

	Character(int x, int y, int HP, int AP, int att, bool is_controllable, SDL_Surface* srf) : max_health(HP), current_health(HP), attack(att), max_ap(AP), current_ap(AP), isControllable(is_controllable) {

	};

	bool isControllable;

	int 

	int current_health;
	int max_health;

	int attack;

	int current_ap;
	int max_ap;



};
