#pragma once
#include "stdlibs.h"
#include "Button.h"
#include "ResourceManager.h"
#include "WindowManager.h"

class Scene : public std::enable_shared_from_this<Scene>{
public:

	Scene() {};
	virtual ~Scene() {};
	Scene(SDL_Renderer* renderer) : ren(renderer) {};

	virtual std::shared_ptr<Scene> Run() { return nullptr; };

	std::shared_ptr<Scene> getptr() { return shared_from_this(); };

private:

	SDL_Renderer * ren = nullptr;

};

class MainMenuScene : public Scene {
public:

	
	MainMenuScene() = default;
	MainMenuScene(SDL_Renderer * renderer);;

	std::shared_ptr<Scene> Run() override;
	std::shared_ptr<Scene> GetNewScene(Button*);

private:

	std::vector<std::string> btn_captions;
	std::vector<Button> buttons;

	SDL_Renderer * ren;
	SDL_Event e;

};