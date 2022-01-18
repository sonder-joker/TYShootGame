//
// Created by yang on 2022/1/18.
//

#include "T_Scene.h"

T_Scene* T_Scene::activeScene=nullptr;


T_Scene::T_Scene()
{
    activeScene=this;
    gameObjectManager = make_unique<T_GameObjectManager>();
    //renderManager = make_unique<T_Render>();
}
