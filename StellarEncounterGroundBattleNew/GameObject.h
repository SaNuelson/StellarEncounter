#pragma once
#include "stdlib.h"

// speed - in milliseconds

class TileMap;
class Tile;

class GameObject {
public:
	~GameObject() {}

	virtual bool isEnemy() = 0;

	virtual void OnRender() = 0;

	virtual void ReceiveAction(int amt) = 0;

	virtual std::string toString() = 0;

	TileMap* tilemap;
	Tile* tile;

};