#include "GameObject.h"
#include "Tiles.h"

Unit::Unit(big HP, big SP, small AP, BoxTile* tile, std::string texSrc, BoxTileMap* tilemap, bool playerTeam) {

	MaxHP = HP;
	CurHP = HP;
	MaxAP = AP;
	CurAP = AP;
	this->tile = tile;
	tile->occ = this;
	this->textures = textures;
	LoadTextures(texSrc);
	this->tilemap = tilemap;
	isPlayer = playerTeam;
}

void Unit::LoadTextures(std::string texSrc)
{
	textures.push_back(ResourceManager::LoadTexture(texSrc));
	SDL_QueryTexture(textures[0], nullptr, nullptr, &position.w, &position.h);
}

void Unit::OnUpdate(double delta) {

}

void Unit::Move(BoxTile * tile)
{
	this->CurAP -= tilemap->GetDistance(this->tile, tile);
	this->tile->SetOccupant(nullptr);
	tile->SetOccupant(this);
	// now move is instant
	this->tile = tile;
}

void Unit::OnRender() {
	//std::cout << "Render " << position.x << " " << position.y << " " << position.w << " " << position.h << std::endl;
	SDL_Point p = tile->GetCenter();
	SDL_Point s; 
	SDL_QueryTexture(textures[currentTexture], nullptr, nullptr, &s.x, &s.y);
	position.x = p.x - s.x / 2;
	position.y = p.y - s.y;
	SDL_RenderCopy(ResourceManager::ren, textures[currentTexture], nullptr, &position);
}

bool Unit::isEnemy() { return !isPlayer; }

std::string Unit::toString()
{
	auto str = "GameObject::Unit( HP: " + std::to_string(CurHP) + "/" + std::to_string(MaxHP) +
		", SP: " + std::to_string(CurSP) + "/" + std::to_string(MaxSP) +
		", AP: " + std::to_string(CurAP) + "/" + std::to_string(MaxAP) +
		(isPlayer ? "PU" : "NPU") + ")";
	return str;
}

Unit * Unit::getPtr() { return this; }

bool GameObject::isEnemy() { return false; }

std::string GameObject::toString()
{
	return "GameObject::BaseClass";
}

GameObject * GameObject::getPtr() { return this; }

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
