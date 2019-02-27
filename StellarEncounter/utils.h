#pragma once
#include "baselibs.h"

namespace utils {

	void logSDLError(std::ostream& os, const std::string &msg);

	std::string getResourcePath(const std::string &subDir = "");

	int InitEverything();
	void QuitEverything();

}