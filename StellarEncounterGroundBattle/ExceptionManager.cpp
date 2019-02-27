#include "ExceptionManager.h"

void Managers::ExceptionManager::logSDLError(std::ostream & o, std::string msg) {
	o << msg << SDL_GetError();
}
