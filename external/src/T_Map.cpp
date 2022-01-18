//
// Created by yang on 2022/1/15.
//

#include "T_Map.h"
#include <fstream>

T_Graph T_Map::mapWallSprite[100]= {};

bool T_Map::LoadNewMapWallSprite(string path="test") {
    mapWallSprite[1]=T_Graph(L"./Map/Sprite/1.png");
    mapWallSprite[2]=T_Graph(L"./Map/Sprite/2.png");
    mapWallSprite[3]=T_Graph(L"./Map/Sprite/3.png");
    mapWallSprite[50] = T_Graph(L"./Map/Sprite/flower.png");
    mapWallSprite[51] =T_Graph(L"./Map/Sprite/ghost.png");
    mapWallSprite[52] =T_Graph(L"./Map/Sprite/flag.png");
    mapWallSprite[53] = T_Graph(L"./Map/Sprite/gun.png");
    mapWallSprite[54] = T_Graph(L"./Map/Sprite/dead_ghost.png");
    return true;
}

T_Map::T_Map(string mapFilePath) {
    fstream file(mapFilePath);
    LoadNewMapWallSprite();
    if(file.is_open()){
        file>>mapHeight>>mapWidth;
        file>>playerSpawnPoint.x>>playerSpawnPoint.z;
        for(int h=0;h<mapHeight;h++){
            for(int w=0;w<mapWidth;w++){
                int tmp;
                file>>tmp;
                blockType.push_back(tmp);
            }
        }
    }
}

Rast T_Map::getBlockTypeAt(T_Vector3 pos) {
    int rx=(int)pos.x;
    int rz=(int)pos.z;



    if(rx<0||rx>=mapWidth||rz<0||rz>=mapHeight) return Rast(-1,0);
    if(blockType[rx+rz*mapWidth]==0) return Rast(0,0);



    Rast ret(blockType[rx+rz*mapWidth],0);
    float fx=pos.x-rx;fx=min(fx,1-fx);
    float fz=pos.z-rz;fz=min(fz,1-fz);
    ret.x=max(fx,fz);
    return ret;
}
