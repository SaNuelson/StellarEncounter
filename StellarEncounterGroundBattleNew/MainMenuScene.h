#pragma once
#include "stdlib.h"
#include "Scene.h"
#include "ResourceManager.h"

class Button;

class MainMenuScene : public Scene {

public:

	MainMenuScene();

	// Inherited via Scene
	void ResolveInput(SDL_Event& e) override;

	void OnUpdate(double delta) override;

	void OnRender() override;

	// A "redneck" temporary solution to at least write some kind of message about who won the last game
	void SetArgs(int code) override;

private:

	// graphical layout variables
	SDL_Rect bg_rect;
	SDL_Texture* bg;

	SDL_Rect title_rect;
	SDL_Texture* title;

	SDL_Rect subtitle_rect;
	SDL_Texture* subtitle;
	std::string subtitle_caption;
	bool is_subtitle;
	
	std::vector<Button*> buttons;

};