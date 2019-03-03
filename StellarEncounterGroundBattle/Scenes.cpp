#include "Scenes.h"

MainMenuScene::MainMenuScene(SDL_Renderer * renderer) : ren(renderer) { 
	SDL_Event e; 
	btn_captions = { "New Game", "Load Game", "Options", "Quit Game" };
	SDL_Rect btnStartPos;
	btnStartPos.x = Constants::WinWidth / 2 - Constants::BtnWidth / 2;
	btnStartPos.y = Constants::WinHeight / 2 - Constants::BtnHeight / 2;
	Button::GenerateButtonStack(ren, btnStartPos, Constants::BtnOffset, false, btn_captions, buttons);
	std::cout << "Constructor" << std::endl;
}

std::shared_ptr<Scene> MainMenuScene::Run()
{
	SDL_RendererInfo info;
	SDL_GetRendererInfo(ren, &info);
	std::cout << info.flags << std::endl;
	
	int x, y;
	bool click = false;

	while (true) {

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_MOUSEBUTTONDOWN)
				click = true;
			else
				click = false;
		}

		SDL_GetMouseState(&x, &y);

		for (auto btn : buttons) {
			if (btn.IsPointInBounds(x, y)) {
				if (click) {
					btn.buttonState = Constants::ButtonState::Clicked;
				}
				else {
					if (btn.buttonState == Constants::ButtonState::Clicked) // from clicked to focus -> invoke button
						return GetNewScene(&btn);
					btn.buttonState = Constants::ButtonState::Focused;
				}
			}
			else
				btn.buttonState = Constants::ButtonState::Idle;
		}

	}

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
