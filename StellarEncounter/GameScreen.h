#pragma once
#include "baselibs.h"
#include "utils.h"
#include "image_control.h"
#include "constants.h"
#include "ResourceManager.h"

class GameScreen
{
public:
	GameScreen();
	~GameScreen();

	SDL_Renderer * ren;
	SDL_Window * win;

	std::map<int, Managers::ResourceDictionary> resourceMap;

	int OnInit();
	void OnCleanup();
	void OnLoop();
	void OnRender();
	void OnWindowStateChange();

	SDL_Event * e;

	vector<Entity> entities;

	constants::WindowState windowState;

};
