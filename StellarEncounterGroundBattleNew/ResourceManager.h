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

	// init functions are called in this succession, ensuring everything's set up.
	static int InitFramework();
	static int InitWinRen(std::string win_title, int win_x, int win_y, int win_w, int win_h, SDL_WindowFlags win_flag, SDL_RendererFlags ren_flag);
	
	// closing function, takes care of everything
	static void Quit();

	static SDL_Texture * LoadTexture(std::string path);
	static SDL_Texture * LoadTexture(std::string path, Uint8 alpha);
	static SDL_Texture * LoadTextureWithCaption(std::string path, std::string caption);
	static SDL_Texture * LoadCaption(std::string caption);

	// unused in current build
	static void RenderText(std::string caption, SDL_Rect& dst_rect);

	// for quick creation
	static SDL_Rect CreateRectangle(int x, int y, int w, int h);

	// push user defined SDL_Event into the event stack
	static void DispatchEvent(Sint32 code, void* data1, void* data2);

	static Scene* GetScene();
	static Scene* CreateScene(Sint32 scene_code);

	static SDL_Window* GetWindow();
	// static void SetWindow(SDL_Window* win);	// unnecessary

	static SDL_Renderer* GetRenderer();
	// static void SetRenderer(SDL_Renderer* ren);	// unnecessary

	static Button* CreateButton();
	
	static Unit* CreateUnit(std::string source);

	static Item* CreateItem(std::string source); // not implemented

private:
	static bool initialized;

	static SDL_Renderer* ren;
	static SDL_Window* win;
	static std::unique_ptr<Scene> scene;

	// holds unique_ptrs for all loaded textures
	static std::map<std::string, SDL_Texture*> TextureMap;

	// for simplicity only one font (with one size) is created... I mean text in SDL looks awful either way.
	static TTF_Font * default_font;

	static std::vector<std::unique_ptr<GameObject>> GameObjects;

	// buttons were intially created in StellarEncounterUI. They worked well, so I moved them here, although there's not all that much place for them here.
	static std::vector<std::unique_ptr<Button>> Buttons;

};

