#pragma once
#include "stdlibs.h"
#include "ResourceManager.h"

typedef void (*func)();

class Button
{
public:

	Button() {};
	Button(std::string btn_caption, SDL_Rect &btn_rect, func func_idle, func func_hover, func func_click, SDL_Texture * tex_idle, SDL_Texture * tex_hover, SDL_Texture * tex_click) :
		caption(btn_caption), rect(btn_rect), idle_func(func_idle), hover_func(func_hover), click_func(func_click), idle_tex(tex_idle), hover_tex(tex_hover), click_tex(tex_idle) {};
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
		btn.idle_func = nullptr;
		btn.hover_func = nullptr;
		btn.click_func = nullptr;
		btn.idle_tex = ResourceManager::LoadTexture("Resources/button_idle.png");
		btn.hover_tex = ResourceManager::LoadTexture("Resources/button_hover.png");
		btn.click_tex = ResourceManager::LoadTexture("Resources/button_click.png");

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

	func GetIdleFunc() {
		return idle_func;
	}
	void SetIdleFunc(func func) {
		if (func != nullptr)
			idle_func = func;
	}

	func GetHoverFunc() {
		return hover_func;
	}
	void SetHoverFunc(func func) {
		if (func != nullptr)
			hover_func = func;
	}

	func GetClickFunc() {
		return click_func;
	}
	void SetClickFunc(func func) {
		if (func != nullptr)
			click_func = func;
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

#pragma endregion

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
		if (IsMouseOn()) {
			if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN) {
				button_state = 2;
			}
			else if(e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONUP) {
				if (button_state == 2 && click_func != nullptr) {
					std::cout << "Mouse Press" << std::endl;
					(*click_func)();
				}
				else if (hover_func != nullptr)
					(*hover_func)();
				button_state = 1;
			}
		}
		else
			button_state = 0;
	}

private:

	std::string caption;

	SDL_Rect rect;

	func idle_func;
	func hover_func;
	func click_func;

	int8_t button_state = 0;

	SDL_Texture * idle_tex;
	SDL_Texture * hover_tex;
	SDL_Texture * click_tex;

};

