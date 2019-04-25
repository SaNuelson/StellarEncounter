#pragma once
#include "stdlib.h"
#include "GameObject.h"

class GameObject;
class Unit;
class Item;

class ResourceManager
{
public:

	static void Init(SDL_Renderer * renderer, SDL_Window* win);

	static SDL_Texture * LoadTexture(std::string path);

	static SDL_Texture * LoadTexture(std::string path, Uint8 alpha);

	static SDL_Texture * LoadTextureWithCaption(std::string path, std::string caption);

	static SDL_Texture * LoadCaption(std::string caption);

	static void RenderText(std::string caption, SDL_Rect& dst_rect);

	static SDL_Rect CreateRectangle(int x, int y, int w, int h); // for quick creation

	static void FreeTextures();

	static SDL_Renderer * ren;
	static SDL_Window * win;

	static Unit* CreateUnit(big HP, big SP, small AP, BoxTile* tile, std::string texSrc, BoxTileMap* tilemap, bool playerTeam);
	static Item* CreateItem(std::string texSrc, BoxTile* tile, BoxTileMap* tilemap, bool usable);

private:

	static bool initialized;


	static std::map<std::string, SDL_Texture*> TextureMap;

	static TTF_Font * default_font;

	static std::vector<std::unique_ptr<GameObject>> GameObjects;

};

