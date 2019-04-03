#pragma once
#include "stdlib.h"

class ResourceManager
{
public:

	static void Init(SDL_Renderer * renderer);

	static SDL_Texture * LoadTexture(std::string path);

	static SDL_Texture * LoadTexture(std::string path, Uint8 alpha);

	static SDL_Texture * LoadTextureWithCaption(std::string path, std::string caption);

	static SDL_Rect CreateRectangle(int x, int y, int w, int h); // for quick creation

	static void FreeTextures();

	static SDL_Renderer * ren;

private:

	static bool initialized;


	static std::map<std::string, SDL_Texture*> TextureMap;

	static TTF_Font * default_font;

};

