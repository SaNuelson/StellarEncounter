#pragma once
#include "stdlib.h"
#include "ResourceManager.h"
#include "Tilemap.h"
#include "GameObject.h"
#include "Unit.h"
#include "Item.h"

// parent to all scenes
class Scene {
public:

	Scene() = default;
	~Scene() = default;

	virtual void ResolveInput(SDL_Event& e) = 0;
	virtual void OnUpdate(double delta) = 0;
	virtual void OnRender() = 0;

	virtual void SetArgs(int code) {};

};