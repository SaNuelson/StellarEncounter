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
	if (btn->caption == "New Game") // NewGameScene
		return nullptr;
	if (btn->caption == "Load Game") // I mean it's pretty obvious for now...
		return nullptr;
	if (btn->caption == "Options")
		return nullptr;
	if (btn->caption == "Quit Game")
		return nullptr;
}
