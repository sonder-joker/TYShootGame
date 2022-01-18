#include "T_Render.h"
#include "T_Scene.h"

bool cmpSprite(const shared_ptr<Sprite> a,const shared_ptr<Sprite> b){
    return a->distanceToCamera>b->distanceToCamera;
}

void T_Render::RenderUpdate(HDC hdc)
{
    HDC memDC= CreateCompatibleDC(hdc);
    //HBITMAP hbitmap= CreateCompatibleBitmap(memDC,screenWidth,screenHeight);
    HBITMAP tempBitmap= (HBITMAP)SelectObject(memDC,backgroundBitmap);
    //绘制天空/地
    BitBlt(hdc,0,0,screenWidth,screenHeight,memDC,0,0,SRCCOPY);
    //绘制墙体
    //HBITMAP wallBitmap= CreateCompatibleBitmap(hdc,screenWidth,screenHeight);

    if(camera==nullptr){
        T_GameObjectManager& gm = *T_Scene::activeScene->gameObjectManager;
        for(auto& gameObj:gm.gameObjectArray){
            for(auto& component:gameObj->componentArray){
                if(component->GetComponentName()=="camera"){
                    camera=dynamic_pointer_cast<Camera>(component);
                    break;
                }
            }
            if(camera!=nullptr) break;
        }
    }
    T_Vector3 playerPos=camera->gameObject.transform.position;
    T_Vector3 playerRot=camera->gameObject.transform.rotation;
    for(int lineNum=0;lineNum<screenWidth;++lineNum){
        T_Vector3 touchPos=playerPos;
        wallDepth[lineNum]=Rast(0,0,0);
        wallDistance[lineNum] = 1.0*0x3f3f3f3f;
        float nowX=playerRot.x-camera->cameraFov/2+lineNum*camera->cameraFov/screenWidth;
        float cosX= cosf(nowX);
        float sinX= sinf(nowX);
        for(float offset=LENGHT_SINGLE_VISIT_STEP;offset<MAX_VISIT_LENGHT;offset+=LENGHT_SINGLE_VISIT_STEP){
            touchPos.x+=cosX*LENGHT_SINGLE_VISIT_STEP;
            touchPos.z+=sinX*LENGHT_SINGLE_VISIT_STEP;
            Rast rast=map.getBlockTypeAt(touchPos);
            if(rast.graphIndex==-1) break;
            if(rast.graphIndex!=0){
                wallDistance[lineNum] = offset;
                float lenToWall=offset*cosf(nowX-playerRot.x)/FIX_RENDER_LENGHT;
                rast.offset=lenToWall;
                wallDepth[lineNum]=rast;
                break;
            }
        }
    }
    PaintRaster(hdc);
    //绘制精灵:
    //获取精灵
    //给精灵按照远近顺序排序
    //按顺序获取精灵
    //计算精灵是否在渲染屏幕内
    //为精灵的每个光栅计算是否应该被墙壁遮挡
    //渲染，回到步骤3
    for(int index=0;index<spriteArray.size();++index){
        Sprite& sprite=*spriteArray[index];
        float tx=sprite.gameObject.transform.position.x-playerPos.x;
        float ty=sprite.gameObject.transform.position.y-playerPos.y;
        sprite.distanceToCamera=sqrtf(tx*tx+ty*ty);
    }
    sort(spriteArray.begin(),spriteArray.end(), cmpSprite);
    int midHeight=screenHeight/2;
    float Pi=3.14159265;
    for(int index=0;index<spriteArray.size();++index){
        Sprite& sprite=*spriteArray[index];
        if(!sprite.gameObject.isActive||sprite.distanceToCamera>MAX_VISIT_LENGHT) continue;
        //计算是否在渲染屏幕内
        float cost= sprite.gameObject.transform.position.z/sprite.distanceToCamera;
        float sint= sprite.gameObject.transform.position.x/sprite.distanceToCamera;
        float thea=acos(cost);
        if(cost>=0&&sint>=0){
            thea+=0;
        }else if(cost<=0&&sint>=0){
            thea+=Pi/2;
        }else if(cost<=0&&sint<=0){
            thea+=Pi;
        }else{
            thea+=Pi*2/3;
        }
        float rot=playerRot.x;
        rot= fmodf(rot,2*Pi);
        if(rot<0) rot+=2*Pi;
        if(
                (thea>=rot-camera->cameraFov/2&&thea<=rot+camera->cameraFov/2)
        ){
            //开始渲染
            thea-=rot-camera->cameraFov/2;
            float lenToSprite=sprite.distanceToCamera*cosf(thea)/FIX_RENDER_LENGHT;
            int rastOffset=(int)(thea*screenWidth/camera->cameraFov);
            int nowWidth=(int)(T_Map::TEXTURE_WIDTH/(lenToSprite));
            int nowHeight=(int)(T_Map::TEXTURE_HEIGHT/(lenToSprite));
            int maxLine=min(nowWidth/2+rastOffset+1,screenWidth);

            for(int screenLine=max(0,rastOffset);screenLine<maxLine;screenLine++){

            }
        }
        //

    }
//    int midHeight=screenHeight/2;
//    HDC memDC= CreateCompatibleDC(destDC);
//    HBITMAP oldBitmap=(HBITMAP) SelectObject(memDC,T_Map::mapWallSprite[1].GetBmpHandle());
//    for(int screenLine=0;screenLine<screenWidth;++screenLine){
//        if(wallDepth[screenLine].graphIndex > 0){
//            Rast& rast=wallDepth[screenLine];
//            SelectObject(memDC,T_Map::mapWallSprite[rast.graphIndex].GetBmpHandle());
//            StretchBlt(destDC,screenLine,midHeight-T_Map::TEXTURE_HEIGHT/(rast.offset*2),1,T_Map::TEXTURE_HEIGHT/rast.offset,
//                       memDC,rast.x*T_Map::TEXTURE_WIDTH,0,1,T_Map::TEXTURE_HEIGHT,SRCCOPY);
//
//        }
//    }
//    SelectObject(memDC,oldBitmap);
//    DeleteObject(memDC);
//    DeleteObject(oldBitmap);

    //绘制UI之类的？

    SelectObject(memDC,tempBitmap);
    DeleteObject(memDC);
    DeleteObject(tempBitmap);
}

