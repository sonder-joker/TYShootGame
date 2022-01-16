#include "PlayerController.h"
#include "InputManager.h"

void PlayerController::Update()
{
	T_Vector3 move;
	if (InputManager::GetInstance().GetKeyDown('W')) {
		move.z += 1;
	}
	else if (InputManager::GetInstance().GetKeyDown('S')) {
		move.z -= 1;
	}
	if (InputManager::GetInstance().GetKeyDown('D')) {
		move.x += 1;
	}
	else if (InputManager::GetInstance().GetKeyDown('A')) {
		move.x -= 1;
	}

	//TODO ÒÆ¶¯
}
