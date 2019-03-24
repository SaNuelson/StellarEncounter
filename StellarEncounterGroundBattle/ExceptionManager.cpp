#include "ExceptionManager.h"

void ExceptionManager::logSDLError(std::ostream & o, std::string msg) {
	o << msg << SDL_GetError();
}

void ExceptionManager::logError(std::string msg)
{
	std::cout << msg << std::endl;
}
