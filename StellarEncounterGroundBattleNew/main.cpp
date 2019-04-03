#include "stdlib.h"
#include "ResourceManager.h"
#include "Tiles.h"

using namespace std;

SDL_Window * win = nullptr;
SDL_Renderer * ren = nullptr;
bool quit = false;

int scr_height = 600;
int scr_width = 800;

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

	ResourceManager::Init(ren);
	SDL_Event e;

	bool PlayerTurn = true;
	BoxTileMap tilemap;
	tilemap.Init(level1boxtilemap, xTileSize, xTileSize);
	tilemap.InitDemo();

	int currentUnit = 0;

	while (!quit) {

		// calc delta
		t_last = t_now;
		t_now = SDL_GetPerformanceCounter();
		delta = (double)((t_now - t_last) * 1000 / (double)SDL_GetPerformanceFrequency());

		// Handle Inputs
		while (SDL_PollEvent(&e)) {

			tilemap.ResolveInput(e);

			if (e.type == SDL_QUIT)
				quit = true;
		}

		tilemap.OnUpdate(delta);

		// Render Screen
		SDL_RenderClear(ren);
		tilemap.OnRender(ren);
		SDL_RenderPresent(ren);

	}

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	return 0;
}
