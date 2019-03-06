#include "ResourceManager.h"

SDL_Renderer * ResourceManager::ren = nullptr;
bool ResourceManager::initialized = false;
std::map<std::string, SDL_Texture*> ResourceManager::TextureMap;
TTF_Font * ResourceManager::default_font;

void ResourceManager::Init(SDL_Renderer * renderer) { 
	ren = renderer; initialized = true; 
	default_font = TTF_OpenFont("Resources/default_font.ttf", 20);
}
SDL_Texture * ResourceManager::LoadTexture(std::string path)
{

	if (TextureMap.find(path) != TextureMap.end())
		return TextureMap[path];

	SDL_Texture * tex = IMG_LoadTexture(ren, path.c_str());
	if (tex == nullptr) {
		std::cout << "IMG_LoadTexture Error on path: " << path << std::endl;
	}
	TextureMap[path] = tex;
	return tex;

}
SDL_Texture * ResourceManager::LoadTextureWithCaption(std::string path, std::string caption)
{

	if (TextureMap.find(path + "@" + caption) != TextureMap.end())
		return TextureMap[path + "@" + caption];

	// button texture
	SDL_Texture * tex = LoadTexture(path); 
	if (tex == nullptr)
		return nullptr;

	// caption texture
	SDL_Rect rect;	// get size of button - needs to be based off text, because it resizes poorly
	SDL_Color color; color.r = 0; color.g = 0; color.b = 0; color.a = 255;
	SDL_Surface * caption_surf = TTF_RenderText_Blended(default_font, caption.c_str(), color);
	SDL_Texture * caption_tex = SDL_CreateTextureFromSurface(ren, caption_surf);
	SDL_QueryTexture(caption_tex, nullptr, nullptr, &rect.w, &rect.h);

	//Default max w/h
	int maxW = 180;
	int maxH = 30;

	if (rect.w > maxW || rect.h > maxH) {
		std::cout << "LoadTextureWithCaption - caption too big." << std::endl;
		SDL_DestroyTexture(tex);
		SDL_DestroyTexture(caption_tex);
		SDL_FreeSurface(caption_surf);
		return nullptr;
	}

	// center rect
	rect.x = (200 - rect.w) / 2;
	rect.y = (50 - rect.h) / 2;

	// blit
	SDL_Texture * blit_tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 50);
	SDL_SetRenderTarget(ren, blit_tex);
	SDL_RenderCopy(ren, tex, nullptr, nullptr);
	SDL_RenderCopy(ren, caption_tex, nullptr, &rect);

	// clean up the mess and return
	SDL_SetRenderTarget(ren, nullptr);
	SDL_DestroyTexture(tex);
	SDL_DestroyTexture(caption_tex);
	SDL_FreeSurface(caption_surf);
	TextureMap[path + "@" + caption] = blit_tex;
	return blit_tex;

}

void ResourceManager::FreeTextures()
{
	for (auto tex_pair : TextureMap) {
		SDL_DestroyTexture(tex_pair.second);
	}
	TextureMap.clear();
}
;