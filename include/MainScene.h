#pragma once
#include "T_GameObject.h"
#include "T_Map.h"

class MainScene :
    public T_Scene
{
public:
    void LoadScene() override;
};

class TestScene:
        public T_Scene{
public:
    unique_ptr<T_Map> gameMap;
    void LoadScene() override;
};