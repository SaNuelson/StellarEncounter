#pragma once
#include "stdlib.h"

// speed - in milliseconds

class BoxTileMap;
class BoxTile;

class GameObject {
public:
	~GameObject() {}

	virtual bool isEnemy();

	virtual void OnRender() {};

	virtual std::string toString();

	virtual GameObject* getPtr();
};