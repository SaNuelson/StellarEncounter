#pragma once
#include "stdlibs.h"
#include "EntityManager.h"
#include "UID.h"

class Tile
{
public:

	Tile(SDL_Texture*);
	~Tile();

	SDL_Texture * tex = nullptr;

	UID ID;
	UID OccID;

};

