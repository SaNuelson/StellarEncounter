#include "Tilemap.h"
#include "GroundBattleScene.h"

SDL_Texture* BoxTile::tex_hover = nullptr;
SDL_Texture* BoxTile::tex_move = nullptr;
SDL_Texture* BoxTile::tex_run = nullptr;
SDL_Texture* BoxTile::tex_attack = nullptr;



void BoxTileMap::Init(std::string source, int x, int y) {
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
	hoverTileTex = ResourceManager::LoadTexture("Graphics/txhover.png");
	moveTileTex = ResourceManager::LoadTexture("Graphics/txmove.png", 150);
	runTileTex = ResourceManager::LoadTexture("Graphics/txrun.png", 150);
	while (std::getline(ss, line, ',')) {
		tiles.push_back(std::vector<BoxTile>());
		for (char c : line) {
			tiles[line_count].push_back(BoxTile(GetBoxTileCodePath(c - 48), pos, mappos, this));
			pos.x += boxTileSize;
			mappos.x++;
		}
		pos.x = x;
		pos.y += boxTileSize;
		line_count++;
		mappos.x = 0;
		mappos.y = line_count;
	}
	BoxTile* left;
	BoxTile* up;
	for(int i = 0; i < tiles.size(); i++)
		for (int j = 0; j < tiles[0].size(); j++) {
			if (i > 0) {
				tiles[i][j].tile_up = &tiles[i - 1][j];
				tiles[i - 1][j].tile_down = &tiles[i][j];
			}
			if (j > 0) {
				tiles[i][j].tile_left = &tiles[i][j - 1];
				tiles[i][j - 1].tile_right = &tiles[i][j];
			}
		}

}

void BoxTileMap::ResolveInput(SDL_Event & e) {

	int x, y;
	SDL_GetMouseState(&x, &y);

	if (y - start_pt.y < 0)
		yt = -1;
	else
		yt = (y - start_pt.y) / boxTileSize;
	if (x - start_pt.x < 0)
		xt = -1;
	else
		xt = (x - start_pt.x) / boxTileSize;

	if (xt < 0 || yt < 0 || yt >= tiles.size() || xt >= tiles[yt].size())
		hover = false;
	else
		hover = true;

	if (e.type == SDL_MOUSEBUTTONDOWN && hover) {
		// click on tile
		if (CanMove(scene->GetCurrentUnit(), &tiles[yt][xt])) {
			scene->GetCurrentUnit()->Move(&tiles[yt][xt]);
		}
		else if (CanAttack(scene->GetCurrentUnit(), &tiles[yt][xt])) {
			scene->GetCurrentUnit()->Move(&tiles[yt - 1][xt]); // TODO move on free tile in reach
			scene->GetCurrentUnit()->UseAction((Unit*)tiles[yt][xt].occ);
		}
	}

}
/*
int BoxTileMap::GetDistance(SDL_Point & p1, SDL_Point & p2) {
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int BoxTileMap::GetDistance(int & tx1, int & tx2, int & ty1, int & ty2) {
	return abs(tx1 - tx2) + abs(ty1 - ty2);
}
*/
int BoxTileMap::GetDistance(BoxTile * t1, BoxTile * t2) {
	
	return 1; // todo
}

bool BoxTileMap::CanMove(Unit * unit, BoxTile * tile)
{
	if (tile == nullptr)
		return false;
	if (tile->occ != nullptr)
		return false;
	return true;
}

bool BoxTileMap::CanAttack(Unit * unit, BoxTile * tile)
{
	if (tile == nullptr)
		return false;
	// std::cout << "BoxTileMap::CanAttack " << tile->occ->isEnemy() << " against " << unit->isEnemy() << std::endl;
	if (tile->occ->isEnemy() != unit->isEnemy())
		return true;
	return false;
}

bool BoxTileMap::CanMoveHere(BoxTile * tile) {
	return GetDistance(scene->GetCurrentUnit()->tile, tile) <= scene->GetCurrentUnit()->CurAP;
}

void BoxTileMap::OnUpdate(double delta) {

	// if any change on field occured, change states of tiles accordingly
	if (true) { //stateChange

		for (int x = 0; x < tiles.size(); x++) {
			for (int y = 0; y < tiles[0].size(); y++) {
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

void BoxTileMap::OnRender() {

	if (oxt >= 0 && oyt >= 0 && oxt < tiles[0].size() && oyt < tiles.size())
		tiles[oyt][oxt].DelState(TILE_HOVER);

	if (hover) {
		//std::cout << "BoxTileMap::OnRender - hover true on: " << yt << " " << xt << std::endl;
		tiles[yt][xt].AddState(TILE_HOVER);
	}

	oxt = xt;
	oyt = yt;

	for (auto &line : tiles)
		for (auto &tile : line)
			tile.OnRender();

}