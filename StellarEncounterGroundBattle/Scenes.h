#pragma once
#include "stdlibs.h"
#include "Button.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "TileMap.h"

class Scene : public std::enable_shared_from_this<Scene>{
public:

	Scene() {};
	virtual ~Scene() {};
	Scene(SDL_Renderer* renderer) : ren(renderer) {};

	// main method of scene, each inherited class does it's job and returns appropriate scene or nullptr to go back a scene
	virtual std::shared_ptr<Scene> Run() { return nullptr; };

	std::shared_ptr<Scene> getptr() { return shared_from_this(); };

private:

	SDL_Renderer * ren = nullptr;

};

class MainMenuScene : public Scene {
public:

	
	MainMenuScene() = default;
	MainMenuScene(SDL_Renderer * renderer);

	// the whole loop handling input, rendering...
	std::shared_ptr<Scene> Run() override;

	// This was a former way to handle if some button was clicked. Should be rebuilt either with pointer functions in buttons (as in SEUI) or using Events
	std::shared_ptr<Scene> GetNewScene(Button*);

private:

	std::vector<std::string> btn_captions;
	std::vector<Button> buttons;

	SDL_Renderer * ren;
	SDL_Event e;

};

class DemoGameScene : public Scene {
public:

	DemoGameScene() {};
	DemoGameScene(SDL_Renderer * renderer);;

	std::shared_ptr<Scene> Run() override;
	std::shared_ptr<Scene> GetNewScene(Button*) {};

private:

	
	TileMap tileMap;
	SDL_Renderer * ren;
	SDL_Event e;

};