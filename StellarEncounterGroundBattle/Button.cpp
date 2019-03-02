#include "Button.h"

Button::Button(int x, int y, int w, int h, std::string caption, SDL_Renderer * ren)
{
	rect = ResourceManager::CreateRect(x, y, w, h);
	buttonState = Constants::ButtonState::Idle;
	caption = caption;
	tex = ResourceManager::CreateButton(ren, rect, caption, "");
	tex_hover = ResourceManager::CreateButton(ren, rect, caption, "hover");
	tex_clicked = ResourceManager::CreateButton(ren, rect, caption, "clicked");
}

SDL_Texture * Button::GetTexture()
{
	switch (buttonState) {
	case Constants::ButtonState::Idle:
		return tex;
	case Constants::ButtonState::Focused:
		return tex_hover;
	case Constants::ButtonState::Clicked:
		return tex_clicked;
	}
}
