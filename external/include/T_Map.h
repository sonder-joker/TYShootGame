//
// Created by yang on 2022/1/15.
//

#ifndef TYSHOOTGAME_T_MAP_H
#define TYSHOOTGAME_T_MAP_H
#include "T_Config.h"
#include "T_GameObject.h"

//地图数据存储类

struct Rast{
    Rast(int _graph=0,float _x=0,float offset=0):graphIndex(_graph),x(x),offset(offset){

    }
    Rast(const Rast& rast) = default;
    Rast operator=(const Rast& rast){
        graphIndex=rast.graphIndex;
        x=rast.x;
        offset=rast.offset;
        return *this;
    }
    int graphIndex;
    float x;
    float offset;
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

    static const int TEXTURE_HEIGHT=64;
    static const int TEXTURE_WIDTH=64;
};



#endif //TYSHOOTGAME_T_MAP_H
