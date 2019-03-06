#ifndef SE_RESOURCE_MANAGER
#define SE_RESOURCE_MANAGER

#include "stdlibs.h"
#include "Constants.h"
#include "UID.h"

// creates textures based on parameters, keeps track of them, should dispose of them when no one uses them

class ResourceManager
{
public:

	static void OnInit(SDL_Renderer*);

	static SDL_Texture * loadTex(const std::string &file);
	static TTF_Font * loadFont(const std::string &file, int size);

	static void renderTex(SDL_Texture * tex, int x, int y, int w, int h);
	static void renderTex(SDL_Texture* tex, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int dstW, int dstH);
	static void renderTex(SDL_Texture * tex, SDL_Rect dst, SDL_Rect * clip = nullptr);
	static void renderTex(SDL_Texture * tex, int x, int y, SDL_Rect * clip = nullptr);

	static SDL_Texture * CreateButton(SDL_Rect &rect, std::string caption, std::string type); // will move partially to button as in SEUI

	static SDL_Rect CreateRect(int x, int y, int w, int h);
	static SDL_Rect CreatePointRect(int x, int y);
	static SDL_Rect CreateRect(int w, int h);

	static SDL_Color CreateColor(int r, int g, int b, int a);

	static void OnCleanup();

private:
	static std::map<std::string, SDL_Texture*> TexMap;
	static std::map<std::string, TTF_Font*> FontMap;
	static SDL_Renderer * ren;
	static bool isInitialized;

};

#endif