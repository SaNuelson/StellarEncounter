#include "Item.h"

Item::Item(std::string texSrc, BoxTile* tile, BoxTileMap * tilemap, bool usable)
{
	tex = ResourceManager::LoadTexture(texSrc);
	ren = ResourceManager::ren;
	this->tilemap = tilemap;
	this->tile = tile;
	isUsable = usable;
}

bool Item::isEnemy() { return false; }

void Item::OnRender()
{
	// TODO Update only if changed
	SDL_Point p = tile->GetCenter();
	SDL_Point s;
	SDL_QueryTexture(tex, nullptr, nullptr, &s.x, &s.y);
	position.x = p.x - s.x / 2;
	position.y = p.y - s.y;
	position.w = s.x;
	position.h = s.y;
	std::cout << position.x << " " << position.y << " " << position.w << " " << position.h << std::endl;
	SDL_RenderCopy(ResourceManager::ren, tex, nullptr, &position);
}

std::string Item::toString()
{
	// TODO
	return "GameObject::Item";
}

Item * Item::getPtr() { return this; }
