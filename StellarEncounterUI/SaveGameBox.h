#pragma once
#include "stdlibs.h"
#include "ResourceManager.h"

class SaveGameBox
{
public:
	SaveGameBox(int &scr_height, int &scr_width, SDL_Renderer * renderer) {
		ren = renderer;
		
		box_rect.x = 30;
		box_rect.y = 30;
		box_rect.w = scr_width - 60;
		box_rect.h = scr_height - 60;

		arrup_rect.x = scr_width - 100;
		arrup_rect.y = 50;
		arrup_rect.w = 50;
		arrup_rect.h = 50;

		arrd_rect.x = scr_width - 100;
		arrd_rect.y = scr_height - 100;
		arrd_rect.w = 50;
		arrd_rect.h = 50;

		slidegap_rect.x = scr_width - 80;
		slidegap_rect.y = 90;
		slidegap_rect.w = 10;
		slidegap_rect.h = scr_height - 190;

		slidebar_rect.x = scr_width - 100;
		slidebar_rect.y = 100;
		slidebar_rect.w = 50;
		slidebar_rect.h = 150;

		item_rect.x = 100;
		item_rect.y = 100;
		item_rect.w = scr_width - 250;
		item_rect.h = (box_rect.h - (shown_items + 4) * 20) / shown_items;

		box_tex = ResourceManager::LoadTexture("Resources/SaveGameBox.png");
		arr_tex = ResourceManager::LoadTexture("Resources/SaveGameArrow.png");
		slidegap_tex = ResourceManager::LoadTexture("Resources/SaveGameSlideBar.png");
		slidebar_tex = ResourceManager::LoadTexture("Resources/SaveGameSlideGap.png");

		// TODO: ResourceManager::LoadSaveGames(&items);
		items.push_back(ResourceManager::LoadTexture("Resources/savegamedebugitem1.png"));
		items.push_back(ResourceManager::LoadTexture("Resources/savegamedebugitem2.png"));
		items.push_back(ResourceManager::LoadTexture("Resources/savegamedebugitem3.png"));
		items.push_back(ResourceManager::LoadTexture("Resources/savegamedebugitem1.png"));
		items.push_back(ResourceManager::LoadTexture("Resources/savegamedebugitem2.png"));
		items.push_back(ResourceManager::LoadTexture("Resources/savegamedebugitem3.png"));
		items.push_back(ResourceManager::LoadTexture("Resources/savegamedebugitem1.png"));
		items.push_back(ResourceManager::LoadTexture("Resources/savegamedebugitem2.png"));
		items.push_back(ResourceManager::LoadTexture("Resources/savegamedebugitem3.png"));

		if (items.size() > 5)
			slide_enabled = true;

	};
	~SaveGameBox() {};

	bool IsInBounds(int &x, int &y, SDL_Rect &el_rect) {
		if (el_rect.x <= x && x <= el_rect.x + el_rect.w && el_rect.y <= y && y <= el_rect.y + el_rect.h)
			return true;
		return false;
	}

	bool IsMouseOn(SDL_Rect &rect) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		return IsInBounds(x, y,rect);
	};

	void ResolveInput(SDL_Event &e) {
		if (e.type == SDL_USEREVENT) {
			// internal program event handling
		}
		else if (IsMouseOn(box_rect)) {

			if (slide_enabled) {
				if (slidebar_focused && e.button.button == SDL_BUTTON_LEFT) {
					int nmy;
					SDL_GetMouseState(nullptr, &nmy);
					int newy = slidebar_rect.y + nmy - my;
					if ( newy >= arrup_rect.y + arrup_rect.h && newy + slidebar_rect.h <= arrd_rect.y) {
						slidebar_rect.y = newy;
						top_item = slidebar_rect.y / (slidegap_rect.h / (items.size() - shown_items));
						std::cout << top_item << std::endl;
						my = nmy;
					}
				}
				else {
					slidebar_focused = false;
					if (IsMouseOn(slidebar_rect)) {
						if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN) {
							slidebar_focused = true;
							SDL_GetMouseState(nullptr, &my);
						}
					}
					if (IsMouseOn(arrup_rect)) {
						if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN)
							if (top_item > 0)
								top_item--;
					}
					else if (IsMouseOn(arrd_rect)) {
						if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN)
							if (items.size() - shown_items > top_item)
								top_item++;
					}
				}
			}
			
			// here check item interaction

		}
	}

	void Render() {
		SDL_RenderCopy(ren, box_tex, nullptr, &box_rect);
		SDL_RenderCopy(ren, slidegap_tex, nullptr, &slidegap_rect);
		SDL_RenderCopy(ren, arr_tex, nullptr, &arrup_rect);
		SDL_RenderCopyEx(ren, arr_tex, nullptr, &arrd_rect, 0, nullptr, SDL_FLIP_VERTICAL);
		SDL_RenderCopy(ren, slidebar_tex, nullptr, &slidebar_rect);
		for (int i = top_item; i < top_item + shown_items; i++) {
			SDL_RenderCopy(ren, items[i], nullptr, &item_rect);
			item_rect.y += item_rect.h + 20;
		}
		item_rect.y = 50;
	}

private:

	SDL_Renderer * ren;

	SDL_Texture * box_tex;
	SDL_Rect box_rect;

	bool slide_enabled = false;

	SDL_Texture * arr_tex;
	SDL_Rect arrup_rect;
	SDL_Rect arrd_rect;

	SDL_Texture * slidegap_tex;
	SDL_Rect slidegap_rect;

	SDL_Texture * slidebar_tex;
	SDL_Rect slidebar_rect;
	bool slidebar_focused = false;
	int my;

	std::vector<SDL_Texture*> items; // TODO: Debug version
	SDL_Rect item_rect;
	int top_item = 0;
	const int shown_items = 3;

	bool lmb_press = false;
	int8_t item_focus = 0;
	/*
		in same order as above:
		0 - none
		1 - box
		2 - arrup
		3 - arrdown
		4 - slidegap
		5 - slidebar
		6 - item1
		7 - item2...
	*/

};

