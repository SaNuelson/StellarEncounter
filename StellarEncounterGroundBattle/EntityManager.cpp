#include "EntityManager.h"



std::vector<std::vector<Tile>> EntityManager::TileMap;
std::map<UID, Character> EntityManager::CharacterMap;

void EntityManager::CreateNewTileMap(std::string * src)
{
	// TODO
}

SDL_Rect EntityManager::GetMouseHex(SDL_Event * e)
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

UID EntityManager::CreateCharacter(std::string &src)
{
	// TODO
	return UID::GetEmptyUID();
}

Character* EntityManager::GetCharacter(UID id)
{
	if (CharacterMap.find(id) == CharacterMap.end()) {
		std::cout << "EntityManager::GetCharacter(" << id.toString() << ") error: UID not found in entity pool." << std::endl;
		return nullptr;
	}
	return &CharacterMap[id];
}

Tile * EntityManager::GetTile(int x, int y)
{
	return (TileMap.size() > x) && (TileMap[x].size() > y) ? &TileMap[x][y] : nullptr ;
}
