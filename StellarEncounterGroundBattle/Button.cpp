#include "Button.h"

Button::Button(int x, int y, int w, int h, std::string caption, SDL_Renderer * ren) {
	rect = ResourceManager::CreateRect(x, y, w, h);
	buttonState = Constants::ButtonState::Idle;
	caption = caption;
	tex = ResourceManager::CreateButton(rect, caption, "");
	tex_hover = ResourceManager::CreateButton(rect, caption, "hover");
	tex_clicked = ResourceManager::CreateButton(rect, caption, "clicked");
}

SDL_Texture * Button::GetTexture() {
	switch (buttonState) {
	case Constants::ButtonState::Idle:
		return tex;
	case Constants::ButtonState::Focused:
		return tex_hover;
	case Constants::ButtonState::Clicked:
		return tex_clicked;
	}
}

bool Button::IsPointInBounds(int x, int y) {
	if (rect.x < x && x < rect.x + rect.w && rect.y < y && y < rect.y + rect.h)
		return true;
	return false;
}

void Button::GenerateButtonStack(SDL_Renderer * ren, SDL_Rect & srcpos, int offset, bool horizontally, std::vector<std::string>& captions, std::vector<Button>& dst)
{
	int x = srcpos.x;
	int y = srcpos.y;

	for (auto caption : captions) {
		dst.push_back(Button(x, y, Constants::BtnWidth, Constants::BtnHeight, caption, ren));
		if (horizontally)
			x += Constants::BtnWidth + offset;
		else
			y += Constants::BtnHeight + offset;
	}
}
