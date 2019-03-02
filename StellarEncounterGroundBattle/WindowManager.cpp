#include "WindowManager.h"

using namespace Managers;

SDL_Renderer * WindowManager::ren = nullptr;
SDL_Window * WindowManager::win = nullptr;
Constants::WindowState WindowManager::windowState = Constants::WindowState::Initializing;
SDL_Event WindowManager::e;

int WindowManager::OnInit()
{

	windowState = Constants::Initializing;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		ExceptionManager::logSDLError(std::cerr, "SDL_Init");
		OnCleanup();
		return 1;
	}
	
	if ((IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG != IMG_INIT_PNG) {
		ExceptionManager::logSDLError(std::cerr, "IMG_Init");
		OnCleanup();
		return 2;
	}

	if (TTF_Init() != 0) {
		ExceptionManager::logSDLError(std::cerr, "TTF_Init");
		OnCleanup();
		return 3;
	}


	win = SDL_CreateWindow("Stellar Encounter - GroundBrawl 0.1", 50, 50, Constants::WinWidth, Constants::WinHeight, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		ExceptionManager::logSDLError(std::cerr, "SDL_CreateWindow");
		OnCleanup();
		return 3;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_ACCELERATED);
	if (ren == nullptr) {
		ExceptionManager::logSDLError(std::cerr, "SDL_CreateRenderer");
		OnCleanup();
		return 4;
	}

	windowState = Constants::WindowState::Menu;

	OnStateChange();

	return 0;

}

void WindowManager::OnStateChange() {

	switch (windowState) {
	case Constants::WindowState::Menu:
		OnMenuLoop();
		break;
	case Constants::WindowState::Battle:
		OnBattleLoop();
		break;
	case Constants::WindowState::Quitting:
		return;
	}

}

void WindowManager::OnLoopOld() {
	
	int xTiles = 8;
	int yTiles = 8;
	int xMargin = 50;
	int yMargin = 50;

	auto tex = ResourceManager::loadTex("Graphics/t1.png", ren);
	auto tex2 = ResourceManager::loadTex("Graphics/t2.png", ren);;
	auto player = ResourceManager::loadTex("Graphics/demon.png",ren);
	int xpos = 50 + Constants::xTileSize / 2;
	int ypos = 50;

	bool quit = false;

	SDL_Event e;
	SDL_Rect mousePos = SDL_Rect();

	while (!quit) {
		SDL_RenderClear(ren);


		while (SDL_PollEvent(&e) == 1) {
			if (e.type == SDL_MOUSEBUTTONDOWN) {

				mousePos = EntityManager::GetMouseHex(&e);
				std::cout << mousePos.x << " " << mousePos.y << std::endl;
			}
		}

		// red tiles
		for (int x = 0; x < xTiles; ++x) {
			for (int y = 0; y < yTiles; ++y) {
				ResourceManager::renderTex(tex, ren, 0, 0, 80, 64, xMargin + x * Constants::xTileSize, yMargin + y * Constants::yTileSize*1.5f, 80, 64);
			}
		}

		// green tiles
		for (int x = 0; x < xTiles; ++x) {
			for (int y = 0; y < yTiles; ++y) {
				ResourceManager::renderTex(tex2, ren, 0, 0, 80, 64, xMargin + (x + 0.5f) * Constants::xTileSize, yMargin + (y + 0.5f) * Constants::yTileSize*1.5f, 80, 64);
			}
		}


		ResourceManager::renderTex(player, ren, 50, 0, 50, 50, mousePos.x*Constants::xTileSize + mousePos.y*40 + xMargin, mousePos.y*48 + yMargin, 80, 64);
		SDL_RenderPresent(ren);
	}

	OnCleanup();

}

