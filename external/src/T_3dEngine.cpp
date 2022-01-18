#include "T_3dEngine.h"

void T_3dEngine::GameInit()
{
	scene->LoadScene();
	scene->gameObjectManager->Start();
}

void T_3dEngine::GameLogic()
{
	scene->gameObjectManager->FixedUpdate();
	for (auto& managerItor : scene->ManagerMap) {
		managerItor->FixedUpdate();
	}
}

void T_3dEngine::GamePaint(HDC hdc)
{
	scene->gameObjectManager->Update();
	for (auto& managerItor : scene->ManagerMap) {
		managerItor->Update();
	}
    scene->renderManager->Update(hdc);
	scene->gameObjectManager->UpdateLate();
	for (auto& managerItor : scene->ManagerMap) {
		managerItor->UpdateLate();
	}
}

void T_3dEngine::GameEnd()
{
	//Ëæ±ã°É
}

void T_3dEngine::GameKeyAction(int KeyType,int ActionType)
{
	scene->gameObjectManager->KeyAction(KeyType, ActionType);
	for (auto& managerItor : scene->ManagerMap) {
		managerItor->KeyAction(KeyType, ActionType);
	}
}

void T_3dEngine::GameMouseAction(int x, int y, int ActionType)
{
	scene->gameObjectManager->MouseAction(x,y,ActionType);
	for (auto& managerItor : scene->ManagerMap) {
		managerItor->MouseAction(x,y,ActionType);
	}
}

