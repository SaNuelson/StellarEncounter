#include "stdlibs.h"
#include "Button.h"

using namespace std;

SDL_Window * win = nullptr;
SDL_Renderer * ren = nullptr;
bool quit = false;

vector<Button> buttons;

void Quit() {
	quit = true;
}

int main() {

	vector<Button> buttons;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG != IMG_INIT_PNG) {
		cout << "IMG_Init Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 2;
	}

	if (TTF_Init() != 0) {
		cout << "TTF_Init Error: " << SDL_GetError() << endl;
		IMG_Quit();
		SDL_Quit();
		return 3;
	}

	win = SDL_CreateWindow("UIWindow", 50, 50, 1800, 900, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		SDL_DestroyWindow(win);
		return -2;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == nullptr) {
		cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		return -1;
	}

	ResourceManager::Init(ren);

	// Add new testing UIElements here

	buttons.push_back(Button::Default());
	buttons[0].SetRect(20, 20, 250, 80);
	//buttons[0].SetClickFunc(Quit);

	// To here

	SDL_Event e;
	while (!quit) {

		// Render Screen
		SDL_RenderClear(ren);
		for (auto &btn : buttons)
			SDL_RenderCopy(ren, btn.GetButtonTex(), nullptr, &btn.GetRect());
		SDL_RenderPresent(ren);

		// Handle Inputs
		while (SDL_PollEvent(&e)) {

			if (e.type == SDL_QUIT)
				quit = true;
		}

		for (auto &btn : buttons)
			btn.ResolveInput(e);

	}

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	return 0;
}
