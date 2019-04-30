#include "UnitStackBlock.h"
#include "Constants.h"
#include "ResourceManager.h"
#include "GroundBattleScene.h"

UnitStackBlock::UnitStackBlock(GroundBattleScene * scene) : scene(scene) {

	tex = ResourceManager::LoadTexture("Graphics/UI/unitinfoblockrect.png");
	rect.x = scr_width - 300;
	rect.y = 0;
	rect.h = scr_height;
	rect.w = 300;

	tex_unit = ResourceManager::LoadTexture("Graphics/UI/button.png");
	rect_unit.w = 280;
	rect_unit.h = 100;
	rect_unit.x = rect.x + 10;
	
	rect_unit_portrait.x = rect_unit.x + 10;
	rect_unit_portrait.h = 80;
	rect_unit_portrait.w = 80;

	tex_unit_hp = ResourceManager::LoadTexture("Graphics/UI/unitinfoblockhpbar.png");
	rect_unit_hp.x = rect_unit.x + 110;
	rect_unit_hp.w = 160;
	rect_unit_hp.h = 30;

	tex_unit_sp = ResourceManager::LoadTexture("Graphics/UI/unitinfoblockspbar.png");
	rect_unit_sp.x = rect_unit_hp.x;
	rect_unit_sp.w = rect_unit_hp.w;
	rect_unit_sp.h = 30;

	SDL_Rect rect;

	SDL_Rect rect_unit;
	SDL_Rect rect_unit_hp;
	SDL_Rect rect_unit_sp;
	SDL_Rect rect_unit_portrait;

}

void UnitStackBlock::OnUpdate(double delta)
{
}

void UnitStackBlock::OnRender()
{
	SDL_RenderCopy(ResourceManager::ren, tex, nullptr, &rect);
	rect_unit.y = 10;
	rect_unit_portrait.y = 20;
	rect_unit_hp.y = 15;
	rect_unit_sp.y = 55;
	for (auto& unit : scene->units) {
		SDL_RenderCopy(ResourceManager::ren, tex_unit, nullptr, &rect_unit);
		SDL_RenderCopy(ResourceManager::ren, unit->textures[unit->currentTexture], nullptr, &rect_unit_portrait);
		SDL_RenderCopy(ResourceManager::ren, tex_unit_hp, nullptr, &rect_unit_hp);
		SDL_RenderCopy(ResourceManager::ren, tex_unit_sp, nullptr, &rect_unit_sp);

		rect_unit.y += rect_unit.h + 10;
		rect_unit_portrait.y += rect_unit.h + 10;
		rect_unit_hp.y += rect_unit.h + 10;
		rect_unit_sp.y += rect_unit.h + 10;
	}
}
