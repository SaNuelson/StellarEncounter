#include "stdlib.h"
#include "Constants.h"
#include "Button.h"

class InGameMenu {
public:
	InGameMenu() {
		rect.w = INGAME_MENU_WIDTH;
		rect.h = INGAME_MENU_HEIGHT;
		rect.x = scr_width / 2 - INGAME_MENU_WIDTH / 2;
		rect.y = scr_height / 2 - INGAME_MENU_HEIGHT / 2;

		int x_offset = (INGAME_MENU_WIDTH - INGAME_MENU_BTN_WIDTH) / 2;
		int y_offset = (INGAME_MENU_HEIGHT - 2 * INGAME_MENU_BTN_HEIGHT) / 3;

		SDL_Rect btn_rect;
		btn_rect.x = rect.x + x_offset;
		btn_rect.y = rect.y + y_offset;
		btn_rect.w = INGAME_MENU_BTN_WIDTH;
		btn_rect.h = INGAME_MENU_BTN_HEIGHT;
		
		btn_resume = ResourceManager::CreateButton();
		btn_resume->SetRect(btn_rect);
		btn_resume->SetCaption("Resume (Esc)");
		btn_resume->SetRetCode(RC_INGAME_MENU_SHOW);
		btn_resume->SetBoundKey(SDLK_ESCAPE);
		
		btn_rect.y += btn_rect.h + y_offset;
		btn_quit = ResourceManager::CreateButton();
		btn_quit->SetRect(btn_rect);
		btn_quit->SetCaption("Quit Game (q)");
		btn_quit->SetRetCode(RC_BACK);
		btn_quit->SetBoundKey(SDLK_q);

		btn_show = ResourceManager::CreateButton();
		btn_show->SetRect(0,0,INGAME_MENU_SBTN_WIDTH,INGAME_MENU_SBTN_HEIGHT);
		btn_show->SetCaption("Menu (Esc)");
		btn_show->SetRetCode(RC_INGAME_MENU_SHOW);
		btn_show->SetBoundKey(SDLK_ESCAPE);

		shade = ResourceManager::LoadTexture(PATH_SHADE, 0);
		tex_rect = ResourceManager::LoadTexture(PATH_INGAME_MENU_RECT);

	};
	~InGameMenu() {};

	void ResolveInput(SDL_Event& e) {

		if (e.type == SDL_USEREVENT) {
			if (e.user.code == RC_INGAME_MENU_SHOW) {
				ChangeShown();
			}
		}

		else if (!shown) {
			btn_show->ResolveInput(e);
		}
		else {
			btn_resume->ResolveInput(e);
			btn_quit->ResolveInput(e);
		}
	}

	void OnRender() {
		if (shown) {
			SDL_RenderCopy(ResourceManager::GetRenderer(), shade, nullptr, nullptr);
			SDL_RenderCopy(ResourceManager::GetRenderer(), tex_rect, nullptr, &rect);
			btn_resume->OnRender();
			btn_quit->OnRender();
		}
		else {
			btn_show->OnRender();
		}
	}

	bool IsShown() {
		return shown;
	}

private:

	void ChangeShown() {
		if (!shown) {
			shown = true;
			ResourceManager::DispatchEvent(RC_PAUSE_GAME, this, nullptr);
		}
		else {
			shown = false;
			ResourceManager::DispatchEvent(RC_RESUME_GAME, this, nullptr);
		}
	}

	Button* btn_show;
	Button* btn_resume;
	Button* btn_quit;

	bool shown = false;

	SDL_Rect rect;
	SDL_Texture* shade = nullptr;
	SDL_Texture* tex_rect = nullptr;

};