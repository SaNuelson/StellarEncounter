#pragma once
#include "stdlib.h"

using big = uint16_t;
using small = uint8_t;
// speed - in milliseconds

class BoxTileMap;
class BoxTile;

class GameObject {
public:
	~GameObject() {}

	virtual bool isEnemy();

	virtual void ResolveEvent(SDL_Event& e) {};
	virtual void OnUpdate(double delta) {};
	virtual void OnRender() {};

	virtual std::string toString();

	virtual GameObject* getPtr();
};

