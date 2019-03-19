#include "Scenes.h"

MainMenuScene::MainMenuScene(SDL_Renderer * renderer) : ren(renderer) { 
	SDL_Event e; 
	btn_captions = { "New Game", "Load Game", "Options", "Quit Game" };
	SDL_Rect btnStartPos;
	btnStartPos.x = Constants::WinWidth / 2 - Constants::BtnWidth / 2;
	btnStartPos.y = Constants::WinHeight / 2 - Constants::BtnHeight / 2;
	Button::GenerateButtonStack(ren, btnStartPos, Constants::BtnOffset, false, btn_captions, buttons);
}

std::shared_ptr<Scene> MainMenuScene::Run()
{

	bool change = false;
	bool click = false;
	int hover = 0;

	while (!change) {

		SDL_RenderClear(ren);

		int x, y;
		SDL_GetMouseState(&x, &y);

		for (auto &btn : buttons) {
			if (btn.IsPointInBounds(x,y)) {
				if (click) {
					btn.buttonState = Constants::ButtonState::Clicked;
				}
				else {
					if (btn.buttonState == Constants::ButtonState::Clicked)
						return GetNewScene(&btn);
					btn.buttonState = Constants::ButtonState::Focused;
				}
			}
			else {
				btn.buttonState = Constants::ButtonState::Idle;
			}
		}

		for (auto btn : buttons) {
			SDL_RenderCopy(ren, btn.GetTexture(), nullptr, &btn.rect);
		}
		SDL_RenderPresent(ren);

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_MOUSEBUTTONDOWN)
				click = true;
			else
				click = false;
			if (e.type == SDL_QUIT) {
				change = true;
			}
		}
	}

	return nullptr;
}

std::shared_ptr<Scene> MainMenuScene::GetNewScene(Button * btn)
{
	if (btn->caption == "New Game") { // NewGameScene
		std::cout << "MainMenuScene jumpting to DemoGameScene" << std::endl;
		return std::make_shared<DemoGameScene>(ren);
	}
	if (btn->caption == "Load Game") // I mean it's pretty obvious for now...
		return nullptr;
	if (btn->caption == "Options")
		return nullptr;
	if (btn->caption == "Quit Game")
		return nullptr;
}

DemoGameScene::DemoGameScene(SDL_Renderer * renderer) : ren(renderer) {
	
	tileMap.Init(Constants::level1tilemap, 20, 20);
	/*
	std::string source = Constants::level1tilemap;
	std::string line;
	std::stringstream ss(source);
	int i = 0;
	while (std::getline(ss, line, ',')) {
		TileTexVec2d.push_back(std::vector<SDL_Texture*>());
		for (char c : line) {
			TileTexVec2d[i].push_back(ResourceManager::loadTex(Constants::GetTileCodePath(c - 48)));
		}
		i++;
	}
	*/
}

std::shared_ptr<Scene> DemoGameScene::Run()
{

	bool change = false;

	while (!change) {

		SDL_RenderClear(ren);

		int x, y;
		SDL_GetMouseState(&x, &y);
		
		/*
		SDL_Rect tile_rect;
		tile_rect.x = 0;
		tile_rect.y = 0;
		tile_rect.w = Constants::xTileSize;
		tile_rect.h = Constants::yTileSize;

		bool odd = true;

		for (auto vec : TileTexVec2d) {
			for (auto tile : vec) {
				SDL_RenderCopy(ren, tile, nullptr, &tile_rect);
				tile_rect.x += Constants::xTileSize;
			}
			odd = !odd;
			tile_rect.y += Constants::yTileTopSize + Constants::yTileBoxSize;
			if (odd) {
				tile_rect.x = 0;
			}
			else {
				tile_rect.x = Constants::xTileSize / 2;
			}
		}
		*/
		
		tileMap.OnRender(ren);

		SDL_RenderPresent(ren);

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				change = true;
			}
		}
	}

	return nullptr;
}
