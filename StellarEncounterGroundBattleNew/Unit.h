#pragma once
#include "stdlib.h"
#include "GameObject.h"
#include "Tilemap.h"
#include "Tile.h"
#include "ResourceManager.h"
#include "Equipment.h"

// core game element, for now without AI, only receiving human input
class Unit : public GameObject {
public:

	// string is parsed and unit is generated from it, more details in ParseSource(src)
	Unit(std::string source);
	~Unit();

	// thanks to parsing, unit can be easily modified by another source
	// this is also the only possible way of setting variables from outside
	void Edit(std::string source);

	// in case of different sizing of different actions (skeleton attacking texture is wider than idle texture)
	// doesn't work correctly without additional info from outside (eg. skeleton's texture itself is on the right side of the attacking animation)
	void Resize();

	void OnUpdate(double delta);

	// attacking/defending, possible to expand to healing, buffing, stunning...
	void UseAction(GameObject * defender);
	void ReceiveAction(int amount) override;

	void Move(Tile* tile);
	void Move(Direction dir);

	void ChangeHP(big amount, bool overload); // overload heals SP with excess healing
	void ChangeSP(big amount, bool overload); // overload damages HP with excess damage
	void ChangeAP(big amount);

	void OnRender() override;

	// debug
	std::string toString() override;
	
	// getters
	small GetCurrentAction() { return currentAction; }
	small GetNextAction() { return nextAction; }
	small GetCurHP() { return CurHP; }
	small GetMaxHP() { return MaxHP; }
	small GetCurSP() { return CurSP; }
	small GetMaxSP() { return MaxSP; }
	small GetCurAP() { return CurAP; }
	small GetMaxAP() { return MaxAP; }
	SDL_Texture* GetCurrentTex() { return textures[currentTexture]; }

private:

	// GameLogic
	// TileMap* tilemap = nullptr;	<- ingerited from GameObject
	small currentAction = UNIT_ACTION_NONE;
	small nextAction = UNIT_ACTION_IDLE;

	// HitPoints
	big MaxHP = 100;
	big CurHP = 100;
	big MaxSP = 100;
	big CurSP = 100;

	// Movement
	small MaxAP = 5;
	small CurAP = 5;

	SDL_Rect position; // exact pixel position used for rendering
	SDL_Point dest_point; // exact pixel vector of movement
	float pos_move_unit_vec_x = 0;
	float pos_move_unit_vec_y = 0; // unit vector derived from dest_point vector
	float pos_x = 0;
	float pos_y = 0; // float version of position, details in Move()
	float moveSpeed = 20; // pixels per second
	big moveTimeLeft = moveSpeed;
	// Tile* tile = nullptr;	// inherited from GameObject

	// Equip
	// should be expanded to equipment. That should be able to hold armor and possible inventory in addion to current weapon
	Weapon weapon;
	

	// Render
	bool default_flip = false; // set to true if source textures are turned to the left side, needs to be written in source_str
	bool flip = false; // expects all textures point to the right side (thanks to default_flip), afterwards flip is true if (team != 0) so any enemies face left, player units face right
	big TPS = 10; // textures per second
	float textureTime = 1000 / TPS;
	float textureTimeCurrent = -1; // on every update delta gets subtracted. Once it reaches zero, texture ptr is incremented
	small currentTexture = 0; // texture ptr
	std::vector<SDL_Texture*> textures;	// textures are loaded automatically (in ParseSource) provided that they are sorted and named correctly
	std::map<small, std::pair<small, small>> textureSets; // indicates ranges where different texture sets are (eg. idle_animation from 0 to 5, attack_animation from 6 to 9, etc.)


	// Other
	std::string name = "";

private:

	static void ParseSource(Unit* unit, std::string& source);

};
