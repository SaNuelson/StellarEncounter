#include "Tile.h"
#include "Tilemap.h"
#include "GameObject.h"
#include "Scene.h"

BoxTile::BoxTile(std::string source, SDL_Point position, SDL_Point mapposition, BoxTileMap* tilemap) {
	tex_default = ResourceManager::LoadTexture(source);
	SDL_QueryTexture(tex_default, nullptr, nullptr, &pos.w, &pos.h);
	pos.x = position.x;
	pos.y = position.y;
	mappos = mapposition;
	occ = nullptr;
	state = 1;
	this->tilemap = tilemap;
}

void BoxTile::SetNeighbors(BoxTile * left, BoxTile * up, BoxTile * right, BoxTile * down)
{
	tile_up = up;
	tile_left = left;
	tile_right = right;
	tile_down = down;
}

void BoxTile::Init()
{
	tex_move = ResourceManager::LoadTexture("Graphics/txmove.png", 150);
	tex_run = ResourceManager::LoadTexture("Graphics/txrun.png", 150);
	tex_hover = ResourceManager::LoadTexture("Graphics/txhover.png");
	tex_attack = ResourceManager::LoadTexture("Graphics/txattack.png", 150);
}

GameObject* BoxTile::GetOccupant() {
	return occ; 
}

void BoxTile::SetOccupant(GameObject* obj) {
	occ = obj;
}

void BoxTile::OnUpdate() {
	state = TILE_DEFAULT;
}

void BoxTile::AddState(TileRenderFlag flag) {
	auto newstate = state | flag;
	if ((newstate | TILE_MOVE | TILE_RUN) == newstate ||
		(newstate | TILE_MOVE | TILE_ATTACK) == newstate ||
		(newstate | TILE_RUN | TILE_ATTACK) == newstate) {
		std::cout << "BoxTile::AddState: " << flag << " unsuccessful, unallowed. Reverting..." << std::endl;
		return;
	}
	state = newstate;
}

void BoxTile::SetState(TileRenderFlag flag) {
	// TILE_DEFAULT is default
	// TILE_HOVER is non-dependent
	// TILE_MOVE is exclusive with TILE_RUN & TILE_ATTACK
	if (flag == TILE_MOVE)
		state = state & ~(TILE_RUN | TILE_ATTACK) | TILE_MOVE;
	else if (flag == TILE_RUN)
		state = state & ~(TILE_MOVE | TILE_ATTACK) | TILE_RUN;
	else if (flag == TILE_ATTACK)
		state = state & ~(TILE_MOVE | TILE_RUN) | TILE_ATTACK;
	else
		state |= flag;

}

void BoxTile::DelState(TileRenderFlag flag) {
	state &= ~flag;
}

bool BoxTile::GetState(TileRenderFlag flag)
{
	return (state == (state | flag));
}

void BoxTile::OnRender() {
	if (TileRenderFlag(state)[0])
		SDL_RenderCopy(ResourceManager::ren, tex_default, nullptr, &pos);
	if (TileRenderFlag(state)[2])
		SDL_RenderCopy(ResourceManager::ren, tex_move, nullptr, &pos);
	if (TileRenderFlag(state)[3])
		SDL_RenderCopy(ResourceManager::ren, tex_run, nullptr, &pos); // this is hover ???
	if (TileRenderFlag(state)[4])
		SDL_RenderCopy(ResourceManager::ren, tex_attack, nullptr, &pos);
	if (TileRenderFlag(state)[1])
		SDL_RenderCopy(ResourceManager::ren, tex_hover, nullptr, &pos);

	if (occ != nullptr)
		occ->OnRender();

}

SDL_Point BoxTile::GetCenter() {
	SDL_Point p;
	p.x = pos.x + pos.w / 2;
	p.y = pos.y + pos.h / 2;
	return p;
}