#pragma once
#include "stdlibs.h"

namespace Managers {

	class EntityManager
	{
	public:

		static int GetEntityID() {  return FreeEntityID++; }



	private:

		static int FreeEntityID;


	};

}

