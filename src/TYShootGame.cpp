// TYShootGame.cpp : 定义应用程序的入口点。
//

#include <windows.h>
#include "TYShootGame.h"
#include "T_Config.h"
#include "T_GameObject.h"
#include "T_3dEngine.h"
#include "MainScene.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
        _In_opt_ HINSTANCE hPrevInstance,
        _In_ LPWSTR    lpCmdLine,
        _In_ int       nCmdShow)
{
    LPCTSTR title=L"Shooter";
    T_3dEngine* engine=new T_3dEngine(hInstance,WIN_CLASS,title, NULL, NULL, 1024, 768);
    engine->scene=make_unique<MainScene>();
    engine->StartEngine();
}
