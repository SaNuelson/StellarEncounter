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
		static void OnStateChange();
		static void OnLoopOld(); // obsolete
		static void OnRender() {};
		static void OnCleanup() {};

		static void OnMenuLoop();
		static void OnBattleLoop();
		// other window states...

		static Constants::WindowState windowState;

	private:

		static SDL_Event e;

	};


}

#endif