#pragma once
#include "T_GameObject.h"
#include "T_Engine.h"

/// <summary>
/// ����͸�����
/// </summary>
class Camera :
        public T_Component
{
public:
    //������ӽ�(��λ�����ȣ�
    float cameraFov;


};
class T_Render :
        public T_IManager
{
public:
    int GetManagerID() override {return 1;}
    unique_ptr<Camera> camera;
    /*
     * Some Issue
     * ��ô������������?
     * ���о���һ�£��о���ֱ����Ⱦ�����������Ժ�����Ⱦǽ�棬�Ϳ���Ӫ�������ߺ͵���ĸо�
     * ��ô������֮���ǰ���������⣿
     * ҪԤ����������Ϸ����֮��ľ��롣���һ���㷨��ÿ֡��On��ʱ��������
     * Ȼ��Զ����Ⱦ˳��
     * ��ô��������ǽ��֮����������⣿
     * ����Ⱦǽ�壬����Ⱦ���飬��������ĳ�д���ǽ��ĳ�У�����Ⱦ�������
     */
    void RenderUpdate(HDC hdc);
    void SetRenderVar();
    vector<float> wallDepth;
    int screenWidth;
    int screenHeight;
};

class Sprite :
        public T_Component
{
    unique_ptr<T_Graph> image;

};