void T_Render::Init(int width, int height) {
    SetRenderVar(width,height);
    HDC memDC= CreateCompatibleDC(GetDC(T_Engine::pEngine->m_hWnd));
    wallDepth=std::vector<Rast>(width);
    wallDistance = std::vector<float>(width);
    spriteRast = std::vector<Rast>(width);
    //如果使用内存设备上下文会变成单色Bitmap
    backgroundBitmap= CreateCompatibleBitmap(GetDC(T_Engine::pEngine->m_hWnd),width,height);

    HBITMAP tempBmp=(HBITMAP) SelectObject(memDC,backgroundBitmap);

    int skyBlockHeight=height/(SKY_LEVEL*2)+1;

    for(int level=0;level<SKY_LEVEL;++level){
        HBRUSH brush= CreateSolidBrush(RGB(
                                               (GetRValue(SKY_COLOR_UP)*(SKY_LEVEL-level)+ GetRValue(SKY_COLOR_DOWN)*level)/SKY_LEVEL,
                                               (GetGValue(SKY_COLOR_UP)*(SKY_LEVEL-level)+ GetGValue(SKY_COLOR_DOWN)*level)/SKY_LEVEL,
                                               (GetBValue(SKY_COLOR_UP)*(SKY_LEVEL-level)+ GetBValue(SKY_COLOR_DOWN)*level)/SKY_LEVEL
                                       ));
        RECT rect={0,level*skyBlockHeight,width,(level+1)*skyBlockHeight};
        FillRect(memDC,&rect,brush);
        DeleteObject(brush);
    }
    HBRUSH brush= CreateSolidBrush(GROUND);
    RECT rect={0,height/2,width,height};
    FillRect(memDC,&rect,brush);
    DeleteObject(brush);
    SelectObject(memDC,tempBmp);
    DeleteObject(memDC);
    DeleteObject(tempBmp);
}


void T_Render::SetRenderVar(int width, int height) {
    this->screenWidth=width;
    this->screenHeight=height;
}

T_Render::T_Render(T_Map& tmap):map(tmap) {
    Init(T_Engine::pEngine->wndWidth,T_Engine::pEngine->wndHeight);
}

void T_Render::PaintRaster(HDC destDC) {
    int midHeight=screenHeight/2;
    HDC memDC= CreateCompatibleDC(destDC);
    HBITMAP oldBitmap=(HBITMAP) SelectObject(memDC,T_Map::mapWallSprite[1].GetBmpHandle());
    for(int screenLine=0;screenLine<screenWidth;++screenLine){
        if(wallDepth[screenLine].graphIndex > 0){
            Rast& rast=wallDepth[screenLine];
            SelectObject(memDC,T_Map::mapWallSprite[rast.graphIndex].GetBmpHandle());
            StretchBlt(destDC,screenLine,midHeight-T_Map::TEXTURE_HEIGHT/(rast.offset*2),1,T_Map::TEXTURE_HEIGHT/rast.offset,
                       memDC,rast.x*T_Map::TEXTURE_WIDTH,0,1,T_Map::TEXTURE_HEIGHT,SRCCOPY);
            
        }
    }
    SelectObject(memDC,oldBitmap);
    DeleteObject(memDC);
    DeleteObject(oldBitmap);
}

Camera::Camera(T_GameObject& tGameObject): T_Component(tGameObject) {

}

void Camera::KeyAction(int KeyType, int ActionType) {
    /*
    if (ActionType == KEY_DOWN) {
       if(KeyType=='T'){
           cameraFov+=0.05;
       }
       if(KeyType=='Y'){
           cameraFov-=0.05;
       }
    }
    */
}

shared_ptr<Sprite> Sprite::CreateSprite(T_GameObject& gameObject,int graphIndex) {
    shared_ptr<Sprite> sprite= make_shared<Sprite>(gameObject,graphIndex);
    T_Scene::activeScene->renderManager->spriteArray.push_back(sprite);
    return sprite;
}
