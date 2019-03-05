#ifndef SE_ENTITY_MANAGER
#define SE_ENTITY_MANAGER
#include "stdlibs.h"
#include "Tile.h"
#include "Character.h"
#include "Constants.h"
#include "UID.h"

// currently not used, should take care of creating and keeping track of tiles and units (from components hopefully).

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

#endif