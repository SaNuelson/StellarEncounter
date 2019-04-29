#pragma once
#include "stdlib.h"

// speed - in milliseconds

class BoxTileMap;
class BoxTile;

class GameObject {
public:
	~GameObject() {}

	virtual bool isEnemy() = 0;

	virtual void OnRender() = 0;

	virtual void ReceiveAction(int amt) = 0;

	virtual std::string toString() = 0;

	virtual GameObject* getPtr() = 0;
};