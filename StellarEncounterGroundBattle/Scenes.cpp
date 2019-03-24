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
}

std::shared_ptr<Scene> DemoGameScene::Run()
{

	// setup the game
	tileMap.Init(Constants::level1tilemap, Constants::xTileSize, Constants::xTileSize);

	bool gameover = false;

	while (!gameover) {

		// this will move, hardcoded units created in players
		player.units.push_back(EntityManager::CreateCharacter(player.GetID(), Constants::unit1));
		enemy.units.push_back(EntityManager::CreateCharacter(player.GetID(), Constants::unit2));

		// ask for units from players, create queue, now without initiative
		units.push_back(player.units[0]);
		units.push_back(enemy.units[0]);

		playerturn = (EntityManager::GetCharacter(units[currentUnit])->GetOwner() == player.GetID());

		time_last = time_now;
		time_now = SDL_GetPerformanceCounter();
		delta = (double)((time_now - time_last) * 1000 / (double)SDL_GetPerformanceFrequency());

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT || e.user.code == Constants::EVENT_BATTLE_END) {
				gameover = true;
				// start end-battle sequence
				std::cout << "EAAGONGAOHE" << std::endl;
			}
			else if (playerturn) {
				player.ResolveEvent(e);
			}
			tileMap.ResolveInput(e);
		}

		SDL_RenderClear(ren);

		tileMap.OnRender(ren);
		player.Update(delta);
		enemy.Update(delta);

		SDL_RenderPresent(ren);

	}

	return nullptr;
}
