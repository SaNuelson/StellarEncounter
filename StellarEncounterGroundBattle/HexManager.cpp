#include "HexManager.h"
#include "stdlibs.h"

using namespace Managers;

SDL_Rect Managers::HexManager::GetMouseHex(SDL_Event * ev)
{
	SDL_Rect pos;
	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);

	x -= 50;
	y -= 50;

	pos.y = y / 48;
	x -= 40 * pos.y;
	pos.x = x / 80;
	if (x < 0)
		pos.x--;

	return pos;
}

// debug version (hardcoded)
void HexManager::CreateField(SDL_Renderer* ren, std::string src){
	
	ClearField();

	tilemap.push_back(std::vector<SDL_Texture*>());
	int line = 0;
	for (auto c : src) {
		SDL_Texture * tex = Constants::GetTextureFromChar(c);
		if (tex == nullptr) {
			line++;
			tilemap.push_back(std::vector<SDL_Texture*>());
		}
		else
			tilemap[line].push_back(tex);
	}
}

void Managers::HexManager::ClearField()
{
	tilemap.clear();
}
