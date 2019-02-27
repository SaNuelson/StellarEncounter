#pragma once
#include "baselibs.h"
#include "utils.h"

namespace image_control
{

	SDL_Texture * loadTex(const std::string &file, SDL_Renderer * ren);


	// x,y - Destination Coords
	// w,h - Image destination rectangle size
	void renderTex(SDL_Texture * tex, SDL_Renderer * ren, int x, int y, int w, int h); // int x: x position

	// dst - Destination rectangle of image
	// clip - Clipping of source image, null means no clipping
	void renderTex(SDL_Texture * tex, SDL_Renderer * ren, SDL_Rect dst, SDL_Rect * clip = nullptr);

	// x,y - Destination Coords
	// clip - Clipping of source image, null means no clipping
	void renderTex(SDL_Texture * tex, SDL_Renderer * ren, int x, int y, SDL_Rect * clip = nullptr);

	SDL_Texture * renderText(const std::string &msg, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer * ren);

};

