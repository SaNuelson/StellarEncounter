#include "Tilemap.h"

SDL_Texture* BoxTile::tex_hover = nullptr;
SDL_Texture* BoxTile::tex_move = nullptr;
SDL_Texture* BoxTile::tex_run = nullptr;
SDL_Texture* BoxTile::tex_attack = nullptr;

// set up demo units

void BoxTileMap::InitDemo() {
	units.push_back(ResourceManager::CreateUnit(100, 100, 5, &tiles[1][2], "Graphics/Hero/idle1.png", this, true));
	units.push_back(ResourceManager::CreateUnit(100, 100, 5, &tiles[4][3], "Graphics/Enemy1/idle1.png", this, false));
	units.push_back(ResourceManager::CreateUnit(100, 100, 5, &tiles[4][4], "Graphics/Enemy2/idle1.png", this, false));
	units.push_back(ResourceManager::CreateUnit(100, 100, 5, &tiles[4][2], "Graphics/Enemy3/idle1.png", this, false));

	items.push_back(ResourceManager::CreateItem("Graphics/box.png",&tiles[3][4], this, false));
	items.push_back(ResourceManager::CreateItem("Graphics/box.png", &tiles[5][2], this, false));
}

// set up tilemap from source

void BoxTileMap::Init(std::string source, int x, int y) {
	start_pt.x = x;
	start_pt.y = y;
	SDL_Point pos;
	pos.x = x;
	pos.y = y;
	std::stringstream ss(source);
	std::string line;
	int line_count = 0;
	hoverTileTex = ResourceManager::LoadTexture("Graphics/txhover.png");
	moveTileTex = ResourceManager::LoadTexture("Graphics/txmove.png", 150);
	runTileTex = ResourceManager::LoadTexture("Graphics/txrun.png", 150);
	while (std::getline(ss, line, ',')) {
		tiles.push_back(std::vector<BoxTile>());
		for (char c : line) {
			tiles[line_count].push_back(BoxTile(GetBoxTileCodePath(c - 48), pos, this));
			pos.x += boxTileSize;
		}
		pos.x = x;
		pos.y += boxTileSize;
		line_count++;
	}
	units.clear();
}

void BoxTileMap::ResolveInput(SDL_Event & e) {

	if (lock)
		return;

	int x, y;
	SDL_GetMouseState(&x, &y);

	yt = (y - start_pt.y) / boxTileSize;
	xt = (x - start_pt.x) / boxTileSize;
	if (xt < 0 || yt < 0 || yt >= tiles.size() || xt >= tiles[yt].size())
		hover = false;
	else
		hover = true;

	if (e.type == SDL_MOUSEBUTTONDOWN && hover && tiles[yt][xt].occ == nullptr) {
		// move active unit TODO passing center of tile
		units[activeUnit]->Move(&tiles[yt][xt]);
	}

}

int BoxTileMap::GetDistance(SDL_Point & p1, SDL_Point & p2) {
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int BoxTileMap::GetDistance(int & tx1, int & tx2, int & ty1, int & ty2) {
	return abs(tx1 - tx2) + abs(ty1 - ty2);
}

int BoxTileMap::GetDistance(BoxTile * t1, BoxTile * t2) {
	return (abs(t1->pos.x - t2->pos.x) + abs(t1->pos.y - t2->pos.y)) / boxTileSize;
}

bool BoxTileMap::CanMoveHere(BoxTile * tile) {
	return GetDistance(units[activeUnit]->tile, tile) <= units[activeUnit]->CurAP;
}

void BoxTileMap::OnUpdate(double delta) {

	for (auto &unit : units)
		unit->OnUpdate(delta);

	// if any change on field occured, change states of tiles accordingly
	if (true) { //stateChange

		for (int x = 0; x < tiles[0].size(); x++) {
			for (int y = 0; y < tiles.size(); y++) {
				tiles[y][x].OnUpdate();
			}
		}

	}

}

void BoxTileMap::OnRender(SDL_Renderer * ren) {

	// if current unit is held by player
	bool renderMovable = true; // units[activeUnit].isPlayer;

	// render tilemap
	/*
	for (auto &line: tiles) {
		for (auto &tile : line) {

			tile.SetState(TILE_DEFAULT);

			std::cout << tile.occ << std::endl;

			// render default with movable
			if (renderMovable && GetDistance(units[activeUnit]->tile, &tile) <= units[activeUnit]->CurAP) {
				if(tile.occ == nullptr) {
					std::cout << "Sending TILE_DEFAULT " << TILE_DEFAULT << "\n       TILE_MOVE " << TILE_MOVE << std::endl;
					tile.SetState(TILE_MOVE);
					}

				// render attack
				else {
					if (tile.occ->isEnemy()) {
						tile.SetState(TILE_ATTACK);
					}
				}
			}
				

		}
	}
	*/

	// render hover tile
	if (hover) {
		tiles[yt][xt].SetState(TILE_HOVER);
	}

	// render tiles
	for (auto &line : tiles)
		for (auto &tile : line)
			tile.OnRender();

	// render units
	for (auto &unit : units)
		unit->OnRender();

	for (auto &item : items)
		item->OnRender();

}

Unit * BoxTileMap::GetCurrentUnit()
{
	return units[activeUnit];
}

bool BoxTileMap::Lock(void * locker) {
	if (lock)
		return false;
	lock = true;
	this->locker = locker;
}

bool BoxTileMap::Unlock(void * locker) {
	if (!lock) {
		std::cout << "Unlock invalid, lock not locked by entity " << typeid(&locker).name();
		exit(5);
	}
	else if (this->locker != locker) {
		std::cout << "Unlock invalid, there is a different locker." << std::endl;
		return false;
	}
	locker = nullptr;
	lock = false;
}

bool BoxTileMap::IsPlayerTurn() {
	if (units.empty())
		return false;
	return units[activeUnit]->isPlayer;
}

void BoxTileMap::EndTurn()
{
	//TODO
	units[activeUnit]->CurAP = units[activeUnit]->MaxAP;
}
