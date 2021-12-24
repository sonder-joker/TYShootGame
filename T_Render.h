#pragma once
#include "T_Engine/T_GameObject.h"
class T_Render :
    public T_IManager
{
public:
    unique_ptr<Camera> camera;
    void RenderUpdate(HDC hdc);
private:
    
};

class Image :
    public T_Component
{
    unique_ptr<T_Graph> image;

};
/// <summary>
/// 小孔成像原理的透视相机组件
/// </summary>
/// 近屏幕：显示屏幕
class Camera :
    public T_Component 
{
public:
    //以下为摄像机内参

    /// <summary>
    /// 近屏幕到相机距离
    /// </summary>
    float closeScreen;
    /// <summary>
    /// 远屏幕到相机的距离
    /// </summary>
    float farScreen;
    /// <summary>
    /// 近屏幕（显示屏幕）宽
    /// </summary>
    int screenX;
    /// <summary>
    /// 近屏幕高
    /// </summary>
    int screenY;
    /// <summary>
    /// 一单位距离转化为多少屏幕像素的比率
    /// </summary>
    float screenRate;
    //TODO 编写相机参数问题

    
};
