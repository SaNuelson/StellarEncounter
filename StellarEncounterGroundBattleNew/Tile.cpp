#include "Tile.h"
#include "Tiles.h"
#include "GameObject.h"

BoxTile::BoxTile(std::string source, SDL_Point position, BoxTileMap* tilemap) {
	tex_default = ResourceManager::LoadTexture(source);
	SDL_QueryTexture(tex_default, nullptr, nullptr, &pos.w, &pos.h);
	pos.x = position.x;
	pos.y = position.y;
	occ = nullptr;
	state = 1;
	this->tilemap = tilemap;
}

void BoxTile::Init()
{
	tex_move = ResourceManager::LoadTexture("Graphics/txmove.png", 150);
	tex_run = ResourceManager::LoadTexture("Graphics/txrun.png", 150);
	tex_hover = ResourceManager::LoadTexture("Graphics/txhover.png");
	tex_attack = nullptr;
}

GameObject* BoxTile::GetOccupant() {
	return occ; 
}

void BoxTile::SetOccupant(GameObject* obj) {
	occ = obj;
}

void BoxTile::OnUpdate() {

	// is update needed?
	if (tilemap->IsPlayerTurn()) {

		// is moveAble?
		if (tilemap->CanMoveHere(this))
			state |= TILE_MOVE;



	}

}

void BoxTile::SetState(TileRenderFlag flag) {
	// TILE_DEFAULT is default
	// TILE_HOVER is non-dependent
	// TILE_MOVE is exclusive with TILE_RUN & TILE_ATTACK
	std::cout << "Tile changed with flag " << flag << " from " << state;
	if (flag == TILE_MOVE)
		state = state & ~(TILE_RUN | TILE_ATTACK) | TILE_MOVE;
	else if (flag == TILE_RUN)
		state = state & ~(TILE_MOVE | TILE_ATTACK) | TILE_RUN;
	else if (flag == TILE_ATTACK)
		state = state & ~(TILE_MOVE | TILE_RUN) | TILE_ATTACK;
	else if (flag == TILE_DEFAULT)
		state = TILE_DEFAULT;
	else
		state |= flag;

	std::cout << " to " << state << std::endl;

}

void BoxTile::OnRender() {
	std::cout << state << std::endl;
	if (TileRenderFlag(state)[0])
		SDL_RenderCopy(ResourceManager::ren, tex_default, nullptr, &pos);
	if (TileRenderFlag(state)[1])
		SDL_RenderCopy(ResourceManager::ren, tex_hover, nullptr, &pos);
	if (TileRenderFlag(state)[2])
		SDL_RenderCopy(ResourceManager::ren, tex_move, nullptr, &pos);
	if (TileRenderFlag(state)[3])
		SDL_RenderCopy(ResourceManager::ren, tex_run, nullptr, &pos); // this is hover ???
	if (TileRenderFlag(state)[4])
		SDL_RenderCopy(ResourceManager::ren, tex_attack, nullptr, &pos);
}

SDL_Point BoxTile::GetCenter() {
	SDL_Point p;
	p.x = pos.x + pos.w / 2;
	p.y = pos.y + pos.h / 2;
	return p;
}