//
// Created by yang on 2022/1/15.
//

#include "T_Map.h"
#include <fstream>

bool T_Map::LoadNewMapWallSprite(string path) {

    return false;
}

T_Map::T_Map(string mapFilePath) {
    fstream file(mapFilePath);
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
    //���ֿ����
    if(rx<0||rx>=mapWidth||rz<0||rz>=mapHeight) return Rast(mapWallSprite[0],0);
    if(blockType[rx+rz*mapWidth]==0) return Rast(mapWallSprite[0],0);

    Rast ret(mapWallSprite[blockType[rx+rz*mapWidth]],0);
    float fx=pos.x-rx;fx=min(fx,1-fx);
    float fz=pos.z-rz;fz=min(fz,1-fz);
    ret.x=max(fx,fz);
    return ret;
}
