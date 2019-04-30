#pragma once
#include "stdlib.h"

class GroundBattleScene;

class UnitStackBlock {

public:

	UnitStackBlock(GroundBattleScene* scene);;

	void OnUpdate(double delta);
	void OnRender();

private:

	GroundBattleScene* scene = nullptr;

	SDL_Rect rect;
	
	SDL_Rect rect_unit;
	SDL_Rect rect_unit_hp;
	SDL_Rect rect_unit_sp;
	SDL_Rect rect_unit_portrait;

	SDL_Texture* tex = nullptr;
	SDL_Texture* tex_unit = nullptr;
	SDL_Texture* tex_unit_hp = nullptr;
	SDL_Texture* tex_unit_sp = nullptr;

};