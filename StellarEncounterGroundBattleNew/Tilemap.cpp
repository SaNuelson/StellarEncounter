#include "Tilemap.h"
#include "GroundBattleScene.h"

void TileMap::Init(std::string source, int x, int y) {

	/*
	
	for now source must be in format with rectangle-like proportions, starting with margined line.
	that means every odd line starting with first, must have N-1 cells
		while every even line must have N cells, because of specific indexation of the tiles.

	*/

	start_pt.x = x;
	start_pt.y = y;
	SDL_Point pos;
	SDL_Point mappos;
	mappos.x = 0;
	mappos.y = 0;
	pos.x = x;
	pos.y = y;
	std::stringstream ss(source);
	std::string line;
	int line_count = 0;
	// true when first line starts with margin
	bool margin = true; // later figured before-hand, used to shift every second line by half the width of a tile
	while (std::getline(ss, line, ',')) {
		pos.x = x;
		pos.y += yTileTopSize + yTileBoxSize;
		if (margin)
			pos.x += xTileSize / 2;
		mappos.x = 0;
		mappos.y = line_count;
		tiles.push_back(std::vector<Tile>());
		for (char c : line) {
			tiles[line_count].push_back(Tile(GetTileCodePath(c - 48), pos, mappos, this));
			pos.x += xTileSize;
			mappos.x++;
		}
		line_count++;
		margin = !margin;
	}

	// bind neighbors for all tiles without margin
	for(int i = 1; i < tiles.size(); i += 2)
		for (int j = 0; j < tiles[i].size(); j ++) {
			// top_right
			if (i > 0 && tiles[i-1].size() > j) {
				tiles[i][j].tile_up_right = &tiles[i - 1][j];
				tiles[i - 1][j].tile_down_left = &tiles[i][j];
			}
			// left
			if (j > 0) {
				tiles[i][j].tile_left = &tiles[i][j - 1];
				tiles[i][j - 1].tile_right = &tiles[i][j];
			}
			// top_left
			if (i > 0 && j > 0) {
				tiles[i][j].tile_up_left = &tiles[i - 1][j - 1];
				tiles[i - 1][j - 1].tile_down_right = &tiles[i][j];
			}
		}

	// bind neighbors for all tiles with margin
	for (int i = 0; i < tiles.size(); i += 2)
		for (int j = 0; j < tiles[i].size(); j ++) {
			// top_right
			if (i > 0 && tiles[i - 1].size() > j + 1) {
				tiles[i][j].tile_up_right = &tiles[i - 1][j + 1];
				tiles[i - 1][j + 1].tile_down_left = &tiles[i][j];
			}
			// left
			if (j > 0) {
				tiles[i][j].tile_left = &tiles[i][j - 1];
				tiles[i][j - 1].tile_right = &tiles[i][j];
			}
			// top_left
			if (i > 0 && tiles[i].size() > j) {
				tiles[i][j].tile_up_left = &tiles[i - 1][j];
				tiles[i - 1][j].tile_down_right = &tiles[i][j];
			}
		}


}

void TileMap::PutOnTile(GameObject* obj, Tile* tile)
{
	obj->tile = tile;
	obj->tilemap = this;
	tile->occ = obj;
}

void TileMap::PutOnTile(GameObject* obj, int x, int y)
{
	PutOnTile(obj, GetTile(x, y));
}

void TileMap::ResolveInput(SDL_Event & e) {

}

int TileMap::GetDistance(Tile * t1, Tile * t2) {
	
	return 1; // todo
}

SDL_Point TileMap::GetMoveVec(Tile* t1, Tile* t2)
{
	SDL_Point p;
	p.x = t2->pos.x - t1->pos.x;
	p.y = t2->pos.y - t1->pos.y;
	return p;
}

bool TileMap::CanMove(Tile * tile)
{
	if (tile == nullptr)
		return false;
	if (tile->occ != nullptr)
		return false;
	return true;
}

bool TileMap::CanAttack(Unit * unit, Tile * tile)
{
	if (tile == nullptr)
		return false;
	// std::cout << "TileMap::CanAttack " << tile->occ->isEnemy() << " against " << unit->isEnemy() << std::endl;
	if (tile->occ->isEnemy() != unit->isEnemy())
		return true;
	return false;
}

void TileMap::OnUpdate(double delta) {

	// if any change on field occured, change states of tiles accordingly
	if (true) { //stateChange

		for (int x = 0; x < tiles.size(); x++) {
			for (int y = 0; y < tiles[x].size(); y++) {
				tiles[x][y].OnUpdate();
			}
		}
		/*
		auto cu = scene->GetCurrentUnit();
		int len = cu->CurAP;
		SDL_Point p;
		p.x = cu->tile->mappos.y;
		p.y = cu->tile->mappos.x;
		std::vector<std::pair<int,SDL_Point>> path;
		while (true) {
			std::cout << "Wielding tile " << p.x << " " << p.y << std::endl;
			if (p.y < tiles[0].size() - 1 && !tiles[p.x][p.y + 1].GetState(TILE_MOVE) && len > 0 && tiles[p.x][p.y + 1].occ == nullptr) {
				path.push_back(std::make_pair(len,p));
				tiles[p.x][p.y + 1].AddState(TILE_MOVE);
				p.y++;
				len--;
			}
			else if (p.y > 0 && !tiles[p.x][p.y - 1].GetState(TILE_MOVE) && len > 0 && tiles[p.x][p.y + 1].occ == nullptr) {
				path.push_back(std::make_pair(len, p));
				tiles[p.x][p.y - 1].AddState(TILE_MOVE);
				p.y--;
				len--;
			}
			else if (p.x < tiles.size() - 1 && !tiles[p.x + 1][p.y].GetState(TILE_MOVE) && len > 0 && tiles[p.x+1][p.y].occ == nullptr) {
				path.push_back(std::make_pair(len, p));
				tiles[p.x + 1][p.y].AddState(TILE_MOVE);
				p.x++;
				len--;
			}
			else if (p.x > 0 && !tiles[p.x - 1][p.y].GetState(TILE_MOVE) && len > 0 && tiles[p.x-1][p.y].occ == nullptr) {
				path.push_back(std::make_pair(len, p));
				tiles[p.x - 1][p.y].AddState(TILE_MOVE);
				p.x--;
				len--;
			}
			else if (path.size() > 0) {
				p = path[path.size() - 1].second;
				len = path[path.size() - 1].first;
				path.pop_back();
			}
			else {
				break;
			}
		}
		*/
	}

}

void TileMap::OnRender() {

	for (auto &line : tiles)
		for (auto &tile : line)
			tile.OnRender();
	for (auto& line : tiles)
		for (auto& tile : line)
			tile.AfterRender();

}