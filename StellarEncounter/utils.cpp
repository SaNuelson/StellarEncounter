#include "utils.h"

using namespace std;

void utils::logSDLError(std::ostream & os, const std::string & msg)
{
	os << msg << " error: " << SDL_GetError() << endl;
}

std::string utils::getResourcePath(const std::string &subDir) {
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	static std::string baseRes;
	if (baseRes.empty()) {
		char *basePath = SDL_GetBasePath();
		if (basePath) {
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		size_t pos = baseRes.rfind("bin");
		baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
	}
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}

int utils::InitEverything()
{
	// init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		utils::logSDLError(cout, "SDL_Init");
		return 1;
	}

	// init IMG
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		utils::logSDLError(cout, "IMG_Init");
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	// init TTF
	if (TTF_Init() != 0) {
		utils::logSDLError(cout, "TTF_Init");
		SDL_Quit();
		IMG_Quit();
		TTF_Quit();
	}
}

void utils::QuitEverything() {

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

}

