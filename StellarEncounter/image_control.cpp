#include "image_control.h"


SDL_Texture * image_control::loadTex(const std::string &file, SDL_Renderer * ren) {
	SDL_Texture * tex = IMG_LoadTexture(ren, file.c_str());
	if (tex == nullptr) {
		utils::logSDLError(std::cout, "LoadTexture");
	}
	return tex;
}

void image_control::renderTex(SDL_Texture * tex, SDL_Renderer * ren, int x, int y, int w, int h) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, nullptr, &dst);
}

void image_control::renderTex(SDL_Texture * tex, SDL_Renderer * ren, SDL_Rect dst, SDL_Rect * clip) {
	SDL_RenderCopy(ren, tex, clip, &dst);
}

void image_control::renderTex(SDL_Texture * tex, SDL_Renderer * ren, int x, int y, SDL_Rect * clip) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
	}
	renderTex(tex, ren, dst, clip);
}

SDL_Texture * image_control::renderText(const std::string &msg, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer * ren) {
	TTF_Font * font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr) {
		utils::logSDLError(std::cout, "TTF_OpenFont");
		return nullptr;
	}
	SDL_Surface * surf = TTF_RenderText_Blended(font, msg.c_str(), color);
	if (surf == nullptr) {
		utils::logSDLError(std::cout, "TTF_RenderTextBlended");
		return nullptr;
	}
	SDL_Texture * tex = SDL_CreateTextureFromSurface(ren, surf);
	if (tex == nullptr) {
		utils::logSDLError(std::cout, "SDL_CreateTextureFromSurface");
		return nullptr;
	}
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return tex;
}