void Managers::WindowManager::OnMenuLoop() {

	int btn_x = Constants::WinWidth / 2 - Constants::BtnWidth / 2;
	int btn_y = Constants::WinHeight / 2 - Constants::BtnHeight / 2;

	std::vector<Button> buttons;
	buttons.push_back(Button(btn_x, btn_y, Constants::BtnWidth, Constants::BtnHeight, "New Game", ren));
	buttons.push_back(Button(btn_x, btn_y + Constants::BtnHeight + Constants::BtnOffset, Constants::BtnWidth, Constants::BtnHeight, "Load Game", ren));
	buttons.push_back(Button(btn_x, btn_y + Constants::BtnHeight * 2 + Constants::BtnOffset * 2, Constants::BtnWidth, Constants::BtnHeight, "Options", ren));
	buttons.push_back(Button(btn_x, btn_y + Constants::BtnHeight * 3 + Constants::BtnOffset * 3, Constants::BtnWidth, Constants::BtnHeight, "Quit", ren));

	bool change = false;
	bool click = false;
	bool key_pressed = false;
	int hover = 0;

	while (!change) {
		SDL_RenderClear(ren);

		if (hover < 0)
			hover = 0;
		else if (hover >= buttons.size())
			hover = buttons.size() - 1;

		for (int i = 0; i < buttons.size(); i++) {
			if (hover == i) {
				if (click)
					buttons[i].buttonState = Constants::ButtonState::Clicked;
				else
					buttons[i].buttonState = Constants::ButtonState::Focused;
			}
			else
				buttons[i].buttonState = Constants::ButtonState::Idle;
		}

		for (int i = 0; i < buttons.size(); i++) {
			SDL_RenderCopy(ren, buttons[i].GetTexture(), nullptr, &buttons[i].rect);
		}
		SDL_RenderPresent(ren);

		int x, y;
		SDL_GetMouseState(&x, &y);

		for (int i = 0; i < buttons.size(); i++) {
			if (buttons[i].IsPointInBounds(x,y)) {
				hover = i;
			}
		}

		while (SDL_PollEvent(&e)) {
			if (e.button.button == SDL_BUTTON_LEFT && hover != -1) {
				click = true;
			}
			else {
				click = false;
			}
			if ((e.type == SDL_MOUSEBUTTONUP && hover != -1) || (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE))) {
				// TODO: Handle Button Clicks
				std::cout << "Click" << std::endl;
			}
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN && e.key.repeat == 0) {
				hover++;
			}
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP && e.key.repeat == 0) {
				hover--;
			}
			else if (e.type == SDL_QUIT) {
				change = true;
			}
		}
	}

}
/*
void Managers::WindowManager::OnMenuLoop()
{
	int btn_x = Constants::WinWidth / 2 - Constants::BtnWidth / 2;
	int btn_y = Constants::WinHeight / 2 - Constants::BtnHeight / 2;

	std::vector<std::string> btn_captions = { "New Game", "Load Game", "Options", "Quit Game" };
	std::vector<SDL_Rect> btn_rects;
	std::vector<SDL_Texture*> btns;
	std::vector<SDL_Texture*> btns_hover;
	std::vector<SDL_Texture*> btns_clicked;

	int hover = -1;
	bool click = false;
	bool is_on_button = false;
	

	for (int i = 0; i < btn_captions.size(); ++i) {
		SDL_Rect rect = ResourceManager::CreateRect(btn_x, btn_y + i * (Constants::BtnHeight + Constants::BtnOffset), Constants::BtnWidth, Constants::BtnHeight);
		btn_rects.push_back(rect);
		btns.push_back(ResourceManager::CreateButton(ren, rect, btn_captions[i], ""));
		btns_hover.push_back(ResourceManager::CreateButton(ren, rect, btn_captions[i], "hover"));
		btns_clicked.push_back(ResourceManager::CreateButton(ren, rect, btn_captions[i], "clicked"));
	}
	
	bool change = false;

	while (!change) {
		SDL_RenderClear(ren);
		for (int i = 0; i < btns.size(); i++) {
			if (i == hover && !click) {
				SDL_RenderCopy(ren, btns_hover[i], nullptr, &btn_rects[i]);
			}
			else if (i == hover && click) {
				SDL_RenderCopy(ren, btns_clicked[i], nullptr, &btn_rects[i]);
			}
			else {
				SDL_RenderCopy(ren, btns[i], nullptr, &btn_rects[i]);
			}
		}
		SDL_RenderPresent(ren); 
		
		int x, y;
		SDL_GetMouseState(&x, &y);
		is_on_button = false;
		for (int i = 0; i < btn_rects.size(); i++) {
			if (btn_rects[i].x < x && x < btn_rects[i].x + btn_rects[i].w && btn_rects[i].y < y && y < btn_rects[i].y + btn_rects[i].h) {
				// mouse click is in this button
				hover = i;
				is_on_button = true;
			}
		}

		if (!is_on_button)
			hover = -1;

		while (SDL_PollEvent(&e)) {
			if (e.button.button == SDL_BUTTON_LEFT && hover != -1) {
				click = true;
			}
			else {
				click = false;
			}
			if (e.type == SDL_MOUSEBUTTONUP && hover != -1) {
				// TODO: Handle Button Clicks
			}
			if (e.type == SDL_QUIT) {
				change = true;
			}
		}
	}

}
*/
void Managers::WindowManager::OnBattleLoop()
{
}
