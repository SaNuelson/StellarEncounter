#pragma once
#include "stdlib.h"
#include "Constants.h"
#include "ResourceManager.h"

class Unit;

class MiniUnitInfoBlock {
public:

	MiniUnitInfoBlock(Unit* owner);

	void OnUpdate(double delta);

	void Move();

	void OnRender();


private:

	Unit* owner = nullptr;

	SDL_Rect rect;
	SDL_Texture * tex;
	SDL_Rect rect_info;
	SDL_Texture * tex_info;
	SDL_Rect rect_hp;
	SDL_Texture * tex_hp;
	SDL_Rect rect_sp;
	SDL_Texture * tex_sp;

};