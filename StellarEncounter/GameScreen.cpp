#include "GameScreen.h"

using namespace std;

GameScreen::GameScreen(){}
GameScreen::~GameScreen() { OnCleanup(); }

int GameScreen::OnInit()
{

	// init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		utils::logSDLError(cout, "SDL_Init");
		return 1;
	}

	// init IMG
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		utils::logSDLError(cout, "IMG_Init");
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	// init TTF
	if (TTF_Init() != 0) {
		utils::logSDLError(cout, "TTF_Init");
		SDL_Quit();
		IMG_Quit();
	}

	// init Window
	win = SDL_CreateWindow("MainWindow", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		utils::logSDLError(cout, "SDL_CreateWindow");
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	// init Renderer
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		utils::logSDLError(cout, "SDL_CreateRenderer");
		SDL_DestroyWindow(win);
		IMG_Quit();
		SDL_Quit();
	}

	windowState = constants::WindowState::Battle;

	OnWindowStateChange();
	OnLoop();

	return 0;
}

void GameScreen::OnLoop() {
	while (windowState != constants::WindowState::Quitting) {
		while (SDL_PollEvent(e)) {
			if (e->type == SDL_QUIT) {
				windowState = constants::WindowState::Quitting;
			}

		}

		OnRender();

	}
}

void GameScreen::OnRender() {
	SDL_RenderClear(ren);
	for (Entity ent : entities) {
		SDL_RenderCopy(ren, ent.tex, nullptr,ent.rect);
	}
	SDL_RenderPresent(ren);
}

void GameScreen::OnWindowStateChange()
{
	string path = utils::getResourcePath("Graphics");

}

void GameScreen::OnCleanup()
{
	// Cleanup
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
