#pragma once
#include "stdlib.h"
#include "ResourceManager.h"
#include "UnitInfoBlock.h"
#include "UnitActionBlock.h"

class UIHolder {
public:

	UIHolder() {

		infoblock = UnitInfoBlock();
		actionblock = UnitActionBlock();

	};
	~UIHolder() {};

	void ResolveInput(SDL_Event& e) {

		// mouse event, send based on coords
		if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
			if (infoblock.IsMouseInBounds())
				infoblock.ResolveInput(e);
			else if (actionblock.IsMouseInBounds())
				actionblock.ResolveInput(e);
		}

		// user event, probably handled by external event handler in the future
		else if (e.type == SDL_USEREVENT) {
			// TODO
		}

		// keyboard event, not yet implemented
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
			// TODO TOO
		}

	}
	void OnUpdate(double delta) {
		infoblock.OnUpdate(delta);
		actionblock.OnUpdate(delta);
	};
	void OnRender() {
		infoblock.OnRender();
		actionblock.OnRender();
	}

private:

	UnitInfoBlock infoblock;
	UnitActionBlock actionblock;

};