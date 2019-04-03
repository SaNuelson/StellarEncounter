#pragma once
#include "stdlib.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "GameObject.h"

class TileMap
{
public:

	TileMap() = default;

	~TileMap() {};

	void Init(std::string source, int x, int y) {
		start_pt.x = x;
		start_pt.y = y;
		std::stringstream ss(source);
		std::string line;
		int line_count = 0;
		hoverTileTex = ResourceManager::LoadTexture("Graphics/thover.png");
		while (std::getline(ss, line, ',')) {
			tileLayout.push_back(std::vector<int>());
			for (char c : line) {
				tileLayout[line_count].push_back(c - 48);
				if (tileCodeMap.find(c - 48) == tileCodeMap.end())
					tileCodeMap[c - 48] = ResourceManager::LoadTexture(GetTileCodePath(c - 48));
			}
			line_count++;
		}
	}

	void ResolveInput(SDL_Event &e) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		yt = (y - start_pt.y) / (yTileBoxSize + yTileTopSize);
		x -= yt * xTileSize / 2;
		xt = (x - start_pt.x) / xTileSize;
		std::cout << "( " << x << " ; " << y << " ) -> [ " << xt << " ; " << yt << " ]" << std::endl;
		if (xt < 0 || yt < 0 || yt >= tileLayout.size() || xt >= tileLayout[yt].size())
			hover = false;
		else
			hover = true;

	}

	void OnRender(SDL_Renderer * ren) {

		// dst rect shifting with each rendered tile
		SDL_Rect tile_rect;
		tile_rect.x = start_pt.x;
		tile_rect.y = start_pt.y;
		tile_rect.w = xTileSize;
		tile_rect.h = yTileSize;

		bool odd = true;

		for (auto vec : tileLayout) {
			for (auto tile : vec) {
				SDL_RenderCopy(ren, tileCodeMap[tile], nullptr, &tile_rect);
				tile_rect.x += xTileSize;
			}
			tile_rect.y += yTileBoxSize + yTileTopSize;
			odd = !odd;
			if (odd) {
				tile_rect.x = start_pt.x;
			}
			else {
				tile_rect.x = start_pt.x + xTileSize / 2;
			}
		}

		if (hover) {
			tile_rect.y = start_pt.y + yt * (yTileBoxSize + yTileTopSize);
			tile_rect.x = start_pt.x + xt * xTileSize + yt * xTileSize / 2;
			SDL_RenderCopy(ren, hoverTileTex, nullptr, &tile_rect);
		}

	}

private:

	// for now tile textures will be held in resourcemanager, tilemap will ask on render for these tiles, later they should be loaded once, then blitted on a uniform surface

	std::vector<std::vector<int>> tileLayout;
	std::map<int, SDL_Texture*> tileCodeMap;
	

	SDL_Point start_pt;

	SDL_Texture* hoverTileTex;
	bool hover;
	int xt, yt;

};


class BoxTileMap
{
public:

	BoxTileMap() = default;

	~BoxTileMap() {};

	// set up demo units
	void InitDemo() {

		SDL_Point pos;
		pos.x = 2;
		pos.y = 3;
		units.push_back(Unit(100, 100, 5, pos, "Graphics/Hero/idle1.png", this, true));
		pos.x = 6;
		pos.y = 3;
		units.push_back(Unit(100, 100, 5, pos, "Graphics/Enemy1/idle1.png", this, false));
		pos.x = 6;
		pos.y = 1;
		units.push_back(Unit(100, 100, 5, pos, "Graphics/Enemy2/idle1.png", this, false));
		pos.x = 6;
		pos.y = 5;
		units.push_back(Unit(100, 100, 5, pos, "Graphics/Enemy3/idle1.png", this, false));
	}

	// set up tilemap from source
	void Init(std::string source, int x, int y) {
		start_pt.x = x;
		start_pt.y = y;
		std::stringstream ss(source);
		std::string line;
		int line_count = 0;
		hoverTileTex = ResourceManager::LoadTexture("Graphics/txhover.png");
		moveTileTex = ResourceManager::LoadTexture("Graphics/txmove.png", 150);
		runTileTex = ResourceManager::LoadTexture("Graphics/txrun.png", 150);
		while (std::getline(ss, line, ',')) {
			tileLayout.push_back(std::vector<int>());
			for (char c : line) {
				tileLayout[line_count].push_back(c - 48);
				if (tileCodeMap.find(c - 48) == tileCodeMap.end())
					tileCodeMap[c - 48] = ResourceManager::LoadTexture(GetBoxTileCodePath(c - 48));
			}
			line_count++;
		}
	}

