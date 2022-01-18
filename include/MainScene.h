#pragma once
#include "T_GameObject.h"
#include "T_Map.h"
#include "T_Scene.h"

class MainScene :
    public T_Scene
{
public:
    void LoadScene() override;
};

class TestScene:
        public T_Scene{
public:

    void LoadScene() override;
};

class Scene1:
        public T_Scene{
public:
    void LoadScene() override;
};