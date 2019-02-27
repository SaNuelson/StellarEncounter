#pragma once
#include "stdlibs.h"

namespace Managers {

	class ExceptionManager {

	public:

		static void logSDLError(std::ostream& o, std::string msg);

	};

}