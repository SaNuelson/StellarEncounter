#include "MainMenuScene.h"
#include "Button.h"
#include "Constants.h"

MainMenuScene::MainMenuScene() {

	// lots and lots of layout...
	bg_rect.x = 0;
	bg_rect.y = 0;
	bg_rect.w = scr_width;
	bg_rect.h = scr_height;
	bg = ResourceManager::LoadTexture("Graphics/UI/bg.png");

	title = ResourceManager::LoadCaption("Stellar Encounter (DEMO)");
	SDL_QueryTexture(title, nullptr, nullptr, &title_rect.w, &title_rect.h);
	title_rect.w *= 2;
	title_rect.h *= 2;
	title_rect.x = (scr_width - title_rect.w) / 2;
	title_rect.y = 250;

	SDL_Rect btn_rect;
	btn_rect.w = 250;
	btn_rect.h = 100;
	btn_rect.x = ( scr_width - btn_rect.w ) / 2;
	btn_rect.y = 400;

	auto ng_btn = ResourceManager::CreateButton();
	ng_btn->SetCaption("New Game");
	ng_btn->SetRect(btn_rect);
	ng_btn->SetRetCode(RC_NEW_GAME);
	buttons.push_back(ng_btn);

	btn_rect.y += 120;

	auto op_btn = ResourceManager::CreateButton();
	op_btn->SetCaption("Options");
	op_btn->SetRect(btn_rect);
	op_btn->SetRetCode(RC_OPTIONS);
	buttons.push_back(op_btn);

	btn_rect.y += 120;

	auto ex_btn = ResourceManager::CreateButton();
	ex_btn->SetCaption("Quit Game");
	ex_btn->SetRect(btn_rect);
	ex_btn->SetRetCode(RC_BACK);
	buttons.push_back(ex_btn);

}

void MainMenuScene::ResolveInput(SDL_Event& e)
{
	for (auto& btn : buttons) {
		btn->ResolveInput(e);
	}
}

void MainMenuScene::OnUpdate(double delta) {}

void MainMenuScene::OnRender()
{
	SDL_RenderCopy(ResourceManager::GetRenderer(), bg, nullptr, &bg_rect);
	SDL_RenderCopy(ResourceManager::GetRenderer(), title, nullptr, &title_rect);

	if (is_subtitle)
		SDL_RenderCopy(ResourceManager::GetRenderer(), subtitle, nullptr, &subtitle_rect);

	for (auto& btn : buttons) {
		btn->OnRender();
	}
}

void MainMenuScene::SetArgs(int code)
{
	if (code != -1) {
		subtitle_caption = "Congrats, team " + std::to_string(code) + " won!";
		is_subtitle = true;
	}

	subtitle = ResourceManager::LoadCaption(subtitle_caption);
	SDL_QueryTexture(subtitle, nullptr, nullptr, &subtitle_rect.w, &subtitle_rect.h);
	subtitle_rect.x = (scr_width - subtitle_rect.w) / 2;
	subtitle_rect.y = 350;
}
