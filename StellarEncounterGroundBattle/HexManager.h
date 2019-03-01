#pragma once
#include "stdlibs.h"
#include "Tile.h"
#include "Constants.h"

namespace Managers {


	class HexManager
	{
	public:

		static int OnInit();
		

		static void CreateField(SDL_Renderer* ren, std::string levelSource); // Debug only
		static void ClearField();
		
		static SDL_Rect GetMouseHex(SDL_Event * ev);

		static void HighlightMouseHex(SDL_Event * ev) {};

	private:

		static std::vector<std::vector<SDL_Texture*>> tilemap;

	};


}
