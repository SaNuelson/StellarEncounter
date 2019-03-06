#pragma once
#include "stdlibs.h"
#include "ResourceManager.h"

typedef void(*func)();

class EnergyFocusTriangle
{
public:

	EnergyFocusTriangle() {};

	static EnergyFocusTriangle Default() {
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 250;
		rect.h = 217;

		SDL_Rect focal_rect;
		focal_rect.x = 115;
		focal_rect.y = 100;
		focal_rect.w = 20;
		focal_rect.h = 17;

		EnergyFocusTriangle eft;
		eft.rect = rect;
		eft.focal_rect = focal_rect;
		eft.pTotal = 200;
		eft.pVector = { 0, 0, 0 };
		eft.move_func = nullptr;
		eft.tex = ResourceManager::LoadTexture("Resources/energyfocus.png");
		eft.focal_tex = ResourceManager::LoadTexture("Resources/energyfocal.png"); // TODO: possibly a better texture
		return eft;
	}

#pragma region Getters/Setters

	SDL_Rect GetRect() {
		return rect;
	}
	void SetRect(SDL_Rect new_rect) {
		if (new_rect.x < 0 || new_rect.y < 0 || new_rect.w < 0 || new_rect.h < 0)
			return;
		focal_rect.w = focal_rect.w * new_rect.w / rect.w;
		focal_rect.h = focal_rect.h * new_rect.h / rect.h;
		focal_rect.x = focal_rect.x * new_rect.x / rect.x;
		focal_rect.y = focal_rect.y * new_rect.y / rect.y;
		rect = new_rect;
	}
	void SetRect(int x, int y, int w, int h) {
		if (x < 0 || y < 0 || w < 0 || h < 0)
			return;
		focal_rect.w = focal_rect.w * w / rect.w;
		focal_rect.h = focal_rect.h * h / rect.h;
		focal_rect.x = focal_rect.x * x / rect.x;
		focal_rect.y = focal_rect.y * y / rect.y;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
	}

	SDL_Rect GetFocalRect() {
		return focal_rect;
	}

	func GetMoveFunc() {
		return move_func;
	}
	void SetClickFunc(func func) {
		if (func != nullptr)
			move_func = func;
	}

	SDL_Texture * GetTexture() {
		return tex;
	}
	void SetTexture(SDL_Texture * texture) {
		tex = texture;
	}
	
	SDL_Texture * GetFocalTexture() {
		return focal_tex;
	}
	void SetFocalTexture(SDL_Texture * texture) {
		focal_tex = texture;
	}

#pragma endregion

	bool IsInBounds(int &x, int &y) {
		// using barycentric weights
		double tbx = rect.w;
		double tby = 0;
		double tcx = rect.w / 2;
		double tcy = - rect.h;
		double tpx = x - rect.x;
		double tpy = y - rect.y - rect.h;

		double d = tbx * tcy - tcx * tby;

		double wa = (tpx * (tby - tcy) + tpy * (tcx - tbx) + tbx * tcy - tcx * tby) / d;
		double wb = (tpx * tcy - tpy * tcx) / d;
		double wc = (tpy*tbx - tpx * tby) / d;

		if (0 <= wa && wa <= 1 && 0 <= wb && wb <= 1 && 0 <= wc && wc <= 1)
			return true;
		return false;

	}

	bool IsMouseOn() {
		int x, y;
		SDL_GetMouseState(&x, &y);
		return IsInBounds(x, y);
	};

	void SetFocalOn(int &x, int &y) {
		focal_rect.x = x - focal_rect.w / 2;
		focal_rect.y = y - focal_rect.h / 2;

		int p1dst = sqrt(pow(x - rect.x - rect.w / 2, 2) + pow(y - rect.y, 2));
		int p2dst = sqrt(pow(x - rect.x, 2) + pow(rect.y + rect.h - y, 2));
		int p3dst = sqrt(pow(rect.x + rect.w - x, 2) + pow(rect.y + rect.h - y, 2));

		double pts2dst = pTotal / (p1dst + p2dst + p3dst);

		pVector[0] = p1dst * pts2dst;
		pVector[1] = p2dst * pts2dst;
		pVector[2] = p3dst * pts2dst;

		SDL_Event e;
		e.user.data1 = &pVector;

		std::cout << "P1: " << p1dst * pts2dst << " P2: " << p2dst * pts2dst << " P3: " << p3dst * pts2dst << std::endl;
	}

	void SetFocalOnMouse() {
		int x, y;
		SDL_GetMouseState(&x, &y);
		SetFocalOn(x, y);
	}

	void ResolveInput(SDL_Event &e) {
		if (IsMouseOn()) {
			if (isMouseHolding) {
				SetFocalOnMouse();
			}
			if ((e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN) || (isMouseHolding && e.type != SDL_MOUSEBUTTONUP)) {
				isMouseHolding = true;
			}
			else {
				isMouseHolding = false;
			}
		}
	}

	void OnRender(SDL_Renderer * ren) {
		SDL_RenderCopy(ren, tex, nullptr, &rect);
		SDL_RenderCopy(ren, focal_tex, nullptr, &focal_rect);
	}

private:

	double pTotal;
	std::vector<double> pVector;

	func move_func;

	SDL_Rect rect;
	SDL_Texture * tex;

	SDL_Rect focal_rect;
	SDL_Texture * focal_tex;

	bool isMouseHolding = false;

};