	void ResolveInput(SDL_Event &e) {
		
		if (lock)
			return;

		int x, y;
		SDL_GetMouseState(&x, &y);

		yt = (y - start_pt.y) / boxTileSize;
		xt = (x - start_pt.x) / boxTileSize;
		//std::cout << "( " << x << " ; " << y << " ) -> [ " << xt << " ; " << yt << " ]" << std::endl;
		std::cout << tileLayout.size() << "x" << tileLayout[0].size() << " <- " << xt << "x" << yt << std::endl;
		if (xt < 0 || yt < 0 || yt >= tileLayout.size() || xt >= tileLayout[yt].size())
			hover = false;
		else
			hover = true;

		if (e.type == SDL_MOUSEBUTTONDOWN) {
			// move active unit TODO passing center of tile
			SDL_Point p;
			p.x = xt;
			p.y = yt;
			units[activeUnit].Move(p);
		}

	}

	// returns center of the tile at said tileposition, used for render
	SDL_Point GetCoords(int &tx, int &ty) {
		SDL_Point pt;
		pt.x = -1;
		pt.y = -1;
		if (tx < 0 || ty < 0 || ty >= tileLayout.size() || tx >= tileLayout[ty].size())
			return pt;
		else {
			pt.x = start_pt.x + (tx + 0.5) * boxTileSize;
			pt.y = start_pt.y + (ty + 0.5) * boxTileSize;
			return pt;
		}
	}

	int GetDistance(SDL_Point &p1, SDL_Point &p2) {
		return abs(p1.x - p2.x) + abs(p1.y - p2.y);
	}

	int GetDistance(int &tx1, int &tx2, int &ty1, int &ty2) {
		return abs(tx1 - tx2) + abs(ty1 - ty2);
	}

	void OnUpdate(double delta) {

		for (auto &unit : units)
			unit.OnUpdate(delta);

	}

	void OnRender(SDL_Renderer * ren) {

		// dst rect shifting with each rendered tile
		SDL_Point tile_pos;
		tile_pos.x = 0;
		tile_pos.y = 0;
		SDL_Rect tile_rect;
		tile_rect.x = start_pt.x;
		tile_rect.y = start_pt.y;
		tile_rect.w = boxTileSize;
		tile_rect.h = boxTileSize;

		bool renderMovable = units[activeUnit].isPlayer;

		// render tilemap
		for (auto vec : tileLayout) {
			for (auto tile : vec) {
				SDL_RenderCopy(ren, tileCodeMap[tile], nullptr, &tile_rect);

				if (renderMovable && GetDistance(units[activeUnit].currTile, tile_pos) <= units[activeUnit].CurAP)
					SDL_RenderCopy(ren, moveTileTex, nullptr, &tile_rect);

				tile_rect.x += boxTileSize;
				tile_pos.x++;
			}
			tile_rect.y += boxTileSize;
			tile_pos.y++;
			tile_rect.x = start_pt.x;
			tile_pos.x = 0;
		}

		// render hover tile
		if (hover) {
			tile_rect.y = start_pt.y + yt * boxTileSize;
			tile_rect.x = start_pt.x + xt * boxTileSize;
			SDL_RenderCopy(ren, hoverTileTex, nullptr, &tile_rect);
		}

		// render units
		for (auto &unit : units)
			unit.OnRender();

	}

	bool Lock(void* locker) {
		if (lock)
			return false;
		lock = true;
		this->locker = locker;
	}

	bool Unlock(void* locker) {
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

private:

	// for now tile textures will be held in resourcemanager, tilemap will ask on render for these tiles, later they should be loaded once, then blitted on a uniform surface


	std::vector<std::vector<int>> tileLayout;
	std::map<int, SDL_Texture*> tileCodeMap;

	std::vector<Unit> units;

	int activeUnit = 0;

	SDL_Point start_pt;

	SDL_Texture* hoverTileTex;
	bool hover;
	int xt, yt;

	SDL_Texture* moveTileTex;
	SDL_Texture* runTileTex;

	bool lock = false; // lock game for animations and other stuff, only when unlocked can game continue
	void* locker;

};

class BoxTile {

public:

	BoxTile(std::string source, SDL_Rect position) {
		tex = ResourceManager::LoadTexture(source);
		pos = position;
		occ = nullptr;
	}

	GameObject* GetOccupant() { return occ; }

	void OnRender() {
		SDL_RenderCopy(ResourceManager::ren, tex, nullptr, &pos);
	}

private:

	SDL_Texture* tex;
	SDL_Rect pos;
	GameObject * occ;

};