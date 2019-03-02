#include "EntityManager.h"



std::vector<std::vector<Tile>> Managers::EntityManager::TileMap;
std::map<UID, Character> Managers::EntityManager::CharacterMap;

void Managers::EntityManager::CreateNewTileMap(std::string * src)
{
	// TODO
}

SDL_Rect Managers::EntityManager::GetMouseHex(SDL_Event * e)
{
	SDL_Rect pos;
	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);

	x -= Constants::xMargin;
	y -= Constants::yMargin;

	pos.y = y / Constants::yTileSize * 4 / 3;
	x -= Constants::xTileSize / 2 * pos.y;
	pos.x = x / Constants::xTileSize;
	if (x < 0)
		pos.x--;

	return pos;
}

Character * Managers::EntityManager::GetCharacter(UID ID)
{
	return CharacterMap.find(ID) == CharacterMap.end() ? nullptr : &CharacterMap[ID];
}

Tile * Managers::EntityManager::GetTile(int x, int y)
{
	return (TileMap.size() > x) && (TileMap[x].size() > y) ? &TileMap[x][y] : nullptr ;
}
