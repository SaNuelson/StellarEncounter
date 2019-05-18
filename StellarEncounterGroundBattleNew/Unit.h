#pragma once
#include "stdlib.h"
#include "GameObject.h"
#include "Tilemap.h"
#include "Tile.h"
#include "ResourceManager.h"
#include "Equipment.h"

class Unit : public GameObject {
public:
	Unit();
	Unit(std::string source);
	Unit(big HP, big SP, small AP, Tile* tile, std::string texSrc, TileMap* tilemap, bool playerTeam);

	void LoadTextures(std::string texSrc);

	void OnUpdate(double delta);

	void UseAction(GameObject * defender);
	void ReceiveAction(int amount) override;

	void Move(Tile* tile);
	void Move(Direction dir);

	void ChangeHP(big amount, bool overload); // overload heals SP with excess healing
	void ChangeSP(big amount, bool overload); // overload damages HP with excess damage
	void ChangeAP(big amount);

	void Die();

	void OnRender() override;

	bool isEnemy() override;

	std::string toString() override;

	//private:

	// GameLogic
	// TileMap* tilemap = nullptr;	<- ingerited from GameObject
	bool isPlayer = false;

	// HitPoints
	big MaxHP = 100;
	big CurHP = 100;
	big MaxSP = 100;
	big CurSP = 100;

	// Movement
	small MaxAP = 5;
	small CurAP = 5;

	SDL_Rect position;
	// Tile* tile = nullptr;	<- inherited from GameObject

	// Equip
	// Equipment equip;
	Weapon weapon;
	

	// Render
	big textureSpeed = 100;
	big textureTimeLeft = textureSpeed;
	small currentTextureSet = 0;
	small currentTexture = 0;
	std::vector<SDL_Texture*> textures;
	std::map<small, std::pair<small, small>> textureSets;


	// Other
	std::string name = "";

private:

	static void ParseSource(Unit* unit, std::string& source);

};
