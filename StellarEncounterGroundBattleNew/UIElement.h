#pragma once
#include "stdlib.h"

class UIElement {
public:

	UIElement() {};

	virtual void ResolveInput(SDL_Event &e) {};
	virtual void OnUpdate(double delta) {};
	virtual void OnRender() {};

	virtual bool IsInBounds(int &x, int& y) { return false; }
	virtual bool IsMouseInBounds() {
		int x, y;
		SDL_GetMouseState(&x, &y);
		return IsInBounds(x, y);
	}

private:
	
	virtual void DispatchEvent() {};

};