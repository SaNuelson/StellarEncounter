#include "Tilemap.h"
#include "Unit.h"

SDL_Texture* BoxTile::tex_hover = nullptr;
SDL_Texture* BoxTile::tex_move = nullptr;
SDL_Texture* BoxTile::tex_run = nullptr;
SDL_Texture* BoxTile::tex_attack = nullptr;

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
}

void BoxTileMap::ResolveInput(SDL_Event & e) {

	int x, y;
	SDL_GetMouseState(&x, &y);

	yt = (y - start_pt.y) / boxTileSize;
	if (yt >= tiles.size())
		yt--;
	xt = (x - start_pt.x) / boxTileSize;
	if (xt >= tiles[0].size())
		xt--;

	hover = true;

	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		click = true;
		
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

bool BoxTileMap::CanMoveHere(Unit* unit, BoxTile * tile) {
	return GetDistance(unit->tile, tile) <= unit->CurAP;
}

void BoxTileMap::OnUpdate(double delta) {

	// if any change on field occured, change states of tiles accordingly
	if (true) { //stateChange

		for (int x = 0; x < tiles[0].size(); x++) {
			for (int y = 0; y < tiles.size(); y++) {
				tiles[y][x].OnUpdate ();
			}
		}

	}

}

void BoxTileMap::OnRender() {

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
		if (oxt != -1 && oyt != -1)
			tiles[oyt][oxt].SetState(TILE_DEFAULT);
		tiles[yt][xt].SetState(TILE_HOVER);
		oxt = xt; oyt = yt;
		hover = false;
	}

	// render tiles
	for (auto &line : tiles)
		for (auto &tile : line)
			tile.OnRender();

}

void BoxTileMap::DispatchEvent(EventCode ec)
{
}

bool BoxTileMap::IsInBounds(int & x, int & y)
{
	auto& brt = tiles[tiles.size() - 1][tiles[tiles.size() - 1].size() - 1];
	return (tiles[0][0].pos.x <= x && tiles[0][0].pos.y <= y && x <= brt.pos.x + brt.pos.w && y <= brt.pos.y + brt.pos.h);
}

bool BoxTileMap::IsMouseInBounds()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return IsInBounds(x, y);
}
