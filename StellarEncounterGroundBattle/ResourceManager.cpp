#include "ResourceManager.h"

std::map<std::string, SDL_Texture*> ResourceManager::TexMap;
std::map<std::string, TTF_Font*> ResourceManager::FontMap;
SDL_Renderer* ResourceManager::ren = nullptr;
bool ResourceManager::isInitialized = false;

void ResourceManager::OnInit(SDL_Renderer* renderer) {
	ren = renderer;
	isInitialized = true;
}

SDL_Texture * ResourceManager::loadTex(const std::string &file) {
	if (TexMap.find(file) != TexMap.end())
		return TexMap[file];
	SDL_Texture * tex = IMG_LoadTexture(ren, file.c_str());
	if (tex == nullptr) {
		std::cout << "Error" << std::endl;
	}
	TexMap[file] = tex;
	return tex;
}

TTF_Font * ResourceManager::loadFont(const std::string &file, int size) {
	if (FontMap.find(file + "@" + std::to_string(size)) != FontMap.end())
		return FontMap[file + "@" + std::to_string(size)];
	TTF_Font * font = TTF_OpenFont(file.c_str(), size);
	if (font == nullptr) {
		std::cout << "loadFont error at path: " << file << std::endl;
		return nullptr;
	}
	FontMap[file + "@" + std::to_string(size)] = font;
	return font;
}

void ResourceManager::renderTex(SDL_Texture * tex, int x, int y, int w, int h) {
	SDL_Rect dst = CreateRect(x, y, w, h);
	SDL_RenderCopy(ren, tex, nullptr, &dst);
}

void ResourceManager::renderTex(SDL_Texture * tex, SDL_Rect dst, SDL_Rect * clip) {
	SDL_RenderCopy(ren, tex, clip, &dst);
}

void ResourceManager::renderTex(SDL_Texture* tex, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int dstW, int dstH) {
	SDL_Rect src = CreateRect(srcX, srcY, srcW, srcH);
	SDL_Rect dst = CreateRect(dstX, dstY, dstW, dstH);
	SDL_RenderCopy(ren, tex, &src, &dst);
}

void ResourceManager::renderTex(SDL_Texture * tex, int x, int y, SDL_Rect * clip) {
	SDL_Rect dst = CreatePointRect(x, y);
	if (clip != nullptr) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
	}
	renderTex(tex, dst, clip);
}

SDL_Texture * ResourceManager::CreateButton(SDL_Rect &rect, std::string caption, std::string type)
{

	TTF_Font * font = TTF_OpenFont("Resources/Raleway-Bold.ttf", 25);

	int txt_w;
	int txt_h;
	
	SDL_Color fg = CreateColor(0, 0, 0, 255);

	SDL_Texture * btn_tex = ResourceManager::loadTex("Graphics/button" + type + ".png");

	SDL_Surface * text_surf = TTF_RenderText_Solid(font, caption.c_str(), fg);
	SDL_Texture * text_tex = SDL_CreateTextureFromSurface(ren, text_surf);
	SDL_QueryTexture(text_tex, nullptr, nullptr, &txt_w, &txt_h);

	SDL_Rect btn_rect = CreateRect(0, 0, rect.w, rect.h);
	SDL_Rect txt_rect = CreateRect(rect.w / 2 - txt_w / 2, rect.h / 2 - txt_h / 2, txt_w, txt_h);

	SDL_Texture * btn = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
	SDL_SetRenderTarget(ren, btn);
	SDL_RenderCopy(ren, btn_tex, nullptr, &btn_rect);
	SDL_RenderCopy(ren, text_tex, &btn_rect, &txt_rect);
	
	SDL_SetRenderTarget(ren, nullptr);

	return btn;
	
}

SDL_Rect ResourceManager::CreateRect(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}

SDL_Rect ResourceManager::CreatePointRect(int x, int y)
{
	return CreateRect(x, y, 0, 0);
}

SDL_Rect ResourceManager::CreateRect(int w, int h)
{
	return CreateRect(0, 0, w, h);
}

SDL_Color ResourceManager::CreateColor(int r, int g, int b, int a)
{
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}

void ResourceManager::OnCleanup() {
	
	for (auto tex_pair : TexMap) {
		SDL_DestroyTexture(tex_pair.second);
	}

	for (auto font_pair : FontMap) {
		TTF_CloseFont(font_pair.second);
	}

}