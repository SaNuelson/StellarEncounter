#include "UnitInfoBlock.h"
#include "GameObject.h"
#include "Unit.h"
#include "Item.h"
#include "GroundBattleScene.h"
#include "Tilemap.h"

UnitInfoBlock::UnitInfoBlock(GroundBattleScene * scene) {
	ren = ResourceManager::ren;
	this->scene = scene;

	block_tex = ResourceManager::LoadTexture("Graphics/unitinfoblockrect.png");
	block_rect.h = 150;
	block_rect.w = 400;
	block_rect.x = 0;
	block_rect.y = scr_height - block_rect.h;

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


}

void UnitInfoBlock::OnUpdate(double delta) {
	// if change

	currentUnit = scene->GetCurrentUnit();
	if (currentUnit != nullptr) {

		curr_hp_rect.w = max_bar_w * currentUnit->CurHP / currentUnit->MaxHP;
		curr_ap_rect.w = max_bar_w * currentUnit->CurAP / currentUnit->MaxAP;
		curr_sp_rect.w = max_bar_w * currentUnit->CurSP / currentUnit->MaxSP;

	}
	else {

		curr_hp_rect.w = 0;
		curr_sp_rect.w = 0;
		curr_ap_rect.w = 0;

	}

}

void UnitInfoBlock::OnRender() {
	SDL_RenderCopy(ren, block_tex, nullptr, &block_rect);

	SDL_RenderCopy(ren, emptybar_tex, nullptr, &hp_rect);
	SDL_RenderCopy(ren, hp_tex, nullptr, &curr_hp_rect);
	ResourceManager::RenderText(std::to_string(currentUnit->CurHP), hp_rect);

	SDL_RenderCopy(ren, emptybar_tex, nullptr, &sp_rect);
	SDL_RenderCopy(ren, sp_tex, nullptr, &curr_sp_rect);
	ResourceManager::RenderText(std::to_string(currentUnit->CurSP), sp_rect);

	SDL_RenderCopy(ren, emptybar_tex, nullptr, &ap_rect);
	SDL_RenderCopy(ren, ap_tex, nullptr, &curr_ap_rect);
	ResourceManager::RenderText(std::to_string(currentUnit->CurAP), ap_rect);

	SDL_RenderCopy(ren, portrait_tex, nullptr, &portrait_rect);
}
