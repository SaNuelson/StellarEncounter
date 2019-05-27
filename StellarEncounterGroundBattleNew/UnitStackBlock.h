#pragma once
#include "stdlib.h"

class GroundBattleScene;

class UnitStackBlock {

public:

	UnitStackBlock(GroundBattleScene* scene);
	void Populate();
	void Reload();

	void ResolveInput(SDL_Event& e);
	void OnUpdate(double delta);
	void OnRender();

private:

	GroundBattleScene* scene = nullptr;

	SDL_Rect rect;
	
	SDL_Rect rect_unit;
	SDL_Point name_center;
	SDL_Rect rect_unit_hp;
	SDL_Rect rect_unit_sp;
	SDL_Rect rect_unit_ap;
	SDL_Rect rect_unit_portrait;
	SDL_Rect rect_unit_active;

	SDL_Texture* tex = nullptr;
	SDL_Texture* tex_unit = nullptr;
	SDL_Texture* tex_unit_active = nullptr;
	SDL_Texture* tex_unit_name = nullptr;
	SDL_Texture* tex_unit_bg = nullptr;
	SDL_Texture* tex_unit_hp = nullptr;
	SDL_Texture* tex_unit_sp = nullptr;
	SDL_Texture* tex_unit_ap = nullptr;

	std::vector<std::vector<int>> widths;
	std::vector<std::vector<SDL_Texture*>> captions;

};