#ifndef SE_WINDOW_MANAGER
#define SE_WINDOW_MANAGER

#include "stdlibs.h"
#include "ExceptionManager.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "Button.h"
#include "Scenes.h"

class Scene;

// main class (wasn't supposed to be), takes care of gamestate and appropriate loops, also initialization and cleanup

namespace Managers {

	class WindowManager
	{
	public:
		
		static SDL_Window * win;
		static SDL_Renderer * ren;

		// former methods, used in direct sequence
		static int OnInit();
		static void OnLoopOld(); // obsolete, only used to try rendering hex grid and reading hex clicks, works
		static void OnRender() {};
		static void OnCleanup() {};

		// 2nd gamestate implementation, works (I think), but is too coupled
		static void OnStateChange();
		static void OnMenuLoop();
		static void OnNewGameLoop();
		static void OnBattleLoop();
		// ...other window states...

		// experiment with scenes, currently in use
		static void ExperimentalSceneLoop();

		static Constants::WindowState windowState;

	private:

		static SDL_Event e;

		static std::vector<std::shared_ptr<Scene>> scenes;

	};


}

#endif