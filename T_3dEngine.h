#pragma once
#include "T_Engine/T_Engine.h"
class T_3dEngine :
    public T_Engine
{
public:
    virtual void GameSceneSet() = 0;
    void GameInit() override;
   
};

