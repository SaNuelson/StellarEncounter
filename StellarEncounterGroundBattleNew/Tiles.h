#pragma once
#include "stdlib.h"
#include "ResourceManager.h"
#include "Constants.h"

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

	SDL_Point GetCoords(int &x, int &y) {
		SDL_Point pt;
		if (x < 0 || y < 0 || x >= tileLayout.size() || y >= tileLayout[0].size())
			return pt;
		else {
			pt.x = start_pt.x + x * boxTileSize;
			pt.y = start_pt.y + y * boxTileSize;
		}
	}

	void ResolveInput(SDL_Event &e) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		yt = (y - start_pt.y) / boxTileSize;
		xt = (x - start_pt.x) / boxTileSize;
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

