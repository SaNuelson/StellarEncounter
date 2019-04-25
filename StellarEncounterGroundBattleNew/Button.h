#pragma once
#include "stdlib.h"
#include "ResourceManager.h"
#include "UIElement.h"

class Button : public UIElement
{
public:

	Button() {};
	Button(std::string btn_caption, SDL_Rect &btn_rect, Sint32 return_code, SDL_Texture * tex_idle, SDL_Texture * tex_hover, SDL_Texture * tex_click) :
		caption(btn_caption), rect(btn_rect), retcode(return_code), idle_tex(tex_idle), hover_tex(tex_hover), click_tex(tex_idle) {};
	Button(std::string btn_caption, SDL_Rect &btn_rect, Sint32 return_code, std::string tex_idle_path, std::string tex_hover_path, std::string tex_click_path) :
		caption(btn_caption), rect(btn_rect), retcode(return_code) {
		idle_tex = ResourceManager::LoadTexture(tex_idle_path);
		hover_tex = ResourceManager::LoadTexture(tex_hover_path);
		click_tex = ResourceManager::LoadTexture(tex_click_path);
	};
	~Button() {};

	static Button Default() {
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 100;
		rect.h = 30;

		Button btn;
		btn.caption = "New_Button";
		btn.rect = rect;
		btn.retcode = 1;
		btn.idle_tex = ResourceManager::LoadTextureWithCaption("Resources/button_idle.png", btn.caption);
		btn.hover_tex = ResourceManager::LoadTextureWithCaption("Resources/button_hover.png", btn.caption);
		btn.click_tex = ResourceManager::LoadTextureWithCaption("Resources/button_click.png", btn.caption);

		return btn;
	}

#pragma region Getters/Setters

	std::string GetCaption() {
		return caption;
	};
	void SetCaption(std::string &new_caption) {
		if (new_caption != "" && new_caption != caption) caption = new_caption;
	};

	SDL_Rect GetRect() {
		return rect;
	}
	void SetRect(SDL_Rect new_rect) {
		rect = new_rect;
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

#pragma endregion

	bool IsInBounds(int &x, int& y) { return (rect.x <= x && x <= rect.x + rect.w &&rect.y <= y && y <= rect.y + rect.h); }

	void ResolveInput(SDL_Event &e) override {
		// idle if not mouse on
		// hover if mouse on && not lmb down
		// click if mouse on && lmb down
		if (IsMouseInBounds()) {
			if ((e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN) || (isMouseHolding && e.type != SDL_MOUSEBUTTONUP)) {
				isMouseHolding = true;
				button_state = 2;
			}
			else {
				if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONUP && button_state == 2) {
					std::cout << "Mouse Press" << std::endl;
					DispatchEvent();
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

	void OnUpdate(double delta) override {
		return;
	}

	void OnRender() override {
		SDL_RenderCopy(ResourceManager::ren, GetButtonTex(), nullptr, &rect);
	}

	void DispatchEvent() override {
		SDL_Event e;
		e.type == SDL_EventType::SDL_USEREVENT;
		e.user.code = retcode;
		e.user.data1 = this;
		SDL_PushEvent(&e);
	}

private:

	std::string caption;

	SDL_Rect rect;

	Sint32 retcode;

	int8_t button_state = 0;

	SDL_Texture * idle_tex;
	SDL_Texture * hover_tex;
	SDL_Texture * click_tex;

	bool isMouseHolding = false;

};

