#include "GroundBattleScene.h"

GroundBattleScene::GroundBattleScene() : tilemap(this), stackblock(this) {

	StartDemo1();

}

void GroundBattleScene::StartDemo1() {

	tilemap.Init(level1tilemap, xTileSize, xTileSize);

	units.push_back(ResourceManager::CreateUnit(hero_source));
	tilemap.PutOnTile(units[0], 1, 3);
	units[0]->Team = 0;
	units.push_back(ResourceManager::CreateUnit(skeleton_source));
	tilemap.PutOnTile(units[1], 5, 3);
	units[1]->Team = 1;
	units.push_back(ResourceManager::CreateUnit(wizard_source));
	tilemap.PutOnTile(units[2], 4, 4);
	units[2]->Team = 1;
	stackblock.Populate(); 
}

void GroundBattleScene::ResolveInput(SDL_Event & e) {

	if (e.type == SDL_USEREVENT) {
		if (e.user.code == RC_UNIT_STAT_CHANGE) {
			stackblock.ResolveInput(e);
		}
		else if (e.user.code == RC_UNIT_DEATH) {
			CheckEndGame();
		}
	}
	else if (e.type == SDL_KEYUP) {
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
	else if (e.type == SDL_KEYDOWN) {
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
			if (units[currentUnit]->GetCurrentAction() == UNIT_ACTION_IDLE) { // movement possible only if active unit is idle
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
			}
			break;

		case SDLK_RIGHT:
		case SDLK_d:
			if (units[currentUnit]->GetCurrentAction() == UNIT_ACTION_IDLE) { // movement possible only if active unit is idle
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
			}
			break;
		}
	}
	
	tilemap.ResolveInput(e);
}

void GroundBattleScene::OnUpdate(double delta) {

	// End Turn, move units
	while (units[currentUnit]->GetCurrentAction() == UNIT_ACTION_DEAD) {
		EndTurn();
	}
	if (units[currentUnit]->GetCurAP() <= 0) {
		units[currentUnit]->ChangeAP(units[currentUnit]->GetCurAP());
		EndTurn();
	}

	tilemap.OnUpdate(delta);
	for (auto &unit : units)
		unit->OnUpdate(delta);
}

void GroundBattleScene::EndTurn()
{
	currentUnit++;
	if (currentUnit >= units.size())
		currentUnit = 0;
}


void GroundBattleScene::OnRender() {
	tilemap.OnRender();
	stackblock.OnRender();
}

bool GroundBattleScene::CheckEndGame()
{
	// std::cout << "Checking endgame... " << std::endl;
	bool player_alive = false;
	bool enemy_alive = false;
	for (int i = 0; i < units.size(); i++) {
		if (player_alive && enemy_alive)
			return false;
		else if (units[i]->GetNextAction() != UNIT_ACTION_DEAD &&  units[i]->Team == 0){
			player_alive = true;
			// std::cout << "Friendly unit " << units[i]->toString() << "alive. " << std::endl;
		}
		else if (units[i]->GetNextAction() != UNIT_ACTION_DEAD && units[i]->Team != 0) {
			enemy_alive = true;
			// std::cout << "Enemy unit " << units[i]->toString() << "alive." << std::endl;
		}
	}
	if (player_alive && enemy_alive)
		return false;
	if (player_alive)
		ResourceManager::DispatchEvent(RC_TEAM_0_WIN, nullptr, nullptr);
	else if (enemy_alive)
		ResourceManager::DispatchEvent(RC_TEAM_1_WIN, nullptr, nullptr);
	else {
		ResourceManager::DispatchEvent(RC_BACK, nullptr, nullptr);
		std::cout << "Somehow nobody won. Hm, smells like last season of GoT..." << std::endl;
	}
	return true;
}

void GroundBattleScene::AddUnit(Unit* unit)
{
	units.push_back(unit);
	ResourceManager::DispatchEvent(RC_UNIT_STAT_CHANGE, unit, nullptr);
}

Unit * GroundBattleScene::GetCurrentUnit() { return (units.size() > currentUnit ? units[currentUnit] : nullptr); }
