#pragma once
#include "baselibs.h"

class CSurface {

public:
	CSurface();

	static SDL_Surface * OnLoad(const char* File);

	static bool OnDraw(SDL_Surface * Surf_Dest, SDL_Surface * Surf_Src, int X, int Y);

};