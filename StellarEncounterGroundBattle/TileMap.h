#pragma once
#include "stdlibs.h"
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
		hoverTileTex = ResourceManager::loadTex("Graphics/thover.png");
		while (std::getline(ss, line, ',')) {
			tileLayout.push_back(std::vector<int>());
			for (char c : line) {
				tileLayout[line_count].push_back(c - 48);
				if (tileCodeMap.find(c - 48) == tileCodeMap.end())
					tileCodeMap[c - 48] = ResourceManager::loadTex(Constants::GetTileCodePath(c - 48));
			}
			line_count++;
		}
	}

	void ResolveInput(SDL_Event &e) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		yt = (y - start_pt.y) / Constants::yTileSize;
		x -= yt * Constants::xTileSize / 2;
		xt = (x - start_pt.x) / Constants::xTileSize;
		std::cout << "[ " << xt << " ; " << yt << " ]" << std::endl;
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
		tile_rect.w = Constants::xTileSize;
		tile_rect.h = Constants::yTileSize;

		bool odd = true;

		for (auto vec : tileLayout) {
			for (auto tile : vec) {
				SDL_RenderCopy(ren, tileCodeMap[tile], nullptr, &tile_rect);
				tile_rect.x += Constants::xTileSize;
			}
			tile_rect.y += Constants::yTileBoxSize + Constants::yTileTopSize;
			odd = !odd;
			if (odd) {
				tile_rect.x = start_pt.x;
			}
			else {
				tile_rect.x = start_pt.x + Constants::xTileSize / 2;
			}
		}

		if (hover) {
			tile_rect.y = start_pt.y + yt * (Constants::yTileBoxSize + Constants::yTileTopSize);
			tile_rect.x = start_pt.x + xt * Constants::xTileSize + yt * Constants::xTileSize / 2;
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


