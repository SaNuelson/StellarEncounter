#pragma once

#include "stdlib.h"
#include "GameObject.h"
#include "Button.h"

class UnitActionBlock {
public:

	UnitActionBlock() {
		block_tex = ResourceManager::LoadTexture("Graphics/UI/unitactionblock.png");
		rect.x = 200;
		rect.y = 500;
		rect.w = 500;
		rect.h = 200;
	};

	void ResolveInput(SDL_Event& e) {
		// sends to appropriate button
		for (auto& btn : buttons) {
			if (btn.IsMouseInBounds()) {
				btn.ResolveInput(e);
				EventHandled = true;
				break;
			}
		}
	};
	void OnUpdate(double delta) {
		// nothing for now
	};
	void OnRender() {
		SDL_RenderCopy(ResourceManager::ren, block_tex, nullptr, &rect);
		for (auto& btn : buttons)
			btn.OnRender();
	};

	bool IsInBounds(int &x, int& y) { return (rect.x <= x && x <= rect.x + rect.w &&rect.y <= y && y <= rect.y + rect.h); }

	void AddButton(std::string btn_idle_path, std::string btn_hover_path, std::string btn_click_path, std::string caption, bool graphic) { // TODO return_code

		if (graphic) {
			// TODO: implement blitting graphic onto button
		}
		else {
			SDL_Rect rect;
			Button(caption, rect, -1, btn_idle_path, btn_hover_path, btn_click_path);
			ResizeButtons();
		}

	}

	void ResizeButtons() {
		if (buttons.size() == 0)
			return;

		// split space between buttons
		int btn_width = rect.w * 8 / 10 / buttons.size();
		int btn_gap = rect.w * 2 / 10 / (buttons.size() + 1);
		int btn_y = (rect.h - btn_width) / 2;

		// if there are too few buttons, shrink them down so they don't overflow
		if (btn_width > rect.h) {

			btn_width = rect.h * 8 / 10;
			btn_gap = (rect.w - btn_width * buttons.size()) / (buttons.size() + 1);
			btn_y = rect.h / 10;

		}

		for (int i = 0; i < buttons.size(); i++) {
			buttons[i].SetRect(btn_width*i + btn_gap * (i + 1), btn_y, btn_width, btn_width);
		}

	}

private:

	void DispatchEvent() override {};

	SDL_Rect rect;
	SDL_Texture * block_tex;

	std::vector<Button> buttons;

};