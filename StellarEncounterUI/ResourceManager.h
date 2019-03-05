#pragma once
#include "stdlibs.h"

class ResourceManager
{
public:

	static void Init(SDL_Renderer * renderer);

	static SDL_Texture * LoadTexture(std::string path);

	static void FreeTextures();

private:

	static bool initialized;

	static SDL_Renderer * ren;

	static std::map<std::string, SDL_Texture*> TextureMap;

};

