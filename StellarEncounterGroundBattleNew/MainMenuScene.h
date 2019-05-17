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

private:

	SDL_Rect bg_rect;
	SDL_Texture* bg;

	SDL_Rect title_rect;
	SDL_Texture* title;
	
	std::vector<Button*> buttons;

};