#pragma once
#include "stdlibs.h"
#include "Tile.h"
#include "Character.h"
#include "Constants.h"
#include "UID.h"

class Tile;
class Character;

namespace Managers {

	class EntityManager
	{
	public:
		static void CreateNewTileMap(std::string* src);

		static SDL_Rect GetMouseHex(SDL_Event* e);

		static Character* GetCharacter(UID ID);
		static Tile* GetTile(int x, int y);

	private:

		static std::vector<std::vector<Tile>> TileMap;
		static std::map<UID, Character> CharacterMap;

	};

}

