#pragma once
#include "stdlib.h"

class ResourceManager
{
public:

	static void Init(SDL_Renderer * renderer);

	static SDL_Texture * LoadTexture(std::string path);

	static SDL_Texture * LoadTextureWithCaption(std::string path, std::string caption);

	static void FreeTextures();

private:

	static bool initialized;

	static SDL_Renderer * ren;

	static std::map<std::string, SDL_Texture*> TextureMap;

	static TTF_Font * default_font;

};

