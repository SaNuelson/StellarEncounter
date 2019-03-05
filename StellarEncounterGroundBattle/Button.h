#pragma once
#include "stdlibs.h"
#include "ResourceManager.h"
#include "Constants.h"

// Button done much better in SEUI
class Button
{
public:

	Button(int x, int y, int w, int h, std::string caption, SDL_Renderer * ren);

	SDL_Texture * GetTexture();

	bool IsPointInBounds(int x, int y);

	SDL_Rect rect;
	std::string caption;

	SDL_Texture * tex;
	SDL_Texture * tex_hover;
	SDL_Texture * tex_clicked;

	Constants::ButtonState buttonState;

	static void GenerateButtonStack(SDL_Renderer*ren, SDL_Rect &srcpos, int offset, bool horizontally, std::vector<std::string> &captions, std::vector<Button> &dst);

};
