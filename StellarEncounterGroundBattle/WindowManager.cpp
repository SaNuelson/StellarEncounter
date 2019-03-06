#include "WindowManager.h"

using namespace Managers;

SDL_Renderer * WindowManager::ren = nullptr;
SDL_Window * WindowManager::win = nullptr;
std::vector<std::shared_ptr<Scene>> WindowManager::scenes;

int WindowManager::OnInit() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		ExceptionManager::logSDLError(std::cerr, "SDL_Init");
		OnCleanup();
		return 1;
	}
	
	if ((IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG != IMG_INIT_PNG) {
		ExceptionManager::logSDLError(std::cerr, "IMG_Init");
		OnCleanup();
		return 2;
	}

	if (TTF_Init() != 0) {
		ExceptionManager::logSDLError(std::cerr, "TTF_Init");
		OnCleanup();
		return 3;
	}


	win = SDL_CreateWindow("Stellar Encounter 0.1", 50, 50, Constants::WinWidth, Constants::WinHeight, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		ExceptionManager::logSDLError(std::cerr, "SDL_CreateWindow");
		OnCleanup();
		return 3;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_ACCELERATED);
	if (ren == nullptr) {
		ExceptionManager::logSDLError(std::cerr, "SDL_CreateRenderer");
		OnCleanup();
		return 4;
	}

	ResourceManager::OnInit(ren);

	InitSceneLoop();

	return 0;

}

void Managers::WindowManager::InitSceneLoop()
{
	//scenes.push_back(std::make_shared<MainMenuScene>(ren));
	scenes.push_back(std::make_shared<DemoGameScene>(ren));
	while (!scenes.empty()) {
		auto new_scene = scenes[scenes.size() - 1]->Run();
		if (new_scene == nullptr) {
			scenes.pop_back();
		}
		else {
			scenes.push_back(new_scene);
		}
	}
	OnCleanup();
}

void Managers::WindowManager::OnCleanup() {
	// for now no managers control much data, only resource manager
	ResourceManager::OnCleanup();
	// TODO: send cleanup call down to all managers

	// and standard procedures
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}