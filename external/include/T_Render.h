#pragma once
#include "T_GameObject.h"
#include "T_Engine.h"

/// <summary>
/// 鱼眼透视相机
/// </summary>
class Camera :
        public T_Component
{
public:
    //摄像机视角(单位：弧度）
    float cameraFov;


};
class T_Render :
        public T_IManager
{
public:
    unique_ptr<Camera> camera;
    /*
     * Some Issue
     * 怎么画地面和天际线?
     * 我研究了一下，感觉先直接渲染地面和天际线以后再渲染墙面，就可以营造出天际线和地面的感觉
     * 怎么处理精灵之间的前后遮罩问题？
     * 要预处理精灵与游戏物体之间的距离。设计一个算法在每帧用On的时间排序精灵
     * 然后远近渲染顺序。
     * 怎么处理精灵与墙体之间的遮罩问题？
     * 先渲染墙体，再渲染精灵，如果精灵的某列大于墙体某列，就渲染精灵该列
     */
    void RenderUpdate(HDC hdc);
    vector<float> wallDepth;
    int screenWidth;
    int screenHeight;
};

class Sprite :
        public T_Component
{
    unique_ptr<T_Graph> image;

};


