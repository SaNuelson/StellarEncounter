#ifndef SE_WINDOW_MANAGER
#define SE_WINDOW_MANAGER

#include "stdlibs.h"
#include "ExceptionManager.h"
#include "EntityManager.h"
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

		static Constants::WindowState windowState;

	};


}

#endif