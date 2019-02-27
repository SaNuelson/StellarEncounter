#include "WindowManager.h"

using namespace Managers;

SDL_Renderer * WindowManager::ren = nullptr;
SDL_Window * WindowManager::win = nullptr;
Constants::WindowState WindowManager::windowState = Constants::WindowState::Initializing;

int WindowManager::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		ExceptionManager::logSDLError(std::cerr, "SDL_Init");
		OnCleanup();
		return 1;
	}
	/*
	if (IMG_Init(IMG_INIT_PNG) != 0) {
		ExceptionManager::logSDLError(std::cerr, "IMG_Init");
		OnCleanup();
		return 2;
	}
	*/

	win = SDL_CreateWindow("Stellar Encounter - GroundBrawl 0.1", 50, 50, 800, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

	windowState = Constants::Initializing;

	OnLoop();

	return 0;

}

void WindowManager::OnLoop() {

	int xTiles = 8;
	int yTiles = 8;
	int xMargin = 50;
	int yMargin = 50;

	auto tex = ResourceManager::loadTex("Graphics/Tiles.png", ren);
	auto player = ResourceManager::loadTex("Graphics/Player.png",ren);
	int xpos = 50 + Constants::xTileSize / 2;
	int ypos = 50;

	bool quit = false;

	SDL_Event e;
	SDL_Rect mousePos = SDL_Rect();

	while (!quit) {
		while (SDL_PollEvent(&e) == 1) {
			if (e.type == SDL_MOUSEBUTTONDOWN) {

				mousePos = GetClickTilePos(&e);
			}
			/*
			int x = 0, y = 0;
			SDL_GetMouseState(&x, &y);

			x -= 50;
			y -= 50;
			
			mousePos.y = y / 48;
			x -= 40 * mousePos.y;
			mousePos.x = x / 80;
			if (x < 0)
				mousePos.x--;
			/*
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				SDL_Rect newpos = GetClickTilePos(&e);
				xpos = newpos.x * Constants::xTileSize + xMargin;
				ypos = newpos.y * Constants::yTileSize + yMargin;
			}
			else if (e.type == SDL_MOUSEMOTION) {
				mousePos = GetClickTilePos(&e);
			}
			*/
		}

		// red tiles
		for (int x = 0; x < xTiles; ++x) {
			for (int y = 0; y < yTiles; ++y) {
				ResourceManager::renderTex(tex, ren, 0, 0, 80, 64, xMargin + x * Constants::xTileSize, yMargin + y * Constants::yTileSize*1.5f, 80, 64);
			}
		}

		// green tiles
		for (int x = 0; x < xTiles; ++x) {
			for (int y = 0; y < yTiles; ++y) {
				ResourceManager::renderTex(tex, ren, 80, 0, 80, 64, xMargin + (x + 0.5f) * Constants::xTileSize, yMargin + (y + 0.5f) * Constants::yTileSize*1.5f, 80, 64);
			}
		}


		ResourceManager::renderTex(player, ren, 50, 0, 50, 50, mousePos.x*Constants::xTileSize + mousePos.y*40 + xMargin, mousePos.y*48 + yMargin, 80, 64);
		SDL_RenderPresent(ren);
	}

	OnCleanup();

}

SDL_Rect WindowManager::GetClickTilePos(SDL_Event * e) {
	SDL_Rect pos;
	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);

	x -= 50;
	y -= 50;

	pos.y = y / 48;
	x -= 40 * pos.y;
	pos.x = x / 80;
	if (x < 0)
		pos.x--;

	return pos;
}