#include "stdlib.h"
#include "Constants.h"
#include "ResourceManager.h"
#include "Tile.h"

#include "Scene.h"
#include "GroundBattleScene.h"
#include "MainMenuScene.h"

using namespace std;

SDL_Window * win = nullptr;
SDL_Renderer * ren = nullptr;
bool quit = false;
bool scene_change = false;
Sint32 scene_change_rc = -1;

void Quit() {
	quit = true;
}

int main() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG != IMG_INIT_PNG) {
		cout << "IMG_Init Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 2;
	}

	if (TTF_Init() != 0) {
		cout << "TTF_Init Error: " << SDL_GetError() << endl;
		IMG_Quit();
		SDL_Quit();
		return 3;
	}

	win = SDL_CreateWindow("UIWindow", 50, 50, scr_width, scr_height, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		SDL_DestroyWindow(win);
		return -2;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == nullptr) {
		cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		return -1;
	}

	//timer
	Uint64 t_now = SDL_GetPerformanceCounter();
	Uint64 t_last = 0;
	double delta = 0;

	// necessary initialization because... reasons
	ResourceManager::Init(ren, win, nullptr);

	std::unique_ptr<Scene> scene = std::make_unique<MainMenuScene>();
	ResourceManager::scene = scene.get();

	SDL_Event e;

	while (!quit) {

		if (scene_change) {
			if (scene_change_rc == 1) {
				scene = std::make_unique<GroundBattleScene>();
				ResourceManager::scene = scene.get();
			}
			scene_change = false;
			scene_change_rc = -1;
		}

		// calc delta
		t_last = t_now;
		t_now = SDL_GetPerformanceCounter();
		delta = (double)((t_now - t_last) * 1000 / (double)SDL_GetPerformanceFrequency());

		// Handle Inputs
		while (SDL_PollEvent(&e)) {

			scene->ResolveInput(e);

			if (e.type == SDL_USEREVENT) {
				if (e.user.code == RC_NEW_GAME) {
					scene_change = true;
					scene_change_rc = RC_NEW_GAME;
				}
				else if (e.user.code == RC_OPTIONS) {
					// OPTIONS NOT IMPLEMENTED
				}
				else if (e.user.code == RC_QUIT_GAME) {
					quit = true;
				}
			}

			if (e.type == SDL_QUIT)
				quit = true;
		}

		scene->OnUpdate(delta);

		// Render Screen
		SDL_RenderClear(ren);
		scene->OnRender();
		SDL_RenderPresent(ren);

	}


	ResourceManager::Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	return 0;
}
