#pragma once
#include "stdlib.h"
#include "Constants.h"

// speed - in milliseconds

class TileMap;
class Tile;

class GameObject {
public:
	~GameObject() {}

	virtual void OnRender() = 0;

	virtual void ReceiveAction(int amt) = 0;

	virtual std::string toString() = 0;

	virtual small GetTeam() { return Team; };
	virtual void SetTeam(small value) { Team = value; };


	TileMap* tilemap;
	Tile* tile;
	small Team = -2;

};