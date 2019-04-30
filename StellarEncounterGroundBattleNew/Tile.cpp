#include "Tile.h"
#include "Tilemap.h"
#include "GameObject.h"
#include "Scene.h"

Tile::Tile(std::string source, SDL_Point position, SDL_Point mapposition, TileMap* tilemap) {
	tex = ResourceManager::LoadTexture(source);
	SDL_QueryTexture(tex, nullptr, nullptr, &pos.w, &pos.h);
	pos.x = position.x;
	pos.y = position.y;
	mappos = mapposition;
	occ = nullptr;
	this->tilemap = tilemap;
}

void Tile::SetNeighbors(Tile * up_left, Tile * up_right, Tile * right, Tile * down_right, Tile * down_left, Tile * left)
{
	tile_up_left = up_left;
	tile_up_right = up_right;
	tile_right = right;
	tile_down_right = down_right;
	tile_down_left = down_left;
	tile_left = left;
}

GameObject* Tile::GetOccupant() {
	return occ; 
}

void Tile::SetOccupant(GameObject* obj) {
	occ = obj;
}

void Tile::OnUpdate() {
}

void Tile::OnRender() {
	
	SDL_RenderCopy(ResourceManager::ren, tex, nullptr, &pos);

	if (occ != nullptr)
		occ->OnRender();
}

SDL_Point Tile::GetCenter() {
	SDL_Point p;
	p.x = pos.x + pos.w / 2;
	p.y = pos.y + pos.h / 2;
	return p;
}