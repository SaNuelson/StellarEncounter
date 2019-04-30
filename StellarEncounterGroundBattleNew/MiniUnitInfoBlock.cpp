#include "MiniUnitInfoBlock.h"
#include "Unit.h"

MiniUnitInfoBlock::MiniUnitInfoBlock(Unit * owner) {
	this->owner = owner;

	tex = ResourceManager::LoadTexture("Graphics/UI/unitinfoblockrect.png");
	rect.x = owner->position.x;
	rect.y = owner->position.y + owner->position.h;
	rect.w = xTileSize;
	rect.h = yTileBoxSize;

	tex_info = ResourceManager::LoadCaption(owner->toString());
	rect_info = rect;
	rect_info.h = rect.h / 3;

	tex_hp = ResourceManager::LoadTexture("Graphics/UI/unitinfoblockhpbar.png");
	rect_hp = rect_info;
	rect_hp.y += rect_hp.h;

	tex_sp = ResourceManager::LoadTexture("Graphics/UI/unitinfoblockspbar.png");
	rect_sp = rect_hp;
	rect_sp.y += 2 * rect_sp.h;

}

void MiniUnitInfoBlock::OnUpdate(double delta) {
	rect_hp.w = rect_info.w * owner->CurHP / owner->MaxHP;
	rect_sp.w = rect_info.w * owner->CurSP / owner->MaxSP;
}

void MiniUnitInfoBlock::Move() {
	rect.x = owner->position.x;
	rect_info.x = owner->position.x;
	rect_hp.x = owner->position.x;
	rect_sp.x = owner->position.x;
	rect.y = owner->position.y + owner->position.h;
	rect_info.y = rect.y;
	rect_hp.y = rect.y + rect.h / 3;
	rect_sp.y = rect.y + rect.h * 2 / 3;
}

void MiniUnitInfoBlock::OnRender() {
	SDL_RenderCopy(ResourceManager::ren, tex, nullptr, &rect);
	SDL_RenderCopy(ResourceManager::ren, tex_info, nullptr, &rect_info);
	SDL_RenderCopy(ResourceManager::ren, tex_hp, nullptr, &rect_hp);
	SDL_RenderCopy(ResourceManager::ren, tex_sp, nullptr, &rect_sp);
}
