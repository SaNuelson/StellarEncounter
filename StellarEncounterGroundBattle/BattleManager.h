#pragma once
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