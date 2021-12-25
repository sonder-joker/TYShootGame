#include "PlayerController.h"
#include "InputManager.h"

void PlayerController::Update()
{
	T_Vector3 move;
	if (InputManager::instance->GetKeyDown('W')) {
		move.z += 1;
	}
	else if (InputManager::instance->GetKeyDown('S')) {
		move.z -= 1;
	}
	if (InputManager::instance->GetKeyDown('D')) {
		move.x += 1;
	}
	else if (InputManager::instance->GetKeyDown('A')) {
		move.x -= 1;
	}
	//TODO ÒÆ¶¯
}
