#pragma once
#include "stdlib.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "Tiles.h"

class UnitInfoBlock {
public:

	UnitInfoBlock(BoxTileMap* tilemap) {
		ren = ResourceManager::ren;
		this->tilemap = tilemap;
		
		block_tex = ResourceManager::LoadTexture("Graphics/unitinfoblockrect.png");
		SDL_QueryTexture(block_tex, nullptr, nullptr, &block_rect.w, &block_rect.h);
		block_rect.x = 0;
		block_rect.y = scr_height - block_rect.h;

		hp_tex = ResourceManager::LoadTexture("Graphics/unitinfohpbar.png");
		SDL_QueryTexture(hp_tex, nullptr, nullptr, &hp_rect.w, &hp_rect.h);
		hp_rect.x = block_rect.x + 3 * block_rect.w / 4 - hp_rect.w / 2;
		hp_rect.y = block_rect.y + block_rect.h / 4 - hp_rect.h / 2;
		curr_hp_rect = hp_rect;

		sp_tex = ResourceManager::LoadTexture("Graphic/unitinfospbar.png");
		SDL_QueryTexture(sp_tex, nullptr, nullptr, &sp_rect.w, &sp_rect.h);
		sp_rect.x = hp_rect.x;
		sp_rect.y = block_rect.y + 3 * block_rect.h / 4 - hp_rect.h / 2;
		curr_sp_rect = sp_rect;

		portrait_tex = ResourceManager::LoadTexture("Graphics/unitinfoportrait.png");
		SDL_QueryTexture(portrait_tex, nullptr, nullptr, &portrait_rect.w, &portrait_rect.h);
		portrait_rect.x = block_rect.x + block_rect.w / 4 - portrait_rect.w / 4;
		portrait_rect.y = block_rect.y + block_rect.h / 2 - portrait_rect.h / 2;
	};
	~UnitInfoBlock() {};

	void OnUpdate(double delta) {
		
	};

	void OnRender() {
		SDL_RenderCopy(ren, block_tex, nullptr, &block_rect);
		SDL_RenderCopy(ren, hp_tex, &curr_hp_rect, &hp_rect);
		SDL_RenderCopy(ren, sp_tex, &curr_sp_rect, &sp_rect);
		SDL_RenderCopy(ren, portrait_tex, nullptr, &portrait_rect);
	}

private:

	// logic
	BoxTileMap* tilemap;
	Unit* currentUnit;


	// render
	SDL_Renderer* ren;

	SDL_Texture* block_tex;
	SDL_Rect block_rect;

	SDL_Texture* portrait_tex;
	SDL_Rect portrait_rect;
	
	SDL_Texture* hp_tex;
	SDL_Rect hp_rect;
	SDL_Rect curr_hp_rect;

	SDL_Texture* sp_tex;
	SDL_Rect sp_rect;
	SDL_Rect curr_sp_rect;

};