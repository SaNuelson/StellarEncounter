#include "stdlibs.h"
#include "WindowManager.h"

int main() {

	int retCode = Managers::WindowManager::OnInit();
	Managers::WindowManager::OnCleanup();

	return retCode;

}