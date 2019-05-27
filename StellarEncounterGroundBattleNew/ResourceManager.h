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

	static int InitFramework();
	static int InitWinRen(std::string win_title, int win_x, int win_y, int win_w, int win_h, SDL_WindowFlags win_flag, SDL_RendererFlags ren_flag);
	static int Init(SDL_Renderer * renderer, SDL_Window* win);
	
	static void Quit();

	static SDL_Texture * LoadTexture(std::string path);

	static SDL_Texture * LoadTexture(std::string path, Uint8 alpha);

	static SDL_Texture * LoadTextureWithCaption(std::string path, std::string caption);

	static SDL_Texture * LoadCaption(std::string caption);

	static void RenderText(std::string caption, SDL_Rect& dst_rect);

	static SDL_Rect CreateRectangle(int x, int y, int w, int h); // for quick creation

	static void DispatchEvent(Sint32 code, void* data1, void* data2);

	static void FreeTextures();

	static Scene* GetScene();
	static Scene* CreateScene(Sint32 scene_code);

	static SDL_Window* GetWindow();
	// static void SetWindow(SDL_Window* win);

	static SDL_Renderer* GetRenderer();
	// static void SetRenderer(SDL_Renderer* ren);

	static Button* CreateButton();
	
	static Unit* CreateUnit();
	static Unit* CreateUnit(std::string source);

	static Item* CreateItem();
	static Item* CreateItem(std::string texSrc, Tile* tile, TileMap* tilemap, bool usable);

private:
	static SDL_Renderer* ren;
	static SDL_Window* win;
	static std::unique_ptr<Scene> scene;

	static bool initialized;


	static std::map<std::string, SDL_Texture*> TextureMap;

	static TTF_Font * default_font;

	static std::vector<std::unique_ptr<GameObject>> GameObjects;

	static std::vector<std::unique_ptr<Button>> Buttons;

};

