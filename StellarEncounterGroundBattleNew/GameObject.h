#pragma once
#include "stdlib.h"
#include "Constants.h"

class TileMap;
class Tile;

// virtual class for units and items
class GameObject {
public:
	virtual ~GameObject() {};

	virtual void OnRender() = 0;

	// generalization of TakeDamage() for possible implementations of healing, buff/debuff, etc.
	virtual void ReceiveAction(int amt) = 0;

	// for debugging
	virtual std::string toString() = 0;

	// teams for possible factions, currently 0=player, 1=enemy/player2
	virtual small GetTeam() { return Team; };
	virtual void SetTeam(small value) { Team = value; };


	TileMap* tilemap;
	Tile* tile;
	small Team = -2;

};