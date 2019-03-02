#ifndef SE_BATTLE_MANAGER
#define SE_BATTLE_MANAGER

#include "stdlibs.h"
#include "Constants.h"

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