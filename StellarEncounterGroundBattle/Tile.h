#ifndef SE_TILE
#define SE_TILE

#include "stdlibs.h"
#include "EntityManager.h"
#include "UID.h"

class Tile
{
public:


	Tile(SDL_Texture* texture) : tex(texture) {
		ID = UID::GetNewTileUID();
	};
	~Tile() {};

	SDL_Texture * tex = nullptr;

	UID ID;
	// UID OccID;

};

#endif