#include "stdlib.h"
#include "Constants.h"
#include "ResourceManager.h"

#include "ConsoleLogic.h"

#include "Tile.h"

#include "Scene.h"
#include "GroundBattleScene.h"
#include "MainMenuScene.h"

using namespace std;

// ptrs for faster access
Scene* scene = nullptr;
SDL_Window* win = nullptr;
SDL_Renderer* ren = nullptr;

// loop and logic variables
SDL_Event e;
bool quit = false;
bool scene_change = false;
int scene_msg = -1;
Sint32 current_scene = RC_MAIN_MENU;

int main() {

	// init section
	int ret = ResourceManager::InitFramework();
	if (ret != 0)
		return ret;

	ret = ResourceManager::InitWinRen("StellarEncounter v0.1", scr_offset_x, scr_offset_y, scr_width, scr_height, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED);
	if (ret != 0)
		return ret;

	win = ResourceManager::GetWindow();
	ren = ResourceManager::GetRenderer();
	scene = ResourceManager::CreateScene(RC_MAIN_MENU);

	//timer
	Uint64 t_now = SDL_GetPerformanceCounter();
	Uint64 t_last = 0;
	double delta = 0;


	while (!quit) {

		// change scenes if needed
		if (scene_change) {
			scene = ResourceManager::CreateScene(current_scene);
			scene_change = false;
			if (current_scene == RC_MAIN_MENU) {
				scene->SetArgs(scene_msg);
			}
		}

		// calc delta
		t_last = t_now;
		t_now = SDL_GetPerformanceCounter();
		delta = (double)((t_now - t_last) * 1000 / (double)SDL_GetPerformanceFrequency());

		// Handle Inputs
		while (SDL_PollEvent(&e)) {

			scene->ResolveInput(e);

			// enable console input (mostly for debugging for easier creation of demo cases)
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F1) { // e.key.keysym.sym == SDLK_<<KEYBOARD_KEY_CODE>>
				ReadConsole();
			}

			// resolve custom events (here specifically for change between scenes)
			if (e.type == SDL_USEREVENT) {

				if (e.user.code == RC_NEW_GAME) {
					scene_change = true;
					current_scene = RC_NEW_GAME;
				}
				// options screen is currently not implemented
				/* 
				else if (e.user.code == RC_OPTIONS) {
					scene_change = true;
					current_scene = RC_OPTIONS;
				}
				*/
				else if (e.user.code == RC_BACK) {
					if(current_scene == RC_MAIN_MENU)
						quit = true;
					else {
						scene_change = true;
						current_scene = RC_MAIN_MENU;
					}
				}
				else if (e.user.code == RC_TEAM_0_WIN) {
					scene_change = true;
					current_scene = RC_MAIN_MENU;
					scene_msg = 0;
				}
				else if (e.user.code == RC_TEAM_1_WIN) {
					scene_change = true;
					current_scene = RC_MAIN_MENU;
					scene_msg = 1;
				}
			}

			if (e.type == SDL_QUIT)
				quit = true;
		}

		// Update Elements
		scene->OnUpdate(delta);

		// Render Screen
		SDL_RenderClear(ren);
		scene->OnRender();
		SDL_RenderPresent(ren);

	}


	ResourceManager::Quit();
	return 0;
}