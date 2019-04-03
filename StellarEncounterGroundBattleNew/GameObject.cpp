#include "GameObject.h"
#include "Tiles.h"

Unit::Unit(big HP, big SP, small AP, SDL_Point tilePosition, std::string texSrc, BoxTileMap* tilemap, bool playerTeam) {

	MaxHP = HP;
	CurHP = HP;
	MaxAP = AP;
	CurAP = AP;
	currTile = tilePosition;
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

void Unit::Move(SDL_Point destTile) {
	currTile = destTile;
}

void Unit::OnRender() {
	//std::cout << "Render " << position.x << " " << position.y << " " << position.w << " " << position.h << std::endl;
	SDL_Point p = tilemap->GetCoords(currTile.x, currTile.y);
	SDL_Point s; 
	SDL_QueryTexture(textures[currentTexture], nullptr, nullptr, &s.x, &s.y);
	position.x = p.x - s.x / 2;
	position.y = p.y - s.y;
	SDL_RenderCopy(ResourceManager::ren, textures[currentTexture], nullptr, &position);
}
