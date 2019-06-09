#include "ResourceManager.h"
#include "GameObject.h"
#include "Unit.h"
#include "Item.h"
#include "Tile.h"
#include "Tilemap.h"
#include "Button.h"

#include "Scene.h"
#include "MainMenuScene.h"
#include "OptionScene.h"
#include "GroundBattleScene.h"


SDL_Renderer * ResourceManager::ren = nullptr;
SDL_Window * ResourceManager::win = nullptr;
std::unique_ptr<Scene> ResourceManager::scene = nullptr;
bool ResourceManager::initialized = false;
std::map<std::string, SDL_Texture*> ResourceManager::TextureMap;
TTF_Font * ResourceManager::default_font;
std::vector<std::unique_ptr<GameObject>> ResourceManager::GameObjects;
std::vector<std::unique_ptr<Button>> ResourceManager::Buttons;

int ResourceManager::InitFramework()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if (((IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cout << "IMG_Init Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 2;
	}

	if (TTF_Init() != 0) {
		std::cout << "TTF_Init Error: " << SDL_GetError() << std::endl;
		IMG_Quit();
		SDL_Quit();
		return 3;
	}

	return 0;
}

int ResourceManager::InitWinRen(std::string win_title, int win_x, int win_y, int win_w, int win_h, SDL_WindowFlags win_flag, SDL_RendererFlags ren_flag)
{
	win = SDL_CreateWindow(win_title.c_str(), win_x, win_y, win_w, win_h, win_flag);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		SDL_DestroyWindow(win);
		return -2;
	}

	ren = SDL_CreateRenderer(win, -1, ren_flag);
	if (ren == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		return -1;
	}

	initialized = true;
	default_font = TTF_OpenFont("Resources/default_font.ttf", 20); // TODO temporary

	return 0;
}

void ResourceManager::Quit()
{
	for (auto& pair : TextureMap) {
		SDL_DestroyTexture(pair.second);
	}
	TextureMap.clear();

	GameObjects.clear();
	Buttons.clear();
	TTF_CloseFont(default_font);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

// any already existing textures aren't loaded repeatedly, just pulled from vector
// The current format of key in textureMap is <image_path>@<caption>#<alpha>
// that can cause some issues with malicious captions, but so far works alright and can be easily changed in the future.
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
SDL_Texture * ResourceManager::LoadTexture(std::string srcpath, Uint8 alpha)
{
	std::string path = srcpath + "#" + std::to_string(alpha);

	if (TextureMap.find(path) != TextureMap.end())
		return TextureMap[path];

	SDL_Texture * tex = IMG_LoadTexture(ren, srcpath.c_str());
	if (tex == nullptr) {
		std::cout << "IMG_LoadTexture Error on path: " << path << SDL_GetError() << std::endl;
	}
	auto ret = SDL_SetTextureAlphaMod(tex, alpha);
	if (ret != 0) {
		std::cout << "IMG_LoadTexture Error on alpha: " << SDL_GetError() << std::endl;
	}
	TextureMap[path] = tex;
	return tex;
}

SDL_Texture * ResourceManager::LoadCaption(std::string caption) 
{
	if (TextureMap.find("@" + caption) != TextureMap.end())
		return TextureMap["@" + caption];

	SDL_Color color; color.r = 0; color.g = 0; color.b = 0; color.a = 255;
	SDL_Surface * caption_surf = TTF_RenderText_Blended(default_font, caption.c_str(), color);
	SDL_Texture * caption_tex = SDL_CreateTextureFromSurface(ren, caption_surf);

	TextureMap["@" + caption] = caption_tex;
	return caption_tex;

}

SDL_Texture * ResourceManager::LoadTextureWithCaption(std::string path, std::string caption)
{

	if (TextureMap.find(path + "@" + caption) != TextureMap.end())
		return TextureMap[path + "@" + caption];

	// button texture
	SDL_Texture * tex = LoadTexture(path);
	if (tex == nullptr) {
		std::cout << "ResourceManager::LoadTextureWithCaption(" << path << ", " << caption << ") -> LoadTexture error" << SDL_GetError() << std::endl;
		return nullptr;
	}

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

void ResourceManager::RenderText(std::string caption, SDL_Rect & dst_rect)
{

	// TODO: Flags -> text_fit, text_stretch, text_align...

	SDL_Texture* tex = LoadCaption(caption);
	SDL_Rect min_rect;
	SDL_QueryTexture(tex, nullptr, nullptr, &min_rect.w, &min_rect.h);
	if (min_rect.h > dst_rect.h || min_rect.w > dst_rect.w) { // text is squished into the dst_rect
		std::cout << "ResourceManager::RenderText Warning, dst_rect is smaller than text_rect, text might be distrorted.\n" <<
			"    text_rect [w,h] = [" << min_rect.w << ", " << min_rect.h << "], dst_rect= [" << dst_rect.w << ", " << dst_rect.h << "]\n";
		SDL_RenderCopy(ren, tex, nullptr, &dst_rect);
	}
	else { // center the text into larger area
		SDL_Rect center_rect;
		min_rect.y = dst_rect.y + (dst_rect.h - min_rect.h) / 2;
		min_rect.x = dst_rect.x + (dst_rect.w - min_rect.w) / 2;
		SDL_RenderCopy(ren, tex, nullptr, &min_rect);
	}
}

SDL_Rect ResourceManager::CreateRectangle(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}

void ResourceManager::DispatchEvent(Sint32 code, void* data1, void* data2)
{
	SDL_Event e;
	e.type = SDL_USEREVENT;
	e.user.code = code;
	e.user.data1 = data1;
	e.user.data2 = data2;
	std::cout << "Dispatching event with code " << code << ".\n";
	SDL_PushEvent(&e);
}

Button* ResourceManager::CreateButton()
{
	Buttons.push_back(std::make_unique<Button>(Button::Default()));
	return Buttons[Buttons.size() - 1].get();
}

Scene* ResourceManager::GetScene()
{
	return scene.get();
}

Scene* ResourceManager::CreateScene(Sint32 scene_code)
{
	scene.reset();
	switch (scene_code) {
	case RC_NEW_GAME:
		scene = std::make_unique<GroundBattleScene>();
		break;
	case RC_OPTIONS:
		scene = std::make_unique<OptionScene>();
		break;
	case RC_MAIN_MENU:
		scene = std::make_unique<MainMenuScene>();
		break;
	}
	if (scene == nullptr) {
		std::cout << "Error at creating new scene of type " << scene_code << std::endl;
	}
	return scene.get();
}

SDL_Window* ResourceManager::GetWindow()
{
	return win;
}

SDL_Renderer* ResourceManager::GetRenderer()
{
	return ren;
}

Unit* ResourceManager::CreateUnit(std::string source)
{
	GameObjects.push_back(std::make_unique<Unit>(source));
	return (Unit*)GameObjects[GameObjects.size() - 1].get();
}
Item * ResourceManager::CreateItem(std::string source)
{
	std::cout << "Use of not implemented ResourceManager::CreateItem(std::string source)" << std::endl;
	return nullptr;
}
