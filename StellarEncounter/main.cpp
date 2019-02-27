#include "baselibs.h"
#include "utils.h"
#include "image_control.h"
#include "GameScreen.h"

using namespace std;


int main(int argc, char * argv[]) {

	GameScreen game;

	int ret = game.OnInit();

	game.~GameScreen();

	return 0;

}