#include "Tiles.h"

SDL_Texture* BoxTile::tex_hover = nullptr;
SDL_Texture* BoxTile::tex_move = nullptr;
SDL_Texture* BoxTile::tex_run = nullptr;
SDL_Texture* BoxTile::tex_attack = nullptr;

// set up demo units

void BoxTileMap::InitDemo() {
	units.push_back(Unit(100, 100, 5, &tiles[1][2], "Graphics/Hero/idle1.png", this, true));
	units[0].tile->occ = &(units[0]); bool u1 = units[0].tile->occ->isEnemy();
	units.push_back(Unit(100, 100, 5, &tiles[4][3], "Graphics/Enemy1/idle1.png", this, false));
	units[1].tile->occ = &(units[1]); bool u2 = units[1].tile->occ->isEnemy();
	units.push_back(Unit(100, 100, 5, &tiles[4][4], "Graphics/Enemy2/idle1.png", this, false));
	units[2].tile->occ = &(units[2]); bool u3 = units[2].tile->occ->isEnemy();
	units.push_back(Unit(100, 100, 5, &tiles[4][2], "Graphics/Enemy3/idle1.png", this, false));
	units[3].tile->occ = &(units[3]); bool u4 = units[3].tile->occ->isEnemy();
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
	//std::cout << "( " << x << " ; " << y << " ) -> [ " << xt << " ; " << yt << " ]" << std::endl;
	std::cout << tiles.size() << "x" << tiles[0].size() << " <- " << xt << "x" << yt << std::endl;
	if (xt < 0 || yt < 0 || yt >= tiles.size() || xt >= tiles[yt].size())
		hover = false;
	else
		hover = true;

	if (e.type == SDL_MOUSEBUTTONDOWN && hover && tiles[yt][xt].occ == nullptr) {
		// move active unit TODO passing center of tile
		units[activeUnit].Move(&tiles[yt][xt]);
	}

}

int BoxTileMap::GetDistance(SDL_Point & p1, SDL_Point & p2) {
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int BoxTileMap::GetDistance(int & tx1, int & tx2, int & ty1, int & ty2) {
	return abs(tx1 - tx2) + abs(ty1 - ty2);
}

int BoxTileMap::GetDistance(BoxTile * t1, BoxTile * t2) {
	std::cout << "GetDistance: " << (abs(t1->pos.x - t2->pos.x) + abs(t1->pos.y - t2->pos.y)) / boxTileSize << std::endl;
	return (abs(t1->pos.x - t2->pos.x) + abs(t1->pos.y - t2->pos.y)) / boxTileSize;
}

bool BoxTileMap::CanMoveHere(BoxTile * tile) {
	return GetDistance(units[activeUnit].tile, tile) <= units[activeUnit].CurAP;
}

void BoxTileMap::OnUpdate(double delta) {

	for (auto &unit : units)
		unit.OnUpdate(delta);

	// if any change on field occured, change states of tiles accordingly
	if (false) { //stateChange

		for (int x = 0; x < tiles[0].size(); x++) {
			for (int y = 0; y < tiles.size(); y++) {
				tiles[y][x].OnUpdate();
			}
		}

	}

}

void BoxTileMap::OnRender(SDL_Renderer * ren) {

	for (auto line : tiles) {

		for (auto tile : line) {
			std::cout << tile.occ << "   ";
		}
		std::cout << std::endl;
	}
	// if current unit is held by player
	bool renderMovable = true; // units[activeUnit].isPlayer;

	// render tilemap
	for (auto &line: tiles) {
		for (auto &tile : line) {

			if (tile.occ == nullptr)
				std::cout << "Current Tile Has No Occupant." << std::endl;
			else
				std::cout << tile.occ->toString();

			// render default with movable
			if (renderMovable && GetDistance(units[activeUnit].tile, &tile) <= units[activeUnit].CurAP) {
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

	// render hover tile
	if (hover) {
		std::cout << "Sending TILE_HOVER " << TILE_HOVER << std::endl;
		tiles[yt][xt].SetState(TILE_HOVER);
		// SDL_RenderCopy(ren, hoverTileTex, nullptr, &tiles[yt][xt].pos);
	}

	for (auto &line : tiles)
		for (auto &tile : line)
			tile.OnRender();

	// render units
	for (auto &unit : units)
		unit.OnRender();

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
	return units[activeUnit].isPlayer;
}
