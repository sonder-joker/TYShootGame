#include "T_3dEngine.h"

void T_3dEngine::GameInit()
{
	scene->LoadScene();
}

void T_3dEngine::GameLogic()
{
	for (auto& managerItor : scene->ManagerMap) {
		auto& manager = managerItor.second;
		manager->FixedUpdate();
	}
}

void T_3dEngine::GamePaint(HDC hdc)
{
	for()
}

void T_3dEngine::GameEnd()
{
}

void T_3dEngine::GameKeyAction(int ActionType)
{
}

void T_3dEngine::GameMouseAction(int x, int y, int ActionType)
{
}

