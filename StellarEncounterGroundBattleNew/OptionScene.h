#pragma once
#include "stdlib.h"
#include "Scene.h"

class OptionScene : public Scene {



	// Inherited via Scene
	virtual void ResolveInput(SDL_Event& e) override;

	virtual void OnUpdate(double delta) override;

	virtual void OnRender() override;

};