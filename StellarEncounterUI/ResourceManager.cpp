#include "ResourceManager.h"

SDL_Renderer * ResourceManager::ren = nullptr;
bool ResourceManager::initialized = false;
std::map<std::string, SDL_Texture*> ResourceManager::TextureMap;

void ResourceManager::Init(SDL_Renderer * renderer) { 
	ren = renderer; initialized = true; 
}
SDL_Texture * ResourceManager::LoadTexture(std::string path)
{
	/*
	if (!initialized) {
		// log uninitialized ResourceManager error
		return nullptr;
	}

	if (TextureMap.find(path) != TextureMap.end()) {
		// texture already in map, return pointer
		return TextureMap[path];
	}

	// texture not in map, create and add
	SDL_Surface * surf = IMG_Load(path.c_str());
	if (surf == nullptr)
		std::cout << "Unable to load " << path << std::endl;
	SDL_Texture * tex = SDL_CreateTextureFromSurface(ren, surf);
	SDL_FreeSurface(surf);

	TextureMap[path] = tex;

	return tex;
	*/

	SDL_Texture * tex = IMG_LoadTexture(ren, path.c_str());
	if (tex == nullptr) {
		std::cout << "IMG_LoadTexture Error on path: " << path << std::endl;
	}
	return tex;

}
void ResourceManager::FreeTextures()
{
	for (auto tex_pair : TextureMap) {
		SDL_DestroyTexture(tex_pair.second);
	}
	TextureMap.clear();
}
;