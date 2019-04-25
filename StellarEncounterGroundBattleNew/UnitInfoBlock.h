#pragma once
#include "stdlib.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "GameHolder.h"
#include "UIElement.h"
#include "Unit.h"

class UnitInfoBlock : public UIElement {
public:

	UnitInfoBlock() {
		ren = ResourceManager::ren;
		currentUnit = nullptr;

		block_tex = ResourceManager::LoadTexture("Graphics/unitinfoblockrect.png");
		block_rect = GetUnitInfoBlockRect();

		portrait_tex = ResourceManager::LoadTexture("Graphics/unitinfoblockportrait.png");
		portrait_rect.x = block_rect.x + 20;
		portrait_rect.y = block_rect.y + 20;
		portrait_rect.h = 110;
		portrait_rect.w = 110;

		hp_tex = ResourceManager::LoadTexture("Graphics/unitinfoblockhpbar.png");
		hp_rect.x = block_rect.x + 165;
		hp_rect.y = block_rect.y + 15;
		hp_rect.h = 30;
		hp_rect.w = 220;
		curr_hp_rect = hp_rect;

		sp_tex = ResourceManager::LoadTexture("Graphics/unitinfoblockspbar.png");
		sp_rect.x = hp_rect.x;
		sp_rect.y = hp_rect.y + 45;
		sp_rect.h = 30;
		sp_rect.w = hp_rect.w;
		curr_sp_rect = sp_rect;

		ap_tex = ResourceManager::LoadTexture("Graphics/unitinfoblockapbar.png");
		ap_rect.x = hp_rect.x;
		ap_rect.y = hp_rect.y + 90;
		ap_rect.h = 30;
		ap_rect.w = hp_rect.w;
		curr_ap_rect = ap_rect;

		emptybar_tex = ResourceManager::LoadTexture("Graphics/unitinfoblockemptybar.png");
		max_bar_w = curr_ap_rect.w;


	};
	~UnitInfoBlock() {};

	void ResolveInput(SDL_Event& e) override {
		// Contains info for now, so nothing to handle really
		EventHandled = true;
	};

	void OnUpdate(double delta) override{

		if (currentUnit == nullptr) {
			curr_hp_rect.w = 0;
			curr_ap_rect.w = 0;
			curr_sp_rect.w = 0;
			return;
		}

		curr_hp_rect.w = max_bar_w * currentUnit->CurHP / currentUnit->MaxHP;
		curr_ap_rect.w = max_bar_w * currentUnit->CurAP / currentUnit->MaxAP;
		curr_sp_rect.w = max_bar_w * currentUnit->CurSP / currentUnit->MaxSP;

	};

	void OnRender() override{
		SDL_RenderCopy(ren, block_tex, nullptr, &block_rect);
		
		SDL_RenderCopy(ren, emptybar_tex, nullptr, &hp_rect);
		SDL_RenderCopy(ren, hp_tex, nullptr, &curr_hp_rect);
		if(currentUnit != nullptr)
			ResourceManager::RenderText(std::to_string(currentUnit->CurHP), hp_rect);

		SDL_RenderCopy(ren, emptybar_tex, nullptr, &sp_rect);
		SDL_RenderCopy(ren, sp_tex, nullptr, &curr_sp_rect);
		if(currentUnit != nullptr)
			ResourceManager::RenderText(std::to_string(currentUnit->CurSP), sp_rect);
		
		SDL_RenderCopy(ren, emptybar_tex, nullptr, &ap_rect);
		SDL_RenderCopy(ren, ap_tex, nullptr, &curr_ap_rect);
		if(currentUnit != nullptr)
			ResourceManager::RenderText(std::to_string(currentUnit->CurAP), ap_rect);
		
		SDL_RenderCopy(ren, portrait_tex, nullptr, &portrait_rect);
	}

	bool IsInBounds(int &x, int& y) { return (block_rect.x <= x && x <= block_rect.x + block_rect.w &&block_rect.y <= y && y <= block_rect.y + block_rect.h); }


private:

	void DispatchEvent() override {};

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

	SDL_Texture* ap_tex;
	SDL_Rect ap_rect;
	SDL_Rect curr_ap_rect;

	SDL_Texture* emptybar_tex;
	int max_bar_w;

};