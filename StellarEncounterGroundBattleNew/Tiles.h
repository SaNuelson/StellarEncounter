#pragma once
#include "stdlib.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "Entity.h"

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

	// set up tilemap from source
	void Init(std::string source, int x, int y) {
		start_pt.x = x;
		start_pt.y = y;
		std::stringstream ss(source);
		std::string line;
		int line_count = 0;
		hoverTileTex = ResourceManager::LoadTexture("Graphics/txhover.png");
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

	SDL_Point GetCoords(int &tx, int &ty) {
		SDL_Point pt;
		pt.x = -1;
		pt.y = -1;
		if (tx < 0 || ty < 0 || tx >= tileLayout.size() || ty >= tileLayout[0].size())
			return pt;
		else {
			pt.x = start_pt.x + tx * boxTileSize;
			pt.y = start_pt.y + ty * boxTileSize;
			return pt;
		}
	}

	void ResolveInput(SDL_Event &e) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		yt = (y - start_pt.y) / boxTileSize;
		xt = (x - start_pt.x) / boxTileSize;
		//std::cout << "( " << x << " ; " << y << " ) -> [ " << xt << " ; " << yt << " ]" << std::endl;
		if (xt < 0 || yt < 0 || yt >= tileLayout.size() || xt >= tileLayout[yt].size())
			hover = false;
		else
			hover = true;

		if (e.type == SDL_MOUSEBUTTONDOWN) {
			// move active unit TODO passing center of tile
			SDL_Point p;
			p.x = xt;
			p.y = yt;
			entities[activeUnit].transform.Move(GetMoveVec(entities[activeUnit].transform.currentTile, p));
		}

	}

	SDL_Point GetMoveVec(SDL_Point tilefrom, SDL_Point tileto) {
		SDL_Point vec;
		vec.x = (tileto.x - tilefrom.x)*boxTileSize;
		vec.y = (tileto.y - tilefrom.y)*boxTileSize;
		return vec;
	}

	void OnUpdate(double delta) {
		for (auto &ent : entities) {
			ent.OnUpdate(delta);
		}

		std::cout << "After update " << entities[0].transform.position.x << entities[0].transform.position.y << std::endl;

	}

	void OnRender(SDL_Renderer * ren) {

		// dst rect shifting with each rendered tile
		SDL_Rect tile_rect;
		tile_rect.x = start_pt.x;
		tile_rect.y = start_pt.y;
		tile_rect.w = boxTileSize;
		tile_rect.h = boxTileSize;

		for (auto vec : tileLayout) {
			for (auto tile : vec) {
				SDL_RenderCopy(ren, tileCodeMap[tile], nullptr, &tile_rect);
				tile_rect.x += boxTileSize;
			}
			tile_rect.y += boxTileSize;
			tile_rect.x = start_pt.x;
		}

		if (hover) {
			tile_rect.y = start_pt.y + yt * boxTileSize;
			tile_rect.x = start_pt.x + xt * boxTileSize;
			SDL_RenderCopy(ren, hoverTileTex, nullptr, &tile_rect);
		}

		std::cout << "Before render " << entities[0].transform.position.x << entities[0].transform.position.y << std::endl;


		for (auto &ent : entities) {
			ent.render.OnRender(ren);
		}

	}

	void AddEntity(Entity ent) {
		entities.push_back(ent);
		SDL_Point p;
		p.x = ent.transform.currentTile.x;
		p.y = ent.transform.currentTile.y;
		entityPositions[&ent] = p;
	}

private:

	// for now tile textures will be held in resourcemanager, tilemap will ask on render for these tiles, later they should be loaded once, then blitted on a uniform surface

	std::vector<std::vector<int>> tileLayout;
	std::map<int, SDL_Texture*> tileCodeMap;

	std::map<Entity*, SDL_Point> entityPositions;
	std::vector<Entity> entities;
	int activeUnit = 0;

	SDL_Point start_pt;

	SDL_Texture* hoverTileTex;
	bool hover;
	int xt, yt;

};

