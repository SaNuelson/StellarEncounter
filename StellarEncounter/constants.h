#pragma once
#include "Entity.h"
#include "image_control.h"

namespace constants {


	int SCREEN_HEIGHT = 800;
	int SCREEN_WIDTH = 600;

	enum WindowState { Starting, MainMenu, Battle, Quitting };

	vector<Character> SetLevel1() {
		vector<Character> level;
		level.push_back(Character(5, 5, 100, 50, 10, true, IMG_Load("face.png")));
		level.push_back(Character(10, 5, 100, 50, 10, false,IMG_Load("face.png")));

		return level;
	}


}