#pragma once
#include "stdlib.h"
#include "Constants.h"

class GameObject;
class Item;
class Unit;
class Tile;
class TileMap;
class Scene;
class Button;

class ResourceManager
{
public:

	static void Init(SDL_Renderer * renderer, SDL_Window* win, Scene * scene);
	
	static void Quit();

	static SDL_Texture * LoadTexture(std::string path);

	static SDL_Texture * LoadTexture(std::string path, Uint8 alpha);

	static SDL_Texture * LoadTextureWithCaption(std::string path, std::string caption);

	static SDL_Texture * LoadCaption(std::string caption);

	static void RenderText(std::string caption, SDL_Rect& dst_rect);

	static SDL_Rect CreateRectangle(int x, int y, int w, int h); // for quick creation


	static void FreeTextures();

	static SDL_Renderer * ren;
	static SDL_Window * win;
	static Scene * scene;

	static Button* CreateButton();
	static Unit* CreateUnit();
	static Item* CreateItem();
	static Unit* CreateUnit(std::string source);
	static Unit* CreateUnit(big HP, big SP, small AP, Tile* tile, std::string texSrc, TileMap* tilemap, bool playerTeam);
	static Item* CreateItem(std::string texSrc, Tile* tile, TileMap* tilemap, bool usable);

private:

	static bool initialized;


	static std::map<std::string, SDL_Texture*> TextureMap;

	static TTF_Font * default_font;

	static std::vector<std::unique_ptr<GameObject>> GameObjects;

	static std::vector<std::unique_ptr<Button>> Buttons;

};

