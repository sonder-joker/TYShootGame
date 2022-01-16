#include "InputManager.h"

InputManager* InputManager::instance=nullptr;

InputManager::InputManager()
{
	instance = this;
}

bool InputManager::GetKeyDown(int keyType)
{
	return isKeyDown[keyType];
}

bool InputManager::GetKeyUp(int keyType)
{
	return isKeyUp[keyType];
}

T_Vector3 InputManager::GetMousePos()
{
	return mousePos;
}

bool InputManager::GetMouseDown(int keyType)
{
	return isMouseDown[keyType] == 2;
}

bool InputManager::GetMouseUp(int keyType) {
	return isMouseDown[keyType] == 1;
}


void InputManager::KeyAction(int keyType, int action)
{
	if (action == KEY_DOWN) {
		isKeyDown[keyType] = true;
	}
	else if (action == KEY_UP) {
		isKeyUp[keyType] = true;
	}
}

void InputManager::MouseAction(int x, int y, int Action)
{
	if (Action == MOUSE_MOVE) {
		mousePos.x = x;
		mousePos.y = y;
	}
	if (Action == MOUSE_LCLICK) {
		isMouseDown[0] = 3;
	}
	if (Action == MOUSE_RCLICK) {
		isMouseDown[1] = 3;
	}
}

void InputManager::Update() {
	for (int i = 0; i < 256; ++i) {
		if (isKeyUp[i]) {
			if (isKeyDown[i]) {
				isKeyDown[i] = false;
			}
			else {
				isKeyUp[i] = false;
			}
		}
	}
	for (int i = 0; i < 3; ++i) {
		if (isMouseDown[i]) {
			isMouseDown[i]--;
		}
	}
}

