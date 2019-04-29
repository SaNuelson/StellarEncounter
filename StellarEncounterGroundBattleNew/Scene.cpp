#include "Scene.h"



Scene::Scene() : infoblock(this), tilemap(this) {

	// actionblock.scene = this

}

void Scene::StartDemo1() {

	tilemap.Init(level1boxtilemap, xTileSize, xTileSize);
	
	units.push_back(ResourceManager::CreateUnit(100, 100, 5, tilemap.GetTile(1, 3), "Graphics/Hero/idle1.png", &tilemap, true));
	units[0]->weapon = Weapon(10);
	units.push_back(ResourceManager::CreateUnit(100, 100, 5, tilemap.GetTile(6, 1), "Graphics/Enemy1/idle1.png", &tilemap, false));
	units.push_back(ResourceManager::CreateUnit(100, 100, 5, tilemap.GetTile(6, 3), "Graphics/Enemy2/idle1.png", &tilemap, false));
	units.push_back(ResourceManager::CreateUnit(100, 100, 5, tilemap.GetTile(6, 5), "Graphics/Enemy3/idle1.png", &tilemap, false));

	items.push_back(ResourceManager::CreateItem("Graphics/box.png", tilemap.GetTile(3, 2), &tilemap, false));
	items.push_back(ResourceManager::CreateItem("Graphics/box.png", tilemap.GetTile(3, 3), &tilemap, false));
	items.push_back(ResourceManager::CreateItem("Graphics/box.png", tilemap.GetTile(3, 4), &tilemap, false));

}

void Scene::ResolveInput(SDL_Event & e) {
	// infoblock.ResolveInput(e);
	// actionblock.ResolveInput(e);

	// for future AI implementation
	// if (!units[currentUnit]->isPlayer) return;

	if (e.type == SDL_KEYUP)
		return;

	switch (e.key.keysym.sym) {
	case SDLK_DOWN:
	case SDLK_s:
		// move down
		if (tilemap.CanMove(units[currentUnit], units[currentUnit]->tile->tile_down))
			units[currentUnit]->Move(Direction::Down);
		else if (tilemap.CanAttack(units[currentUnit], units[currentUnit]->tile->tile_down))
			units[currentUnit]->UseAction(units[currentUnit]->tile->tile_down->occ);
		break;
	case SDLK_RIGHT:
	case SDLK_d:
		// move right
		if (tilemap.CanMove(units[currentUnit], units[currentUnit]->tile->tile_right))
			units[currentUnit]->Move(Direction::Right);
		else if (tilemap.CanAttack(units[currentUnit], units[currentUnit]->tile->tile_right))
			units[currentUnit]->UseAction(units[currentUnit]->tile->tile_right->occ);
		break;
	case SDLK_LEFT:
	case SDLK_a:
		// move left
		if (tilemap.CanMove(units[currentUnit], units[currentUnit]->tile->tile_left))
			units[currentUnit]->Move(Direction::Left);
		else if (tilemap.CanAttack(units[currentUnit], units[currentUnit]->tile->tile_left))
			units[currentUnit]->UseAction(units[currentUnit]->tile->tile_left->occ);
		break;
	case SDLK_UP:
	case SDLK_w:
		// move up
		if (tilemap.CanMove(units[currentUnit], units[currentUnit]->tile->tile_up))
			units[currentUnit]->Move(Direction::Up);
		else if (tilemap.CanAttack(units[currentUnit], units[currentUnit]->tile->tile_up))
			units[currentUnit]->UseAction(units[currentUnit]->tile->tile_up->occ);
		break;
	// ...
	}

	tilemap.ResolveInput(e);
}

void Scene::OnUpdate(double delta) {

	if (units[currentUnit]->CurAP == 0)
		currentUnit++;

	infoblock.OnUpdate(delta);
	//actionblock.OnUpdate(delta);
	tilemap.OnUpdate(delta);
	for (auto &unit : units)
		unit->OnUpdate(delta);
}

void Scene::OnRender() {
	infoblock.OnRender();
	//actionblock.OnRender();
	tilemap.OnRender();
}

bool Scene::IsPlayerTurn() { return units[currentUnit]->isPlayer; }

Unit * Scene::GetCurrentUnit() { return (units.size() > currentUnit ? units[currentUnit] : nullptr); }
