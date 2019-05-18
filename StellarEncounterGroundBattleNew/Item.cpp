#include "Item.h"

Item::Item(std::string texSrc, Tile* tile, TileMap * tilemap, bool usable)
{
	tex = ResourceManager::LoadTexture(texSrc);
	ren = ResourceManager::ren;
	this->tilemap = tilemap;
	this->tile = tile;
	tile->occ = this;
	isUsable = usable;
}

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
	// std::cout << "Item::OnRender on position: " << position.x << " " << position.y << " " << position.w << " " << position.h << std::endl;
	SDL_RenderCopy(ResourceManager::ren, tex, nullptr, &position);
}

void Item::ReceiveAction(int amount)
{
	if (amount > 0) {
		std::cout << toString() << "gets hurt, but it's just an inanimate object and because of lacking implementation feels nothing." << std::endl;
	}
	else {
		std::cout << toString() << "gets healed, but once again it's just AN INANIMATE OBJECT. The object feels nothing. Not a thing. This action was useless." << std::endl;
	}
}

std::string Item::toString()
{
	// TODO
	return "GameObject::Item";
}
