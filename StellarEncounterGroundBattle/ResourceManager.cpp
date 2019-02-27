#include "ResourceManager.h"

SDL_Texture * ResourceManager::loadTex(const std::string &file, SDL_Renderer * ren) {
	SDL_Texture * tex = IMG_LoadTexture(ren, file.c_str());
	if (tex == nullptr) {
		std::cout << "Error" << std::endl;
	}
	return tex;
}

void ResourceManager::renderTex(SDL_Texture * tex, SDL_Renderer * ren, int x, int y, int w, int h) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, nullptr, &dst);
}

void ResourceManager::renderTex(SDL_Texture * tex, SDL_Renderer * ren, SDL_Rect dst, SDL_Rect * clip) {
	SDL_RenderCopy(ren, tex, clip, &dst);
}

void ResourceManager::renderTex(SDL_Texture* tex, SDL_Renderer* ren, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int dstW, int dstH) {
	SDL_Rect src;
	src.x = srcX;
	src.y = srcY;
	src.w = srcW;
	src.h = srcH;
	SDL_Rect dst;
	dst.x = dstX;
	dst.y = dstY;
	dst.w = dstW;
	dst.h = dstH;
	SDL_RenderCopy(ren, tex, &src, &dst);
}

void ResourceManager::renderTex(SDL_Texture * tex, SDL_Renderer * ren, int x, int y, SDL_Rect * clip) {
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