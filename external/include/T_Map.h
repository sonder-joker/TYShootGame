//
// Created by yang on 2022/1/15.
//

#ifndef TYSHOOTGAME_T_MAP_H
#define TYSHOOTGAME_T_MAP_H
#include "T_Config.h"
#include "T_GameObject.h"

//地图数据存储类

struct Rast{
    Rast(T_Graph& _graph,float _x):graph(_graph),x(x){
    }
    T_Graph& graph;
    float x;
};

class T_Map{
public:
    static T_Graph mapWallSprite[100];
    T_Vector3 playerSpawnPoint;
    int mapWidth,mapHeight;
    vector<int> blockType;
    static bool LoadNewMapWallSprite(string spritePath);
    T_Map(string mapFilePath);
    Rast getBlockTypeAt(T_Vector3 pos);
};



#endif //TYSHOOTGAME_T_MAP_H
