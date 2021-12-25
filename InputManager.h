#pragma once
#include "T_Engine/T_GameObject.h"
#include <stack>


enum MOUSE {
    LMB = 0,
    RMB = 1
};

class InputManager :
    public T_IManager
{
public:
    static unique_ptr<InputManager>& instance;
    bool isKeyDown[256];
    bool isKeyUp[256];
    T_Vector3 mousePos;
    int isMouseDown[3];

    InputManager();
    /// <summary>
    /// 获取按键是否下压
    /// </summary>
    /// <param name="keyType">按键类型(参考wParam)</param>
    /// <returns></returns>
    inline bool GetKeyDown(int keyType);
    /// <summary>
    /// 获取按键是否弹起
    /// </summary>
    /// <param name="keyType">按键类型(参考wParam)</param>
    /// <returns></returns>
    inline bool GetKeyUp(int keyType);
    inline T_Vector3 GetMousePos();
    inline bool GetMouseDown(int keyType);
    inline bool GetMouseUp(int keyType);
    void KeyAction(int KeyType, int Action) override;
    void MouseAction(int x, int y, int Action) override;
    void Update() override;
};

