#pragma once
#include "stdlib.h"
#include "ResourceManager.h"

#include "Scene.h"
#include "GroundBattleScene.h"
#include "MainMenuScene.h"

#include "Unit.h"
#include "Item.h"

void ReadConsole() {
	
	// here should be focus set on console, but that requires way too many additional heads along with libs...
	
	// load line from console into vector of args
	std::string input;
	std::getline(std::cin, input);
	std::vector<std::string> args;
	std::stringstream ss(input);
	std::string data;
	while (std::getline(ss, data,' ')) { // can't put additional spaces in source string, quote implementation would be necessary otherwise
		args.push_back(data);
	}

	// show help
	// "help"
	if (args[0] == "help" || args[0] == "h") {
		std::cout << "  CONSOLE COMMAND (FOR DEBUG) HELP" << std::endl;
		std::cout << "    ----    ----    ----    ----" << std::endl;
		std::cout << "make/create item/unit <tx> <ty> <src_string>" << std::endl;
		std::cout << "remove/delete item/unit <tx> <ty>" << std::endl;
		std::cout << "move item/unit <from_tx> <from_ty> <to_tx> <to_ty>" << std::endl;
		std::cout << "edit item/unit <tx> <ty> <src_string>" << std::endl;
		std::cout << "EXAMPLE: " << std::endl;
		std::cout << "make unit 3 3 HP=10,SP=5,Name=Big Little Joe";
		std::cout << "    ----    ----    ----    ----" << std::endl;
	}

	// bind groundbattlescene for easier access
	if (dynamic_cast<GroundBattleScene*>(ResourceManager::GetScene()) == nullptr)
	{
		std::cout << "Current scene hasn't console commands implemented yet." << std::endl;
		return;
	}

	GroundBattleScene* scene = (GroundBattleScene*)ResourceManager::GetScene();

	// pre-check tx,ty tile position (mandatory in all following commands)
	int tx; int ty;
	try
	{
		tx = std::stoi(args[2]);
		ty = std::stoi(args[3]);
		if (scene->GetTilemap()->GetTile(tx, ty) == nullptr) {
			std::cout << "Tile position out of bounds." << std::endl;
			return;
		}
	}
	catch (const std::exception&)
	{
		std::cout << "Invalid tile position, couldn't parse." << std::endl;
	}

	// new item/unit
	// "make/create item/unit <tx> <ty> <src_string>"
	if (args[0] == "create" || args[0] == "make") {
		if (args[1] == "item") {
			// TODO
		}
		else if (args[1] == "unit") {
			auto unit = ResourceManager::CreateUnit(args[4]);
			scene->GetTilemap()->PutOnTile(unit, tx, ty);
			scene->AddUnit(unit);
		}
		else {
			std::cout << "Invalid arguments for create at 1: " << args[1] << std::endl;
		}
	}
	// delete item/unit
	// "delete item/unit <tx> <ty>"
	else if (args[0] == "remove" || args[0] == "delete") {
		if (args[1] == "item") {
			// TODO
		}
		else if (args[1] == "unit") {
			auto occ = scene->GetTilemap()->GetTile(tx, ty)->occ;
			if (occ != nullptr) {
				occ->~GameObject();
			}
		}
		else {
			std::cout << "Invalid arguments for remove at 1: " << args[1] << std::endl;
		}
	}
	// move item/unit
	// "move item/unit <from_tx> <from_ty> <to_tx> <to_ty>"
	else if (args[0] == "move") {
		int ttx, tty;
		try
		{
			ttx = std::stoi(args[2]);
			tty = std::stoi(args[3]);
			if (scene->GetTilemap()->GetTile(ttx, tty) == nullptr) {
				std::cout << "Destination tile position out of bounds." << std::endl;
				return;
			}
		}
		catch (const std::exception&)
		{
			std::cout << "Invalid destination tile position, couldn't parse." << std::endl;
		}
		if (args[1] == "item") {
			// TODO
		}
		else if (args[1] == "unit") {
			auto occ = scene->GetTilemap()->GetTile(tx, ty)->occ;
			if (occ != nullptr && scene->GetTilemap()->GetTile(ttx,tty) == nullptr) {
				scene->GetTilemap()->PutOnTile(occ, ttx, tty);
			}
		}
		else {
			std::cout << "Invalid arguments for move at 1: " << args[1] << std::endl;
		}
	}
	// edit item/unit
	// "edit item/unit <tx> <ty> <src_string>"
	else if (args[0] == "edit") {
		if (args[1] == "item") {
			// TODO
		}
		else if (args[1] == "unit") {
			auto occ = scene->GetTilemap()->GetTile(tx, ty)->occ;
			if (occ != nullptr) {
				if (dynamic_cast<Unit*>(occ) != nullptr) {
					((Unit*)occ)->Edit(args[4]);
				}
			}
		}
		else {
			std::cout << "Invalid arguments for edit at 1: " << args[1] << std::endl;
		}
	}
	else {
		std::cout << "Invalid argument at 0: " << args[0] << std::endl;
	}
}

