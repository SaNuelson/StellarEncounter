#pragma once
#include "stdlibs.h"
#include "ExceptionManager.h"
#include "ResourceManager.h"
#include "Constants.h"

namespace Managers {

	class WindowManager
	{
	public:
		
		static SDL_Window * win;
		static SDL_Renderer * ren;

		static int OnInit();
		static void OnLoop();
		static void OnRender() {};
		static void OnCleanup() {};

		static SDL_Rect GetClickTilePos(SDL_Event * e);

		static Constants::WindowState windowState;

	};


}
