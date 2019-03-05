#ifndef SE_RESOURCE_MANAGER
#define SE_RESOURCE_MANAGER

#include "stdlibs.h"
#include "Constants.h"
#include "UID.h"

// creates textures based on parameters, keeps track of them, should dispose of them when no one uses them

class ResourceManager
{
public:
	static SDL_Texture * loadTex(const std::string &file, SDL_Renderer * ren);

	static void renderTex(SDL_Texture * tex, SDL_Renderer * ren, int x, int y, int w, int h);
	static void renderTex(SDL_Texture* tex, SDL_Renderer* ren, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int dstW, int dstH);
	static void renderTex(SDL_Texture * tex, SDL_Renderer * ren, SDL_Rect dst, SDL_Rect * clip = nullptr);
	static void renderTex(SDL_Texture * tex, SDL_Renderer * ren, int x, int y, SDL_Rect * clip = nullptr);

	static bool GenerateTextures(SDL_Renderer* ren);

	static SDL_Texture * GetTexture(UID ID);
	static SDL_Texture * GetCharacterTex(UID ID);
	static TTF_Font * GetFont(UID ID);

	static SDL_Texture * CreateButton(SDL_Renderer* ren, SDL_Rect &rect, std::string caption, std::string type);

	static SDL_Rect CreateRect(int x, int y, int w, int h);
	static SDL_Rect CreatePointRect(int x, int y);
	static SDL_Rect CreateRect(int w, int h);

	static SDL_Color CreateColor(int r, int g, int b, int a);

private:
	static std::map<UID, SDL_Texture*> TileTexMap;
	static std::map<UID, SDL_Texture*> CharacterTexMap;
	static std::map<UID, TTF_Font*> FontMap;
};

#endif