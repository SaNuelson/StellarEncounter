#include "UnitStackBlock.h"
#include "Constants.h"
#include "ResourceManager.h"
#include "GroundBattleScene.h"

UnitStackBlock::UnitStackBlock(GroundBattleScene * scene) : scene(scene) {

	tex = ResourceManager::LoadTexture("Graphics/UI/unitinfoblockrect.png");
	rect.x = STACK_BLOCK_X;
	rect.y = STACK_BLOCK_Y;
	rect.h = STACK_BLOCK_H;
	rect.w = STACK_BLOCK_W;

	tex_unit_active = ResourceManager::LoadTexture("Graphics/UI/arrow.png");
	rect_unit_active.w = 50;
	rect_unit_active.h = 50;
	rect_unit_active.x = STACK_BLOCK_X;

	tex_unit = ResourceManager::LoadTexture("Graphics/UI/button.png");
	tex_unit_bg = ResourceManager::LoadTexture("Graphics/UI/button_hover.png");
	rect_unit.w = STACK_BLOCK_BLOCK_W;
	rect_unit.h = STACK_BLOCK_BLOCK_H;
	rect_unit.x = STACK_BLOCK_BLOCK_X;
	
	rect_unit_portrait.x = STACK_BLOCK_PORTRAIT_X;
	rect_unit_portrait.h = STACK_BLOCK_PORTRAIT_H;
	rect_unit_portrait.w = STACK_BLOCK_PORTRAIT_W;

	name_center.x = STACK_BLOCK_NAME_CENTER_X;

	tex_unit_hp = ResourceManager::LoadTexture("Graphics/UI/unitinfoblockhpbar.png");
	rect_unit_hp.x = STACK_BLOCK_BAR_X;
	rect_unit_hp.w = STACK_BLOCK_BAR_W;
	rect_unit_hp.h = STACK_BLOCK_BAR_H;

	tex_unit_sp = ResourceManager::LoadTexture("Graphics/UI/unitinfoblockspbar.png");
	rect_unit_sp.x = STACK_BLOCK_BAR_X;
	rect_unit_sp.w = STACK_BLOCK_BAR_W;
	rect_unit_sp.h = STACK_BLOCK_BAR_H;

	tex_unit_ap = ResourceManager::LoadTexture("Graphics/UI/unitinfoblockapbar.png");
	rect_unit_ap.x = STACK_BLOCK_BAR_X;
	rect_unit_ap.w = STACK_BLOCK_BAR_W;
	rect_unit_ap.h = STACK_BLOCK_BAR_H;

}

void UnitStackBlock::Populate() {

	widths.clear();
	captions.clear();

	for (auto& unit : scene->units) {
		std::vector<int> line;
		line.push_back(unit->CurHP * rect_unit_hp.w / unit->MaxHP);
		line.push_back(unit->CurSP * rect_unit_sp.w / unit->MaxSP);
		line.push_back(unit->CurAP * rect_unit_ap.w / unit->MaxAP);
		widths.push_back(line);

		std::vector<SDL_Texture*> caption_line;
		caption_line.push_back(ResourceManager::LoadCaption(std::to_string(unit->CurHP) + "/" + std::to_string(unit->MaxHP)));
		caption_line.push_back(ResourceManager::LoadCaption(std::to_string(unit->CurSP) + "/" + std::to_string(unit->MaxSP)));
		caption_line.push_back(ResourceManager::LoadCaption(std::to_string(unit->CurAP) + "/" + std::to_string(unit->MaxAP)));
		captions.push_back(caption_line);
	}
}

void UnitStackBlock::Reload()
{

}

void UnitStackBlock::ResolveInput(SDL_Event& e)
{
	if (e.type == SDL_USEREVENT && e.user.code == RC_UNIT_STAT_CHANGE) {

		if (scene->units.size() != widths.size()) {
			Populate();
		}

		for (int i = 0; i < scene->units.size(); i++) {
			if (scene->units[i] == (Unit*)e.user.data1) {
				widths[i][0] = scene->units[i]->CurHP * rect_unit_hp.w / scene->units[i]->MaxHP;
				widths[i][1] = scene->units[i]->CurSP * rect_unit_sp.w / scene->units[i]->MaxSP;
				widths[i][2] = scene->units[i]->CurAP * rect_unit_ap.w / scene->units[i]->MaxAP;

				captions[i][0] = ResourceManager::LoadCaption(std::to_string(scene->units[i]->CurHP) + "/" + std::to_string(scene->units[i]->MaxHP));
				captions[i][1] = ResourceManager::LoadCaption(std::to_string(scene->units[i]->CurSP) + "/" + std::to_string(scene->units[i]->MaxSP));
				captions[i][2] = ResourceManager::LoadCaption(std::to_string(scene->units[i]->CurAP) + "/" + std::to_string(scene->units[i]->MaxAP));
			}
		}
	}
}

void UnitStackBlock::OnUpdate(double delta)
{
}

