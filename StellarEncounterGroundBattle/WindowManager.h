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

		static int OnInit(); // initialization function, inits all modules and managers
		static void InitSceneLoop();
		static void OnCleanup(); // cleanups this as well as all used managers and their resources

	private:

		static std::vector<std::shared_ptr<Scene>> scenes;

	};


}

#endif