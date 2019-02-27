#pragma once
#include "stdlibs.h"

class ResourceManager
{
public:
	static SDL_Texture * loadTex(const std::string &file, SDL_Renderer * ren);

	static void renderTex(SDL_Texture * tex, SDL_Renderer * ren, int x, int y, int w, int h);

	static void renderTex(SDL_Texture* tex, SDL_Renderer* ren, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int dstW, int dstH);

	static void renderTex(SDL_Texture * tex, SDL_Renderer * ren, SDL_Rect dst, SDL_Rect * clip = nullptr);

	static void renderTex(SDL_Texture * tex, SDL_Renderer * ren, int x, int y, SDL_Rect * clip = nullptr);
};

