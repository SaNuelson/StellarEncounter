#include "ExceptionManager.h"

void Managers::ExceptionManager::logSDLError(std::ostream & o, std::string msg) {
	o << msg << SDL_GetError();
}

void Managers::ExceptionManager::logError(std::string msg)
{
	std::cout << msg << std::endl;
}
