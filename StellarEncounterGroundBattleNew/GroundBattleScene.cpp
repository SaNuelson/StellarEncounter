#include "GroundBattleScene.h"

GroundBattleScene::GroundBattleScene() : tilemap(this), actionblock(this), stackblock(this) {

	StartDemo1();

}

void GroundBattleScene::StartDemo1() {

	tilemap.Init(level1tilemap, xTileSize, xTileSize);

	units.push_back(ResourceManager::CreateUnit(hero_source));
	tilemap.PutOnTile(units[0], 1, 3);
	units[0]->isPlayer = true;
	units.push_back(ResourceManager::CreateUnit(hero_source));
	tilemap.PutOnTile(units[1], 5, 3);
	units[1]->isPlayer = false;
	/*
	//units.push_back(ResourceManager::CreateUnit(15, 5, 5, tilemap.GetTile(1, 3), "Graphics/GameObjects/Hero/idle1.png", &tilemap, true));
	//units[0]->name = "Sir Longderston";
	units.push_back(ResourceManager::CreateUnit(8, 10, 8, tilemap.GetTile(6, 1), "Graphics/GameObjects/Enemy1/idle1.png", &tilemap, false));
	units[1]->name = "Blair Wraith";
	units.push_back(ResourceManager::CreateUnit(12, 0, 4, tilemap.GetTile(6, 3), "Graphics/GameObjects/Enemy2/idle1.png", &tilemap, false));
	units[2]->name = "Crooked Brood";
	units.push_back(ResourceManager::CreateUnit(10, 8, 6, tilemap.GetTile(6, 5), "Graphics/GameObjects/Enemy3/idle1.png", &tilemap, false));
	units[3]->name = "Voidslave";

	items.push_back(ResourceManager::CreateItem("Graphics/GameObjects/box.png", tilemap.GetTile(3, 2), &tilemap, false));
	items.push_back(ResourceManager::CreateItem("Graphics/GameObjects/box.png", tilemap.GetTile(3, 3), &tilemap, false));
	items.push_back(ResourceManager::CreateItem("Graphics/GameObjects/box.png", tilemap.GetTile(3, 4), &tilemap, false));
	*/
}

void GroundBattleScene::ResolveInput(SDL_Event & e) {

	if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w:
			UpKey = false;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			DownKey = false;
			break;
		}
	}
	else if (units[currentUnit]->currentAction == 0 && e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w:
			UpKey = true;
			DownKey = false;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			UpKey = false;
			DownKey = true;
			break;
		case SDLK_LEFT:
		case SDLK_a:
			if (UpKey) {
				// move up_left
				if (tilemap.CanMove(units[currentUnit]->tile->tile_up_left))
					units[currentUnit]->Move(Direction::UpLeft);
				else if (tilemap.CanAttack(units[currentUnit], units[currentUnit]->tile->tile_up_left))
					units[currentUnit]->UseAction(units[currentUnit]->tile->tile_up_left->occ);
			}
			else if (DownKey) {
				// move down_left
				if (tilemap.CanMove(units[currentUnit]->tile->tile_down_left))
					units[currentUnit]->Move(Direction::DownLeft);
				else if (tilemap.CanAttack(units[currentUnit], units[currentUnit]->tile->tile_down_left))
					units[currentUnit]->UseAction(units[currentUnit]->tile->tile_down_left->occ);
			}
			else {
				// move left
				if (tilemap.CanMove(units[currentUnit]->tile->tile_left))
					units[currentUnit]->Move(Direction::Left);
				else if (tilemap.CanAttack(units[currentUnit], units[currentUnit]->tile->tile_left))
					units[currentUnit]->UseAction(units[currentUnit]->tile->tile_left->occ);
			}
			break;

		case SDLK_RIGHT:
		case SDLK_d:
			if (UpKey) {
				// move up_right
				if (tilemap.CanMove(units[currentUnit]->tile->tile_up_right))
					units[currentUnit]->Move(Direction::UpRight);
				else if (tilemap.CanAttack(units[currentUnit], units[currentUnit]->tile->tile_up_right))
					units[currentUnit]->UseAction(units[currentUnit]->tile->tile_up_right->occ);
			}
			else if (DownKey) {
				// move down_right
				if (tilemap.CanMove(units[currentUnit]->tile->tile_down_right))
					units[currentUnit]->Move(Direction::DownRight);
				else if (tilemap.CanAttack(units[currentUnit], units[currentUnit]->tile->tile_down_right))
					units[currentUnit]->UseAction(units[currentUnit]->tile->tile_down_right->occ);
			}
			else {
				// move right
				if (tilemap.CanMove(units[currentUnit]->tile->tile_right))
					units[currentUnit]->Move(Direction::Right);
				else if (tilemap.CanAttack(units[currentUnit], units[currentUnit]->tile->tile_right))
					units[currentUnit]->UseAction(units[currentUnit]->tile->tile_right->occ);
			}
			break;
		}
	}
	

	tilemap.ResolveInput(e);
}

void GroundBattleScene::OnUpdate(double delta) {

	if (units[currentUnit]->CurAP <= 0) {
		units[currentUnit]->ChangeAP(units[currentUnit]->MaxAP);
		currentUnit++;
	}
	if (currentUnit >= units.size())
		currentUnit = 0;

	//actionblock.OnUpdate(delta);
	tilemap.OnUpdate(delta);
	for (auto &unit : units)
		unit->OnUpdate(delta);
}

void GroundBattleScene::OnRender() {
	tilemap.OnRender();
	stackblock.OnRender();
	//actionblock.OnRender();


	/*
	if(units[currentUnit]->tile->tile_up_left != nullptr)
		SDL_RenderCopy(ResourceManager::ren, ResourceManager::LoadTexture("Graphics/Tiles/trees.png"), nullptr, &units[currentUnit]->tile->tile_up_left->pos);
	if (units[currentUnit]->tile->tile_up_right != nullptr)
		SDL_RenderCopy(ResourceManager::ren, ResourceManager::LoadTexture("Graphics/Tiles/trees.png"), nullptr, &units[currentUnit]->tile->tile_up_right->pos);
	if (units[currentUnit]->tile->tile_right != nullptr)
		SDL_RenderCopy(ResourceManager::ren, ResourceManager::LoadTexture("Graphics/Tiles/trees.png"), nullptr, &units[currentUnit]->tile->tile_right->pos);
	if (units[currentUnit]->tile->tile_down_left != nullptr)
		SDL_RenderCopy(ResourceManager::ren, ResourceManager::LoadTexture("Graphics/Tiles/trees.png"), nullptr, &units[currentUnit]->tile->tile_down_left->pos);
	if (units[currentUnit]->tile->tile_down_right != nullptr)
		SDL_RenderCopy(ResourceManager::ren, ResourceManager::LoadTexture("Graphics/Tiles/trees.png"), nullptr, &units[currentUnit]->tile->tile_down_right->pos);
	if (units[currentUnit]->tile->tile_left != nullptr)
		SDL_RenderCopy(ResourceManager::ren, ResourceManager::LoadTexture("Graphics/Tiles/trees.png"), nullptr, &units[currentUnit]->tile->tile_left->pos);
	*/

}

bool GroundBattleScene::IsPlayerTurn() { return units[currentUnit]->isPlayer; }

Unit * GroundBattleScene::GetCurrentUnit() { return (units.size() > currentUnit ? units[currentUnit] : nullptr); }
