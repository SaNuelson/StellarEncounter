#include "Tile.h"



Tile::Tile(SDL_Texture * srctex)
{
	tex = srctex;
	ID = UID::GetNewTileUID();
	OccID = UID::GetEmptyUID();
}


Tile::~Tile()
{
}