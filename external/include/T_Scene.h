//
// Created by yang on 2022/1/18.
//

#ifndef TYSHOOTGAME_T_SCENE_H
#define TYSHOOTGAME_T_SCENE_H
#include "T_Config.h"
#include "T_GameObject.h"
#include "T_Render.h"

class T_Scene {
public:
    T_Scene();
    static T_Scene* activeScene;
    static T_Scene& GetActiveScene(){return *activeScene;};
    virtual void LoadScene() = 0;
    vector<shared_ptr<T_IManager>> ManagerMap;
    unique_ptr<T_GameObjectManager> gameObjectManager;
    unique_ptr<T_Render> renderManager;

    unique_ptr<T_Map> gameMap;
};


#endif //TYSHOOTGAME_T_SCENE_H
