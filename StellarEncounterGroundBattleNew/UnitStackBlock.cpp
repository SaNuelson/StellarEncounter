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
	tex_unit_bg = ResourceManager::LoadTexture("Graphics/UI/button.png");
	rect_unit.w = 280;
	rect_unit.h = 100;
	rect_unit.x = rect.x + 10;
	
	rect_unit_portrait.x = rect_unit.x + 10;
	rect_unit_portrait.h = 80;
	rect_unit_portrait.w = 80;

	name_center.x = rect_unit.x + 190;

	tex_unit_hp = ResourceManager::LoadTexture("Graphics/UI/unitinfoblockhpbar.png");
	rect_unit_hp.x = rect_unit.x + 110;
	rect_unit_hp.w = 160;
	rect_unit_hp.h = 20;

	tex_unit_sp = ResourceManager::LoadTexture("Graphics/UI/unitinfoblockspbar.png");
	rect_unit_sp.x = rect_unit_hp.x;
	rect_unit_sp.w = rect_unit_hp.w;
	rect_unit_sp.h = 20;

	tex_unit_ap = ResourceManager::LoadTexture("Graphics/UI/unitinfoblockapbar.png");
	rect_unit_ap.x = rect_unit_hp.x;
	rect_unit_ap.w = rect_unit_hp.w;
	rect_unit_ap.h = 20;

}

void UnitStackBlock::Populate() {
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

void UnitStackBlock::ResolveInput(SDL_Event& e)
{
	if (e.type == SDL_USEREVENT && e.user.code == RC_UNIT_STAT_CHANGE) {
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
	SDL_RenderCopy(ResourceManager::ren, tex, nullptr, &rect);
	rect_unit.y = 10;
	rect_unit_portrait.y = 20;
	name_center.y = 25;
	rect_unit_hp.y = 35;
	rect_unit_sp.y = 55;
	rect_unit_ap.y = 75; 
	for (int i = 0; i < widths.size(); i++) {
		

		SDL_RenderCopy(ResourceManager::ren, tex_unit, nullptr, &rect_unit);

		SDL_RenderCopy(ResourceManager::ren, tex_unit_bg, nullptr, &rect_unit_portrait);
		SDL_RenderCopy(ResourceManager::ren, scene->units[i]->textures[scene->units[i]->currentTexture], nullptr, &rect_unit_portrait);

		SDL_Texture* name_tex = ResourceManager::LoadCaption(scene->units[i]->toString());
		SDL_Rect rect_unit_name;
		SDL_QueryTexture(name_tex, nullptr, nullptr, &rect_unit_name.w, &rect_unit_name.h);
		rect_unit_name.x = name_center.x - rect_unit_name.w / 2;
		rect_unit_name.y = name_center.y - rect_unit_name.h / 2;
		SDL_RenderCopy(ResourceManager::ren, name_tex, nullptr, &rect_unit_name);
		
		SDL_Rect rect_caption_hp;
		SDL_QueryTexture(captions[i][0], nullptr, nullptr, &rect_caption_hp.w, &rect_caption_hp.h);
		rect_caption_hp.x = rect_unit_hp.x + rect_unit_hp.w / 2 - rect_caption_hp.w / 2;
		rect_caption_hp.y = rect_unit_hp.y + rect_unit_hp.h / 2 - rect_caption_hp.h / 2;
		rect_unit_hp.w = widths[i][0];
		SDL_RenderCopy(ResourceManager::ren, tex_unit_hp, nullptr, &rect_unit_hp);
		SDL_RenderCopy(ResourceManager::ren, captions[i][0], nullptr, &rect_caption_hp);

		SDL_Rect rect_caption_sp;
		SDL_QueryTexture(captions[i][1], nullptr, nullptr, &rect_caption_sp.w, &rect_caption_sp.h);
		rect_caption_sp.x = rect_unit_sp.x + rect_unit_sp.w / 2 - rect_caption_sp.w / 2;
		rect_caption_sp.y = rect_unit_sp.y + rect_unit_sp.h / 2 - rect_caption_sp.h / 2;
		rect_unit_sp.w = widths[i][1];
		SDL_RenderCopy(ResourceManager::ren, tex_unit_sp, nullptr, &rect_unit_sp);
		SDL_RenderCopy(ResourceManager::ren, captions[i][1], nullptr, &rect_caption_sp);

		SDL_Rect rect_caption_ap;
		SDL_QueryTexture(captions[i][2], nullptr, nullptr, &rect_caption_ap.w, &rect_caption_ap.h);
		rect_caption_ap.x = rect_unit_ap.x + rect_unit_ap.w / 2 - rect_caption_ap.w / 2;
		rect_caption_ap.y = rect_unit_ap.y + rect_unit_ap.h / 2 - rect_caption_ap.h / 2;
		rect_unit_ap.w = widths[i][2];
		SDL_RenderCopy(ResourceManager::ren, tex_unit_ap, nullptr, &rect_unit_ap);
		SDL_RenderCopy(ResourceManager::ren, captions[i][2], nullptr, &rect_caption_ap);

		rect_unit_hp.w = 160;
		rect_unit_ap.w = 160;
		rect_unit_sp.w = 160;

		rect_unit.y += rect_unit.h + 10;
		rect_unit_portrait.y += rect_unit.h + 10;
		name_center.y += rect_unit.h + 10;
		rect_unit_hp.y += rect_unit.h + 10;
		rect_unit_sp.y += rect_unit.h + 10;
		rect_unit_ap.y += rect_unit.h + 10;
	}
}
