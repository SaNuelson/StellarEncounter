#ifndef SE_EXCEPTION_MANAGER
#define SE_EXCEPTION_MANAGER

#include "stdlibs.h"

class ExceptionManager {

public:

	static void logSDLError(std::ostream& o, std::string msg);

	static void logError(std::string msg);

};
#endif