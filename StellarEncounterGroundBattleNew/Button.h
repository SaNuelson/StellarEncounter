#pragma once
#include "stdlib.h"
#include "ResourceManager.h"

// imported from StellarEncounterUI
class Button
{
public:

	Button() {};
	Button(std::string btn_caption, SDL_Rect &btn_rect, Sint32 return_code, std::string tex_idle_path, std::string tex_hover_path, std::string tex_click_path, Sint32 keybind = -1) :
		caption(btn_caption), rect(btn_rect), retcode(return_code), bound_key(keybind) {
		idle_tex = ResourceManager::LoadTexture(tex_idle_path);
		hover_tex = ResourceManager::LoadTexture(tex_hover_path);
		click_tex = ResourceManager::LoadTexture(tex_click_path);
		SetCaption(caption);
	};
	~Button() {};

	static Button Default() {
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 100;
		rect.h = 30;
		SDL_Rect caption_rect;
		caption_rect.x = 5;
		caption_rect.y = 5;
		caption_rect.h = 20;
		caption_rect.w = 90;

		Button btn;
		btn.caption = "New_Button";
		btn.rect = rect;
		btn.caption_rect = caption_rect;
		btn.retcode = 1;
		btn.idle_tex = ResourceManager::LoadTexture("Graphics/UI/button_idle.png");
		btn.hover_tex = ResourceManager::LoadTexture("Graphics/UI/button_hover.png");
		btn.click_tex = ResourceManager::LoadTexture("Graphics/UI/button_click.png");
		btn.caption_tex = ResourceManager::LoadCaption(btn.caption);

		return btn;
	}

	// getters/setters

	std::string GetCaption() {
		return caption;
	};
	void SetCaption(std::string new_caption) {
		if (new_caption != "" && new_caption != caption) caption = new_caption;
		caption_tex = ResourceManager::LoadCaption(caption);
		CenterCaption();
	};

	SDL_Rect GetRect() {
		return rect;
	}
	void SetRect(SDL_Rect new_rect) {
		rect = new_rect;
		CenterCaption();
	}
	void SetRect(int x, int y, int w, int h) {
		if (x != -1) rect.x = x;
		if (y != -1) rect.y = y;
		if (w != -1) rect.w = w;
		if (h != -1) rect.h = h;
	}

	SDL_Texture * GetIdleTex() {
		return idle_tex;
	}
	void SetIdleTex(SDL_Texture * tex) {
		if (tex != nullptr)
			idle_tex = tex;
	}

	SDL_Texture * GetHoverTex() {
		return hover_tex;
	}
	void SetHoverTex(SDL_Texture * tex) {
		if (tex != nullptr)
			hover_tex = tex;
	}

	SDL_Texture * GetClickTex() {
		return click_tex;
	}
	void SetClicktex(SDL_Texture * tex) {
		if (tex != nullptr)
			click_tex = tex;
	}

	SDL_Texture * GetButtonTex() {
		switch (button_state) {
		case 0:
			return idle_tex;
		case 1:
			return hover_tex;
		case 2:
			return click_tex;
		}
	}

	void SetRetCode(Sint32 ret) {
		retcode = ret;
	}
	Sint32 GetRetCode() {
		return retcode;
	}

	Sint32 GetBoundKey() {
		return bound_key;
	}
	void SetBoundKey(Sint32 key) {
		bound_key = key;
	}

	// helpful functions

	bool IsInBounds(int &x, int &y) {
		if (rect.x <= x && x <= rect.x + rect.w && rect.y <= y && y <= rect.y + rect.h)
			return true;
		return false;
	}

	bool IsMouseOn() {
		int x, y;
		SDL_GetMouseState(&x, &y);
		return IsInBounds(x, y);
	};

	void ResolveInput(SDL_Event &e) {
		// idle if not mouse on
		// hover if mouse on && not lmb down
		// click if mouse on && lmb down
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == bound_key) {
			ResourceManager::DispatchEvent(retcode, this, nullptr);
		}
		
		if (IsMouseOn()) {
			if ((e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN) || (isMouseHolding && e.type != SDL_MOUSEBUTTONUP)) {
				isMouseHolding = true;
				button_state = 2;
			}
			else {
				if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONUP && button_state == 2) {
					// std::cout << "Mouse Press" << std::endl;
					ResourceManager::DispatchEvent(retcode, this, nullptr);
				}
				isMouseHolding = false;
				button_state = 1;
			}
		}
		else {
			isMouseHolding = false;
			button_state = 0;
		}
	}

	void OnRender() {
		SDL_RenderCopy(ResourceManager::GetRenderer(), GetButtonTex(), nullptr, &rect);
		if (caption != "") {
			SDL_RenderCopy(ResourceManager::GetRenderer(), caption_tex, nullptr, &caption_rect);
		}
	}

private:

	void CenterCaption() {
		SDL_QueryTexture(caption_tex, nullptr, nullptr, &caption_rect.w, &caption_rect.h);
		auto x_offset = rect.w / 2 - caption_rect.w / 2;
		if (x_offset <= 0) {
			caption_rect.w = rect.w;
			caption_rect.x = rect.x;
		}
		else {
			caption_rect.x = rect.x + x_offset;
		}
		auto y_offset = rect.h / 2 - caption_rect.h / 2;
		if (y_offset <= 0) {
			caption_rect.h = rect.h;
			caption_rect.y = rect.y;
		}
		else {
			caption_rect.y = rect.y + y_offset;
		}
	}

	// graphical layout
	std::string caption;

	SDL_Rect rect;
	SDL_Rect caption_rect;


	SDL_Texture* idle_tex = nullptr;
	SDL_Texture* hover_tex = nullptr;
	SDL_Texture* click_tex = nullptr;
	SDL_Texture* caption_tex = nullptr;

	// logic

	// code to dispatch upon button press
	Sint32 retcode;
	SDL_Keycode bound_key;

	// 0 = default, 1 = hover, 2 = press
	int8_t button_state = 0;
	bool isMouseHolding = false;

};