void UnitStackBlock::OnRender()
{
	SDL_RenderCopy(ResourceManager::GetRenderer(), tex, nullptr, &rect);
	rect_unit.y = STACK_BLOCK_BLOCK_Y;
	rect_unit_portrait.y = STACK_BLOCK_PORTRAIT_Y;
	name_center.y = STACK_BLOCK_NAME_CENTER_Y;
	rect_unit_hp.y = STACK_BLOCK_HP_BAR_Y;
	rect_unit_sp.y = STACK_BLOCK_SP_BAR_Y;
	rect_unit_ap.y = STACK_BLOCK_AP_BAR_Y;
	rect_unit_active.y = STACK_BLOCK_BLOCK_Y + STACK_BLOCK_BLOCK_H / 2 - rect_unit_active.h / 2;

	for (int i = 0; i < widths.size(); i++) {

		SDL_RenderCopy(ResourceManager::GetRenderer(), tex_unit, nullptr, &rect_unit);

		SDL_RenderCopy(ResourceManager::GetRenderer(), tex_unit_bg, nullptr, &rect_unit_portrait);
		SDL_RenderCopy(ResourceManager::GetRenderer(), scene->units[i]->textures[scene->units[i]->currentTexture], nullptr, &rect_unit_portrait);

		SDL_Texture* name_tex = ResourceManager::LoadCaption(scene->units[i]->toString());
		SDL_Rect rect_unit_name;
		SDL_QueryTexture(name_tex, nullptr, nullptr, &rect_unit_name.w, &rect_unit_name.h);
		rect_unit_name.x = name_center.x - rect_unit_name.w / 2;
		rect_unit_name.y = name_center.y - rect_unit_name.h / 2;
		SDL_RenderCopy(ResourceManager::GetRenderer(), name_tex, nullptr, &rect_unit_name);
		
		SDL_Rect rect_caption_hp;
		SDL_QueryTexture(captions[i][0], nullptr, nullptr, &rect_caption_hp.w, &rect_caption_hp.h);
		rect_caption_hp.x = rect_unit_hp.x + rect_unit_hp.w / 2 - rect_caption_hp.w / 2;
		rect_caption_hp.y = rect_unit_hp.y + rect_unit_hp.h / 2 - rect_caption_hp.h / 2;
		rect_unit_hp.w = widths[i][0];
		SDL_RenderCopy(ResourceManager::GetRenderer(), tex_unit_hp, nullptr, &rect_unit_hp);
		SDL_RenderCopy(ResourceManager::GetRenderer(), captions[i][0], nullptr, &rect_caption_hp);

		SDL_Rect rect_caption_sp;
		SDL_QueryTexture(captions[i][1], nullptr, nullptr, &rect_caption_sp.w, &rect_caption_sp.h);
		rect_caption_sp.x = rect_unit_sp.x + rect_unit_sp.w / 2 - rect_caption_sp.w / 2;
		rect_caption_sp.y = rect_unit_sp.y + rect_unit_sp.h / 2 - rect_caption_sp.h / 2;
		rect_unit_sp.w = widths[i][1];
		SDL_RenderCopy(ResourceManager::GetRenderer(), tex_unit_sp, nullptr, &rect_unit_sp);
		SDL_RenderCopy(ResourceManager::GetRenderer(), captions[i][1], nullptr, &rect_caption_sp);

		SDL_Rect rect_caption_ap;
		SDL_QueryTexture(captions[i][2], nullptr, nullptr, &rect_caption_ap.w, &rect_caption_ap.h);
		rect_caption_ap.x = rect_unit_ap.x + rect_unit_ap.w / 2 - rect_caption_ap.w / 2;
		rect_caption_ap.y = rect_unit_ap.y + rect_unit_ap.h / 2 - rect_caption_ap.h / 2;
		rect_unit_ap.w = widths[i][2];
		SDL_RenderCopy(ResourceManager::GetRenderer(), tex_unit_ap, nullptr, &rect_unit_ap);
		SDL_RenderCopy(ResourceManager::GetRenderer(), captions[i][2], nullptr, &rect_caption_ap);

		if (i == scene->currentUnit)
			SDL_RenderCopy(ResourceManager::GetRenderer(), tex_unit_active, nullptr, &rect_unit_active);

		rect_unit_hp.w = STACK_BLOCK_BAR_W;
		rect_unit_ap.w = STACK_BLOCK_BAR_W;
		rect_unit_sp.w = STACK_BLOCK_BAR_W;

		rect_unit.y += STACK_BLOCK_SHIFT_Y;
		rect_unit_portrait.y += STACK_BLOCK_SHIFT_Y;
		name_center.y += STACK_BLOCK_SHIFT_Y;
		rect_unit_hp.y += STACK_BLOCK_SHIFT_Y;
		rect_unit_sp.y += STACK_BLOCK_SHIFT_Y;
		rect_unit_ap.y += STACK_BLOCK_SHIFT_Y;
		rect_unit_active.y += STACK_BLOCK_SHIFT_Y;
	}
}
