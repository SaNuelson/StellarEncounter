#pragma once
#include "stdlibs.h"
#include "ResourceManager.h"
#include "Constants.h"

class Button
{
public:

	Button(int x, int y, int w, int h, std::string caption, SDL_Renderer * ren);

	SDL_Texture * GetTexture();

	SDL_Rect rect;
	std::string caption;

	SDL_Texture * tex;
	SDL_Texture * tex_hover;
	SDL_Texture * tex_clicked;

	Constants::ButtonState buttonState;

};
