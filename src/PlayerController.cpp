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
		gameObject.transform.rotation.x += 0.05;
	}
	else if (InputManager::GetInstance().GetKeyDown('A')) {
		gameObject.transform.rotation.x -= 0.05;
	}
	gameObject.transform.position.x += move.z * v * cosf(gameObject.transform.rotation.x);
	gameObject.transform.position.z += move.z * v * sinf(gameObject.transform.rotation.x);
}
