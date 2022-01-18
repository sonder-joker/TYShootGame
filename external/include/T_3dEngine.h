#pragma once
#include "T_Engine.h"
#include "T_GameObject.h"
#include "T_Render.h"
#include "T_Scene.h"
class T_3dEngine :
    public T_Engine
{
public:
    T_3dEngine(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
               WORD Icon = NULL, WORD SmIcon = NULL,
               int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT,
               COLORREF bkColor = WIN_BKCLR):
               T_Engine(hInstance,szWindowClass,szTitle,Icon,SmIcon,iWidth,iHeight,bkColor){};
    unique_ptr<T_Scene> scene;
    void GameInit() override;
    void GameLogic() override;
    void GamePaint(HDC hdc) override;
    void GameEnd() override;
    void GameKeyAction(int KeyType,int ActionType) override;
    void GameMouseAction(int x, int y, int ActionType) override;
};

