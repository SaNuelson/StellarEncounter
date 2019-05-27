#pragma once
#include "stdlib.h"

class GroundBattleScene;

// shows panel (on right side by default) filled with units along with their data and arrow indicating current unit
class UnitStackBlock {

public:

	UnitStackBlock(GroundBattleScene* scene);
	// set up all units
	void Populate();

	void ResolveInput(SDL_Event& e);
	void OnUpdate(double delta);
	void OnRender();

private:

	GroundBattleScene* scene = nullptr;

	// widths are current_health / max_health * bar_width    for each unit
	std::vector<std::vector<int>> widths;
	// Unit names along with textual representation of their data
	std::vector<std::vector<SDL_Texture*>> captions;

	// graphical layout
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


};