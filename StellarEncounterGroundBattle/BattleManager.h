#ifndef SE_BATTLE_MANAGER
#define SE_BATTLE_MANAGER

#include "stdlibs.h"
#include "Constants.h"

// currently not in use, should take care of turns, AI, movement on map... probably redundant and ought to be removed soon.

namespace Managers {

	class BattleManager
	{
	public:

		Constants::BattleState battleState;

		int OnInit();
		void CreateTiles();
		void CreateUnits();

	};

}

#endif