#pragma once
#include "stdlibs.h"
#include "Button.h"
#include "ResourceManager.h"

class Scene : std::enable_shared_from_this<Scene>{

	Scene() {};

	virtual std::shared_ptr<Scene> Run() = 0;

	std::shared_ptr<Scene> getptr() { return shared_from_this(); };

};

class MainMenuScene : public Scene {

	std::shared_ptr<Scene> Run() override;

};