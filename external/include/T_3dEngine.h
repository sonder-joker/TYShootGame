#pragma once
#include "T_Engine.h"
#include "T_GameObject.h"
class T_3dEngine :
    public T_Engine
{
public:
    unique_ptr<T_Scene> scene;
    void GameInit() override;
    void GameLogic() override;
    void GamePaint(HDC hdc) override;
    void GameEnd() override;
    void GameKeyAction(int KeyType,int ActionType) override;
    void GameMouseAction(int x, int y, int ActionType) override;
};

