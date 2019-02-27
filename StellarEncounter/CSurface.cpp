#include "CSurface.h"

using namespace std;

CSurface::CSurface() {
}

SDL_Surface* CSurface::OnLoad(const char* File) {
	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Return = NULL;

	if ((Surf_Temp = SDL_LoadBMP(File)) == NULL) {
		cout << "Error in CSurface - LoadBMP - " << File << endl;
		return NULL;
	}

	Surf_Return = SDL_ConvertSurfaceFormat(Surf_Temp,SDL_PIXELFORMAT_BGR888,0);

	if (Surf_Return == NULL) {
		cout << "Error in CSurface - ConvertSurfaceFormat" << endl;
		return NULL;
	}

	SDL_FreeSurface(Surf_Temp);

	return Surf_Return;
}

bool CSurface::OnDraw(SDL_Surface * Surf_Dest, SDL_Surface * Surf_Src, int X, int Y) {
	if (Surf_Dest == NULL || Surf_Src == NULL) {
		return false;
	}

	SDL_Rect DestR;
	DestR.x = X;
	DestR.y = Y;

	SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

	return true;

}